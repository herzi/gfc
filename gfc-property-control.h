/* This file is part of libgfc
 *
 * AUTHORS
 *     Sven Herzberg  <sven@imendio.com>
 *
 * Copyright (C) 2008  Sven Herzberg
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

#ifndef GFC_PROPERTY_CONTROL_H
#define GFC_PROPERTY_CONTROL_H

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _GfcPropertyControl        GfcPropertyControl;
typedef struct _GfcPropertyControlPrivate GfcPropertyControlPrivate;
typedef struct _GfcPropertyControlClass   GfcPropertyControlClass;

#define GFC_TYPE_PROPERTY_CONTROL         (gfc_property_control_get_type ())
#define GFC_PROPERTY_CONTROL(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), GFC_TYPE_PROPERTY_CONTROL, GfcPropertyControl))
#define GFC_PROPERTY_CONTROL_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GFC_TYPE_PROPERTY_CONTROL, GfcPropertyControlClass))
#define GFC_IS_PROPERTY_CONTROL(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GFC_TYPE_PROPERTY_CONTROL))
#define GFC_IS_PROPERTY_CONTROL_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), GFC_TYPE_PROPERTY_CONTROL))
#define GFC_PROPERTY_CONTROL_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), GFC_TYPE_PROPERTY_CONTROL, GfcPropertyControlClass))

GType gfc_property_control_get_type (void);

enum GfcParamFlags {
	GFC_PARAM_VISIBLE = 1 << G_PARAM_USER_SHIFT
};

struct _GfcPropertyControl {
	/* FIXME: turn into a GtkWidget with get_label() or into an interface */
	GObject                    base_instance;
	GfcPropertyControlPrivate* _private;
};

struct _GfcPropertyControlClass {
	GObjectClass               base_class;
};

G_END_DECLS

#endif /* !GFC_PROPERTY_CONTROL_H */
