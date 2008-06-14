/* This file is part of libgfc
 *
 * AUTHORS
 *     Sven Herzberg  <sven@imendio.com>
 *
 * Copyright (C) 2007,2008  Sven Herzberg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#include "gfc-job.h"

#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#include <gfc-spawn-simple.h>

typedef enum {
	GFC_JOB_SETUP,
	GFC_JOB_EXECUTE,
	GFC_JOB_DONE
} GfcJobState;

/* FIXME: some rewrite planned
 * The job should have a status field. The available private fields should not
 * depend on the status. Instead, there should be a status_data union (which
 * basically works like GdkEvent. */

struct _GfcJobPrivate {
	/* state indicating the object's state */
	GfcJobState       state;

	/* data for GFC_JOB_SETUP (also valid later) */
	gchar           * working_folder;
	gchar           **argv;

	/* data for GFC_JOB_SETUP only */
	GfcSpawnStrategy* spawn;

	/* data for GFC_JOB_EXECUTE */
	GfcReader       * err_reader;
	GfcReader       * out_reader;
	GPid              pid;
	guint             child_watch_tag;

	/* data for GFC_JOB_DONE */
	gint              return_code;
	guint             exited : 1;
};

enum {
	PROP_0,
	PROP_ARGV,
	PROP_COMMAND,
	PROP_SPAWN,
	PROP_WORKING_FOLDER
};

enum {
	DONE,
	N_SIGNALS
};

static guint gfc_job_signals[N_SIGNALS] = {0};

G_DEFINE_TYPE (GfcJob, gfc_job, G_TYPE_OBJECT);

static void
gfc_job_init (GfcJob* self)
{
	self->_private = G_TYPE_INSTANCE_GET_PRIVATE (self,
						      GFC_TYPE_JOB,
						      GfcJobPrivate);
	self->_private->state = GFC_JOB_SETUP;
}

static void
job_set_status (GfcJob  * self,
		gint      return_code,
		gboolean  exited)
{
	gfc_job_set_return_code (GFC_JOB (self), return_code);
	gfc_job_set_exited      (GFC_JOB (self), exited);

	/* usually the application code will unref() the job in the done signal handler */
	g_object_ref (self);

	// FIXME: emit the signal by id once the emission is moved into the GfcJob
	g_signal_emit_by_name (self, "done");

	gfc_job_set_out_reader (GFC_JOB (self), NULL);
	gfc_job_set_err_reader (GFC_JOB (self), NULL);

	g_object_unref (self);
}

static void
job_child_watch_cb (GPid     pid,
		    gint     status,
		    gpointer data)
{
	GfcJob* self = GFC_JOB (data);

	g_spawn_close_pid (pid);
	gfc_job_set_pid (GFC_JOB (self),
			 0);

	job_set_status (self,
			WEXITSTATUS (status),
			WIFEXITED (status));
}

static void
job_constructed (GObject* object)
{
	GfcJob* self = GFC_JOB (object);

	gboolean  success = FALSE;
	GError  * error   = NULL;
	gint      out     = 0;
	gint      err     = 0;
	GPid      pid     = 0;

	if (G_UNLIKELY (!gfc_job_get_argv (GFC_JOB (self)))) {
		g_warning ("no command or argument vector has been set");

		self->_private->state = GFC_JOB_DONE;

		goto finish;
	}

	/* FIXME: should goto finish; */
	g_return_if_fail (self->_private->spawn);

	success = gfc_spawn_strategy_spawn (self->_private->spawn,
					    gfc_job_get_working_folder (self),
					    gfc_job_get_argv (self),
					    NULL,
					    G_SPAWN_SEARCH_PATH | G_SPAWN_DO_NOT_REAP_CHILD,
					    &pid,
					    NULL, /* in */
					    &out,
					    &err,
					    &error);

	if (!success || error) {
		g_warning ("Error executing command \"%s\" in \"%s\": %s",
			   gfc_job_get_command (self),
			   gfc_job_get_working_folder (self),
			   error->message);
		g_error_free (error);
		// FIXME: set up an idle handler that invokes "canceled"
	} else {
		gfc_job_set_out_reader (GFC_JOB (self),
					gfc_reader_new (out));
		g_object_unref (gfc_job_get_out_reader (self));
		gfc_job_set_err_reader (GFC_JOB (self),
					gfc_reader_new (err));
		g_object_unref (gfc_job_get_err_reader (self));
		gfc_job_set_pid (self, pid);
		self->_private->child_watch_tag = g_child_watch_add (pid,
								     job_child_watch_cb,
								     self);
	}

	self->_private->state = GFC_JOB_EXECUTE;

finish:
	g_object_unref (self->_private->spawn);
	self->_private->spawn = NULL;

	if (G_OBJECT_CLASS (gfc_job_parent_class)->constructed) {
		G_OBJECT_CLASS (gfc_job_parent_class)->constructed (object);
	}
}

static void
job_finalize (GObject* object)
{
	GfcJob* self = GFC_JOB (object);

	g_free (self->_private->working_folder);
	g_strfreev (self->_private->argv);

	// FIXME: kill the process

	if (self->_private->child_watch_tag) {
		g_source_remove (self->_private->child_watch_tag);
	}

	if (self->_private->err_reader) {
		// FIXME: move to dispose
		// FIXME: try to assert for NULL
		g_object_unref (self->_private->err_reader);
		self->_private->err_reader = NULL;
	}

	if (self->_private->out_reader) {
		// FIXME: move to dispose
		// FIXME: try to assert for NULL
		g_object_unref (self->_private->out_reader);
		self->_private->out_reader = NULL;
	}

	if (self->_private->pid) {
		g_spawn_close_pid (self->_private->pid);
	}

	G_OBJECT_CLASS (gfc_job_parent_class)->finalize (object);
}

static void
job_get_property (GObject   * object,
		  guint       prop_id,
		  GValue    * value,
		  GParamSpec* pspec)
{
	GfcJob* self = GFC_JOB (object);

	switch (prop_id) {
	case PROP_ARGV:
		g_value_set_boxed (value, self->_private->argv);
		break;
	case PROP_COMMAND:
		g_value_set_string (value, gfc_job_get_command (GFC_JOB (self)));
		break;
	case PROP_WORKING_FOLDER:
		g_value_set_string (value, self->_private->working_folder);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
job_set_property (GObject     * object,
		  guint         prop_id,
		  GValue const* value,
		  GParamSpec  * pspec)
{
	GError* error = NULL;
	GfcJob* self  = GFC_JOB (object);
	gchar **argv  = NULL;

	switch (prop_id) {
	case PROP_ARGV:
		g_return_if_fail (self->_private->state == GFC_JOB_SETUP);
		if (!g_value_get_boxed (value)) {
			break;
		}
		g_return_if_fail (!self->_private->argv);
		self->_private->argv = g_value_dup_boxed (value);
		g_object_notify (object, "argv");
		break;
	case PROP_COMMAND:
		if (!g_value_get_string (value)) {
			break;
		}
		if (g_shell_parse_argv (g_value_get_string (value),
					NULL,
					&argv,
					&error))
		{
			g_object_set (object,
				      "argv", argv,
				      NULL);
			g_strfreev (argv);
			g_object_notify (object, "command");
		} else {
			g_warning ("%s: error escaping command:\ncommand: \"%s\"\nerror:   %s",
				   G_STRFUNC,
				   g_value_get_string (value),
				   error ? error->message : "(none)");
			g_clear_error (&error);
		}
		break;
	case PROP_SPAWN:
		g_return_if_fail (!self->_private->spawn);

		if (!g_value_get_object (value)) {
			self->_private->spawn = gfc_spawn_simple_new ();
		} else {
			self->_private->spawn = g_value_dup_object (value);
		}
		g_object_notify (object, "spawn");
		break;
	case PROP_WORKING_FOLDER:
		g_return_if_fail (self->_private->state == GFC_JOB_SETUP);
		g_return_if_fail (!self->_private->working_folder);

		self->_private->working_folder = g_value_dup_string (value);
		g_object_notify (object, "working-folder");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
gfc_job_class_init (GfcJobClass* self_class)
{
	GObjectClass* object_class = G_OBJECT_CLASS (self_class);

	object_class->constructed  = job_constructed;
	object_class->finalize     = job_finalize;
	object_class->get_property = job_get_property;
	object_class->set_property = job_set_property;

	g_object_class_install_property (object_class, PROP_ARGV,
					 g_param_spec_boxed ("argv", "argv", "argv",
							     G_TYPE_STRV, G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (object_class, PROP_COMMAND,
					 g_param_spec_string ("command", NULL, NULL,
							      NULL, G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (object_class, PROP_SPAWN,
					 g_param_spec_object ("spawn", "spawn", "spawn",
							      GFC_TYPE_SPAWN_STRATEGY,
							      G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (object_class, PROP_WORKING_FOLDER,
					 g_param_spec_string ("working-folder", "working-folder", "working-folder",
							      NULL, G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

	gfc_job_signals[DONE] = g_signal_new ("done", GFC_TYPE_JOB,
					      G_SIGNAL_RUN_LAST, 0, // FIXME: add default handler to release the pid
					      NULL, NULL,
					      g_cclosure_marshal_VOID__VOID,
					      G_TYPE_NONE,
					      0);

	g_type_class_add_private (self_class, sizeof (GfcJobPrivate));
}

gchar**
gfc_job_get_argv (GfcJob const* self)
{
	// FIXME: fix the return value to be correctly const'ed
	g_return_val_if_fail (GFC_IS_JOB (self), NULL);

	return self->_private->argv;
}

gchar const*
gfc_job_get_command (GfcJob const* self)
{
	g_return_val_if_fail (GFC_IS_JOB (self), NULL);

	return self->_private->argv ?
	       self->_private->argv[0] :
	       NULL;
}

GfcReader*
gfc_job_get_err_reader (GfcJob const* self)
{
	g_return_val_if_fail (GFC_IS_JOB (self), NULL);

	return self->_private->err_reader;
}

gboolean
gfc_job_get_exited (GfcJob const* self)
{
	g_return_val_if_fail (GFC_IS_JOB (self), FALSE);
	g_return_val_if_fail (self->_private->state == GFC_JOB_DONE, FALSE);

	return self->_private->exited;
}

GfcReader*
gfc_job_get_out_reader (GfcJob const* self)
{
	g_return_val_if_fail (GFC_IS_JOB (self), NULL);

	return self->_private->out_reader;
}

GPid
gfc_job_get_pid (GfcJob const* self)
{
	g_return_val_if_fail (GFC_IS_JOB (self), 0);

	return self->_private->pid;
}

gint
gfc_job_get_return_code (GfcJob const* self)
{
	g_return_val_if_fail (GFC_IS_JOB (self), -1);
	g_return_val_if_fail (self->_private->state == GFC_JOB_DONE, -1);

	return self->_private->return_code;
}

gchar const*
gfc_job_get_working_folder (GfcJob const* self)
{
	g_return_val_if_fail (GFC_IS_JOB (self), NULL);

	return self->_private->working_folder;
}

gboolean
gfc_job_kill (GfcJob* self)
{
	g_return_val_if_fail (GFC_IS_JOB (self), FALSE);
	g_return_val_if_fail (gfc_job_get_pid (GFC_JOB (self)), FALSE);

	if (kill (gfc_job_get_pid (GFC_JOB (self)), SIGKILL) != 0) {
		g_warning ("Error killing process: %s",
			   g_strerror (errno));
		return FALSE;
	} else {
		g_spawn_close_pid (gfc_job_get_pid (GFC_JOB (self)));
		gfc_job_set_pid (GFC_JOB (self), 0);
		/* FIXME: I actually think that this should be triggered by the
		 * child watch anyways - test case needed */
		job_set_status (self, 1, FALSE); // FIXME: maybe add is_killed()
		return TRUE;
	}
}

GfcJob*
gfc_job_new (gchar const* working_folder,
	     gchar const* command)
{
	return g_object_new (GFC_TYPE_JOB,
			     "working-folder", working_folder,
			     "command",        command,
			     NULL);
}

void
gfc_job_set_err_reader (GfcJob   * self,
			GfcReader* reader)
{
	g_return_if_fail (GFC_IS_JOB (self));
	g_return_if_fail (!reader || GFC_IS_READER (reader));

	if (self->_private->err_reader == reader) {
		return;
	}

	if (self->_private->err_reader) {
		g_object_unref (self->_private->err_reader);
		self->_private->err_reader = NULL;
	}

	if (reader) {
		self->_private->err_reader = g_object_ref (reader);
	}
}

void
gfc_job_set_exited (GfcJob  * self,
		    gboolean  exited)
{
	g_return_if_fail (GFC_IS_JOB (self));
	g_return_if_fail (self->_private->state == GFC_JOB_DONE);

	self->_private->exited = exited;
}

void
gfc_job_set_out_reader (GfcJob   * self,
			GfcReader* reader)
{
	g_return_if_fail (GFC_IS_JOB (self));
	g_return_if_fail (!reader || GFC_IS_READER (reader));

	if (self->_private->out_reader == reader) {
		return;
	}

	if (self->_private->out_reader) {
		g_object_unref (self->_private->out_reader);
		self->_private->out_reader = NULL;
	}

	if (reader) {
		self->_private->out_reader = g_object_ref (reader);
	}
}

void
gfc_job_set_pid (GfcJob* self,
		 GPid    pid)
{
	g_return_if_fail (GFC_IS_JOB (self));

	self->_private->pid = pid;
}

void
gfc_job_set_return_code (GfcJob* self,
			 gint    return_code)
{
	g_return_if_fail (GFC_IS_JOB (self));
	//g_return_if_fail (self->_private->state == GFC_JOB_DONE);
	self->_private->state = GFC_JOB_DONE;

	self->_private->return_code = return_code;
}

