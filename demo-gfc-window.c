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

#include <gtk/gtk.h>
#include <gfc.h>

static void
button_clicked (GtkWidget* button,
		GtkWidget* window)
{
	gfc_window_toggle_sidebar (GFC_WINDOW (window));
}

int
main (int   argc,
      char**argv)
{
	GtkWidget* window;
	GtkWidget* button;

	gtk_init (&argc, &argv);

	window = gfc_window_new ();
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	button = gtk_button_new_with_label ("Toggle Sidebar");
	g_signal_connect (button, "clicked",
			  G_CALLBACK (button_clicked), window);
	gtk_widget_show (button);
	gtk_container_add (GTK_CONTAINER (window),
			   button);
	gtk_widget_show (window);
	gtk_main ();

	return 0;
}

