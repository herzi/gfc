/* This file is part of libgfc
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

#include "gfc-test.h"

#include <stdio.h>

static gboolean   initialized = FALSE;
static GPrintFunc print_func = NULL;

static void
gfc_test_print (gchar const* string)
{
	if (print_func) {
		gchar* message = g_strdup_printf ("%s: %s",
						  g_get_prgname (),
						  string);
		print_func (message);
		g_free (message);
	} else {
		printf ("%s: %s",
			g_get_prgname (),
			string);
	}
}

void
gfc_test_init (gint*   argc,
	       gchar***argv)
{
	if (G_UNLIKELY (initialized)) {
		return;
	}

	g_set_prgname ((*argv)[0]);

	print_func = g_set_print_handler (gfc_test_print);
}

