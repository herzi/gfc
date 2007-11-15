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

#include "gfc-drawer.h"

G_DEFINE_TYPE (GfcDrawer, gfc_drawer, GTK_TYPE_BIN);

static void
gfc_drawer_init (GfcDrawer* self)
{
	GTK_WIDGET_UNSET_FLAGS (self, GTK_NO_WINDOW);
	GTK_WIDGET_SET_FLAGS (self, GTK_TOPLEVEL);

	/* GTK_PRIVATE_SET_FLAG (window, GTK_ANCHORED); */
	GTK_WIDGET(self)->private_flags |= (1 <<  9);
}

static void
drawer_realize (GtkWidget* widget)
{
	GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);
}

static void
drawer_unrealize (GtkWidget* widget)
{
	GTK_WIDGET_UNSET_FLAGS (widget, GTK_REALIZED);
}

static void
gfc_drawer_class_init (GfcDrawerClass* self_class)
{
	GtkWidgetClass* widget_class = GTK_WIDGET_CLASS (self_class);

	widget_class->realize   = drawer_realize;
	widget_class->unrealize = drawer_unrealize;
}

GtkWidget*
gfc_drawer_new (GfcWindow* parent)
{
	return g_object_new (GFC_TYPE_DRAWER,
			     NULL);
}

