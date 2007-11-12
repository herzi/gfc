/* This file is part of libgfc
 *
 * AUTHORS
 *     Sven Herzberg  <set the EMAIL_ADDRESS environment variable>
 *
 * Copyright (C) 2007  Sven Herzberg
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
	GfcJobState  state;
	gchar      **argv;
};

enum {
	PROP_0,
	PROP_ARGV
};

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

	g_strfreev (self->_private->argv);

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

