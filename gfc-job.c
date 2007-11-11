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
gfc_job_class_init (GfcJobClass* self_class)
{
	GObjectClass* object_class = G_OBJECT_CLASS (self_class);

	object_class->constructed = job_constructed;

	g_type_class_add_private (self_class, sizeof (GfcJobPrivate));
}

