/* This file is part of cairo tree
 *
 * AUTHORS
 *     Sven Herzberg  <herzi@gnome-de.org>
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

#include "ct-control-bool.h"

#include <gtk/gtklabel.h>
#include <gtk/gtkcheckbutton.h>

struct _CtControlBoolPrivate {
	GtkWidget * widget;
};

enum {
	PROP_0
};

G_DEFINE_TYPE (CtControlBool, ct_control_bool, CT_TYPE_CONTROL);

static inline GParamSpec*
control_bool_get_pspec (CtControlBool* self)
{
	return ct_control_get_pspec (CT_CONTROL (self));
}

static void
control_bool_toggled (GtkToggleButton* button,
		      gpointer         data)
{
	CtControlBool* self = CT_CONTROL_BOOL (data);

	g_object_set (ct_control_get_subject (CT_CONTROL (self)),
		      g_param_spec_get_name (control_bool_get_pspec (self)),
		      gtk_toggle_button_get_active (button),
		      NULL);
}

static void
control_bool_release_label (GtkWidget* widget)
{
	gtk_widget_destroy (widget);
	g_object_unref (widget);
}

static void
ct_control_bool_init (CtControlBool* self)
{
	GtkWidget* label;
	GtkWidget* widget;

	self->_private = G_TYPE_INSTANCE_GET_PRIVATE (self,
						      CT_TYPE_CONTROL_BOOL,
						      CtControlBoolPrivate);

	widget = gtk_check_button_new ();
	g_signal_connect (widget, "toggled",
			  G_CALLBACK (control_bool_toggled), self);
	self->_private->widget = widget;

	ct_control_set_widget (CT_CONTROL (self),
			       widget);

	label = gtk_label_new (NULL);
	gtk_widget_show   (label);
	gtk_container_add (GTK_CONTAINER (widget),
			   label);

	ct_control_set_label (CT_CONTROL (self),
			      label);
}

static void
control_bool_dispose (GObject* object)
{
	CtControlBool* self = CT_CONTROL_BOOL (object);

	gtk_widget_destroy (ct_control_get_widget (CT_CONTROL (self)));

	G_OBJECT_CLASS (ct_control_bool_parent_class)->dispose (object);
}

static void
control_bool_set_property (GObject     * object,
			   guint         prop_id,
			   GValue const* value,
			   GParamSpec  * pspec)
{
	CtControlBool* self = CT_CONTROL_BOOL (object);

	switch (prop_id) {
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object,
						   prop_id,
						   pspec);
		break;
	}
}

static void
control_bool_value_changed (CtControl* control,
			    GValue   * value)
{
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (ct_control_get_widget (control)),
				      g_value_get_boolean (value));
}

static void
ct_control_bool_class_init (CtControlBoolClass* self_class)
{
	GObjectClass   * object_class  = G_OBJECT_CLASS (self_class);
	CtControlClass * control_class = CT_CONTROL_CLASS (self_class);

	object_class->dispose      = control_bool_dispose;
	object_class->set_property = control_bool_set_property;

	control_class->value_changed = control_bool_value_changed;

	g_type_class_add_private (self_class, sizeof (CtControlBoolPrivate));
}

