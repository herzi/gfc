/* This file is part of libgfc
 *
 * AUTHORS
 *     Sven Herzberg  <sven@imendio.com>
 *
 * Copyright (C) 2007, 2008  Sven Herzberg
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

#ifndef GFC_JOB_H
#define GFC_JOB_H

#include "gfc-reader.h"

G_BEGIN_DECLS

typedef struct _GfcJob        GfcJob;
typedef struct _GfcJobPrivate GfcJobPrivate;
typedef struct _GfcJobClass   GfcJobClass;

#define GFC_TYPE_JOB         (gfc_job_get_type ())
#define GFC_JOB(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), GFC_TYPE_JOB, GfcJob))
#define GFC_JOB_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GFC_TYPE_JOB, GfcJobClass))
#define GFC_IS_JOB(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GFC_TYPE_JOB))
#define GFC_IS_JOB_CLASS(i)  (G_TYPE_CHECK_CLASS_TYPE ((c), GFC_TYPE_JOB))
#define GFC_JOB_GET_CLASS(c) (G_TYPE_INSTANCE_GET_CLASS ((i), GFC_TYPE_JOB, GfcJobClass))

GType        gfc_job_get_type           (void);
gchar**      gfc_job_get_argv           (GfcJob const* self);
gchar const* gfc_job_get_command        (GfcJob const* self);
GfcReader*   gfc_job_get_err_reader     (GfcJob const* self);
gboolean     gfc_job_get_exited         (GfcJob const* self);
GfcReader*   gfc_job_get_out_reader     (GfcJob const* self);
GPid         gfc_job_get_pid            (GfcJob const* self);
gint         gfc_job_get_return_code    (GfcJob const* self);
gchar const* gfc_job_get_working_folder (GfcJob const* self);
gboolean     gfc_job_kill               (GfcJob      * self);
GfcJob*      gfc_job_new                (gchar const * working_folder,
					 gchar const * command);
#ifndef FIXME_HIDE_PRIVATE_APIS
void         gfc_job_set_err_reader     (GfcJob      * self,
					 GfcReader   * reader);
void         gfc_job_set_exited         (GfcJob      * self,
					 gboolean      exited);
void         gfc_job_set_out_reader     (GfcJob      * self,
					 GfcReader   * reader);
void         gfc_job_set_pid            (GfcJob      * self,
					 GPid          pid);
void         gfc_job_set_return_code    (GfcJob      * self,
					 gint          return_code);
#endif

struct _GfcJob {
	GObject        base_instance;
	GfcJobPrivate* _private;
};

struct _GfcJobClass {
	GObjectClass   base_class;
};

G_END_DECLS

#endif /* !GFC_JOB_H */
