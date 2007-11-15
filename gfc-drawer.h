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

#ifndef GFC_DRAWER_H
#define GFC_DRAWER_H

#include <gfc-window.h>

G_BEGIN_DECLS

typedef struct _GfcDrawer        GfcDrawer;
typedef struct _GfcDrawerPrivate GfcDrawerPrivate;
typedef struct _GfcDrawerClass   GfcDrawerClass;

#define GFC_TYPE_DRAWER         (gfc_drawer_get_type ())
#define GFC_DRAWER(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), GFC_TYPE_DRAWER, GfcDrawer))
#define GFC_DRAWER_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GFC_TYPE_DRAWER, GfcDrawerClass))
#define GFC_IS_DRAWER(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), GFC_TYPE_DRAWER))
#define GFC_IS_DRAWER_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), GFC_TYPE_DRAWER))
#define GFC_DRAWER_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), GFC_TYPE_DRAWER, GfcDrawerClass))

GType      gfc_drawer_get_type (void);
GtkWidget* gfc_drawer_new      (GfcWindow* parent);
void       gfc_drawer_open     (GfcDrawer* self);
void       gfc_drawer_close    (GfcDrawer* self);

struct _GfcDrawer {
	GtkBin            base_instance;
	GfcDrawerPrivate* _private;
};

struct _GfcDrawerClass {
	GtkBinClass       base_class;
};

G_END_DECLS

#endif /* !GFC_DRAWER_H */
