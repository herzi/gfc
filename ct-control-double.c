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

#include "ct-control-double.h"

#include <gtk/gtklabel.h>
#include <gtk/gtkspinbutton.h>

G_DEFINE_TYPE (CtControlDouble, ct_control_double, CT_TYPE_CONTROL);

static void
spin_button_value_changed_cb (GtkSpinButton* spin,
			      CtControl    * control)
{
	g_object_set (ct_control_get_subject (control),
		      g_param_spec_get_name (ct_control_get_pspec (control)),
		      gtk_spin_button_get_value (spin),
		      NULL);
}

static void
ct_control_double_init (CtControlDouble* self)
{
	GtkWidget* spin = gtk_spin_button_new_with_range (-G_MAXDOUBLE, G_MAXDOUBLE, 1.0);
	gtk_spin_button_set_digits (GTK_SPIN_BUTTON (spin),
				    3);
	ct_control_set_widget (CT_CONTROL (self),
			       spin);
	ct_control_set_label  (CT_CONTROL (self),
			       gtk_label_new (NULL));

	g_signal_connect (ct_control_get_widget (CT_CONTROL (self)),
			  "value-changed",
			  G_CALLBACK (spin_button_value_changed_cb),
			  self);
}

static void
control_double_value_changed (CtControl* control,
			      GValue   * value)
{
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (ct_control_get_widget (control)),
				   g_value_get_double (value));
}

static void
ct_control_double_class_init (CtControlDoubleClass* self_class)
{
	CtControlClass* control_class = CT_CONTROL_CLASS (self_class);

	control_class->value_changed = control_double_value_changed;
}

