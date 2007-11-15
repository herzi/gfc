/* This file is part of libgfc
 *
 * AUTHORS
 *     Sven Herzberg
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

#ifndef GFC_WINDOW_H
#define GFC_WINDOW_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _GfcWindow        GfcWindow;
typedef struct _GfcWindowPrivate GfcWindowPrivate;
typedef struct _GfcWindowClass   GfcWindowClass;

#define GFC_TYPE_WINDOW         (gfc_window_get_type ())
#define GFC_WINDOW(i)           (G_TYPE_CHECK_INSTANE_CAST ((i), GFC_TYPE_WINDOW, GfcWindow))
#define GFC_WINDOW_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GFC_TYPE_WINDOW, GfcWindowClass))
#define GFC_IS_WINDOW(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GFC_TYPE_WINDOW))
#define GFC_IS_WINDOW_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), GFC_TYPE_WINDOW))
#define GFC_WINDOW_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), GFC_ZTYPE_WINDOW, GfcWindowClass))

GType      gfc_window_get_type (void);
GtkWidget* gfc_window_new      (void);

struct _GfcWindow {
	GtkWindow         base_instance;
	GfcWindowPrivate* _private;
};

struct _GfcWindowClass {
	GtkWindowClass    base_class;
};

G_END_DECLS

#endif /* !GFC_WINDOW_H */
