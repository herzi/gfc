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

#include <gdk/quartz/gdkquartz.h>
#include <gdk/quartz/GdkQuartzView.h>

struct _GfcDrawerPrivate {
	GfcWindow* window;
	NSDrawer * drawer;
};

enum {
	PROP_0,
	PROP_WINDOW
};

G_DEFINE_TYPE (GfcDrawer, gfc_drawer, GTK_TYPE_BIN);

static void
gfc_drawer_init (GfcDrawer* self)
{
	self->_private = G_TYPE_INSTANCE_GET_PRIVATE (self,
						      GFC_TYPE_DRAWER,
						      GfcDrawerPrivate);

	GTK_WIDGET_UNSET_FLAGS (self, GTK_NO_WINDOW);
	GTK_WIDGET_SET_FLAGS (self, GTK_TOPLEVEL);

	/* GTK_PRIVATE_SET_FLAG (window, GTK_ANCHORED); */
	GTK_WIDGET(self)->private_flags |= (1 <<  9);
}

static void
drawer_dispose (GObject* object)
{
	GfcDrawer* self = GFC_DRAWER (object);

	if (self->_private->window) {
		g_object_unref (self->_private->window);
		self->_private->window = NULL;
	}

	G_OBJECT_CLASS (gfc_drawer_parent_class)->dispose (object);
}

static void
drawer_get_property (GObject   * object,
		     guint       prop_id,
		     GValue    * value,
		     GParamSpec* pspec)
{
	GfcDrawer* self = GFC_DRAWER (object);

	switch (prop_id) {
	case PROP_WINDOW:
		g_value_set_object (value, self->_private->window);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
drawer_set_property (GObject     * object,
		     guint         prop_id,
		     GValue const* value,
		     GParamSpec  * pspec)
{
	GfcDrawer* self = GFC_DRAWER (object);

	switch (prop_id) {
	case PROP_WINDOW:
		self->_private->window = g_value_dup_object (value);
		g_object_notify (object, "window");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
drawer_realize (GtkWidget* widget)
{
	GfcDrawer* self = GFC_DRAWER (widget);
	NSView   * view_window;

	g_return_if_fail (GFC_IS_WINDOW (self->_private->window));
	g_return_if_fail (GTK_WIDGET_REALIZED (self->_private->window));
	g_return_if_fail (!self->_private->drawer);

	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

	view_window = gdk_quartz_window_get_nsview (GTK_WIDGET (self->_private->window)->window);
	self->_private->drawer = [[NSDrawer alloc] initWithContentSize:NSMakeSize (100,100)
						   preferredEdge:NSMinXEdge];
	[self->_private->drawer setParentWindow:[view_window window]];

	[pool release];

	GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);
}

static void
drawer_unrealize (GtkWidget* widget)
{
	GfcDrawer* self = GFC_DRAWER (widget);

	[self->_private->drawer release];
	self->_private->drawer = NULL;

	GTK_WIDGET_UNSET_FLAGS (widget, GTK_REALIZED);
}

static void
gfc_drawer_class_init (GfcDrawerClass* self_class)
{
	GObjectClass  * object_class = G_OBJECT_CLASS (self_class);
	GtkWidgetClass* widget_class = GTK_WIDGET_CLASS (self_class);

	object_class->dispose      = drawer_dispose;
	object_class->get_property = drawer_get_property;
	object_class->set_property = drawer_set_property;

	g_object_class_install_property (object_class, PROP_WINDOW,
					 g_param_spec_object ("window", "window", "window",
							      GFC_TYPE_WINDOW, G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

	widget_class->realize   = drawer_realize;
	widget_class->unrealize = drawer_unrealize;

	g_type_class_add_private (self_class, sizeof (GfcDrawerPrivate));
}

GtkWidget*
gfc_drawer_new (GfcWindow* parent)
{
	return g_object_new (GFC_TYPE_DRAWER,
			     "window", parent,
			     NULL);
}

