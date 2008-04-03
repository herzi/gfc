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

typedef enum {
	GFC_JOB_SETUP,
	GFC_JOB_EXECUTE,
	GFC_JOB_DONE
} GfcJobState;

struct _GfcJobPrivate {
	/* state indicating the object's state */
	GfcJobState  state;

	/* data for GFC_JOB_SETUP (also valid later) */
	gchar      * working_folder;
	gchar      **argv;

	/* data for GFC_JOB_EXECUTE */
	GfcReader  * out_reader;
};

enum {
	PROP_0,
	PROP_ARGV,
	PROP_COMMAND,
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
job_constructed (GObject* object)
{
	GfcJob* self = GFC_JOB (object);

	// FIXME: spawn process and connect to the watch
	// FIXME: after executing the process make sure the state gets set to done

	self->_private->state = GFC_JOB_EXECUTE;

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

	if (self->_private->out_reader) {
		g_object_unref (self->_private->out_reader);
		self->_private->out_reader = NULL;
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
	GfcJob* self = GFC_JOB (object);
	gchar** argv;

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
		argv = g_new0 (gchar*, 2);
		argv[0] = g_value_dup_string (value);
		g_object_set (object,
			      "argv", argv,
			      NULL);
		g_strfreev (argv);
		g_object_notify (object, "command");
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
					 g_param_spec_boxed ("command", NULL, NULL,
							     G_TYPE_STRING, G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (object_class, PROP_WORKING_FOLDER,
					 g_param_spec_boxed ("working-folder", NULL, NULL,
							     G_TYPE_STRING, G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

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
gfc_job_get_out_reader (GfcJob const* self)
{
	g_return_val_if_fail (GFC_IS_JOB (self), NULL);

	return self->_private->out_reader;
}

gchar const*
gfc_job_get_working_folder (GfcJob const* self)
{
	g_return_val_if_fail (GFC_IS_JOB (self), NULL);

	return self->_private->working_folder;
}

void
gfc_job_set_out_reader (GfcJob   * self,
			GfcReader* reader)
{
	g_return_if_fail (GFC_IS_JOB (self));

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

