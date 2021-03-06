/* This file is part of libgfc
 *
 * AUTHORS
 *     Sven Herzberg  <herzi@gnome-de.org>
 *
 * Copyright (C) 2007  Sven Herzberg
 *
 * This work is provided "as is"; redistribution and modification
 * in whole or in part, in any medium, physical or electronic is
 * permitted without restriction.
 *
 * This work is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * In no event shall the authors or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 */

#include <gfc-test.h>
#include <gfc-test-main.h>

static gboolean
check_glib_main_priorities (void)
{
	/* Objective: this test makes sure that an idle handler with a low
	 * priority doesn't get called before a handler with a higher priority
	 * gets called */
	return TRUE;
}
	
static gboolean
count (gpointer data)
{
	gint* counter = data;

	(*counter)++;

	return *counter < 10;
}

static gboolean
check_gfc_main_quit (void)
{
	/* Objective: this test checks that setting up the quit idle handler
	 * gets executed after the idle handler with the higher priority */

	/* prepare */
	GMainLoop* loop = g_main_loop_new (NULL, FALSE);
	gboolean   passed = TRUE;
	gint       counter = 0;

	gfc_test_add_quit_handler (loop);
	g_idle_add_full (G_PRIORITY_LOW,
			 count,
			 &counter,
			 NULL);

	/* exercise */
	g_main_loop_run (loop);

	/* verify */
	if (counter != 10) {
		g_warning ("%s: counter has an unexpected value: %d (expected %d)",
			   G_STRLOC,
			   counter,
			   10);
		passed = FALSE;
	}

	/* cleanup */
	g_main_loop_unref (loop);

	return passed;
}

int
main (int   argc,
      char**argv)
{
	gboolean passed = TRUE;

	gfc_test_init (&argc, &argv);

	passed &= check_glib_main_priorities ();
	passed &= check_gfc_main_quit ();

	return passed ? 0 : 1;
}

