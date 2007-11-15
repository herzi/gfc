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

#include "gfc-window.h"

#include "gfc-drawer.h"

struct _GfcWindowPrivate {
	GfcDrawer* drawer;
};

G_DEFINE_TYPE (GfcWindow, gfc_window, GTK_TYPE_WINDOW);

static void
window_destroy_drawer (GtkObject* drawer,
		       GfcWindow* self)
{
	g_signal_handlers_disconnect_by_func (drawer, window_destroy_drawer, self);
	g_object_unref (drawer);
	self->_private->drawer = NULL;
}

static void
gfc_window_init (GfcWindow* self)
{
	GtkWidget* widget;

	self->_private = G_TYPE_INSTANCE_GET_PRIVATE (self,
						      GFC_TYPE_WINDOW,
						      GfcWindowPrivate);

	widget = gfc_drawer_new (self);
	self->_private->drawer = g_object_ref_sink (widget);
	g_signal_connect (self->_private->drawer, "destroy",
			  G_CALLBACK (window_destroy_drawer), self);
}

static void
window_destroy (GtkObject* object)
{
	GfcWindow* self = GFC_WINDOW (object);

	if (self->_private->drawer) {
		gtk_object_destroy (GTK_OBJECT (self->_private->drawer));
	}

	GTK_OBJECT_CLASS (gfc_window_parent_class)->destroy (object);
}

static void
gfc_window_class_init (GfcWindowClass* self_class)
{
	GtkObjectClass* gtk_object_class = GTK_OBJECT_CLASS (self_class);

	gtk_object_class->destroy = window_destroy;

	g_type_class_add_private (self_class, sizeof (GfcWindowPrivate));
}

GtkWidget*
gfc_window_new (void)
{
	return g_object_new (GFC_TYPE_WINDOW, NULL);
}

