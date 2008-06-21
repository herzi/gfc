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

#include "ct-control-string.h"

#include <gtk/gtkentry.h>
#include <gtk/gtklabel.h>

G_DEFINE_TYPE (CtControlString, ct_control_string, CT_TYPE_CONTROL);

static void
entry_changed_cb (GtkEntry * entry,
		  CtControl* control)
{
	g_object_set (ct_control_get_subject (control),
		      g_param_spec_get_name (ct_control_get_pspec (control)),
		      gtk_entry_get_text (entry),
		      NULL);
}

static void
ct_control_string_init (CtControlString* self)
{
	GtkWidget* label   = gtk_label_new (NULL);
	GtkWidget* control = gtk_entry_new ();

	ct_control_set_widget (CT_CONTROL (self),
			       control);
	ct_control_set_label  (CT_CONTROL (self),
			       label);

	g_signal_connect (control, "changed",
			  G_CALLBACK (entry_changed_cb), self);
}

static void
control_string_value_changed (CtControl* control,
			      GValue   * value)
{
	gtk_entry_set_text (GTK_ENTRY (ct_control_get_widget (control)),
			    g_value_get_string (value));
}

static void
ct_control_string_class_init (CtControlStringClass* self_class)
{
	CtControlClass* control_class = CT_CONTROL_CLASS (self_class);

	control_class->value_changed = control_string_value_changed;
}

