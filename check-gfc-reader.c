/* This file is part of libgfc
 *
 * AUTHORS
 *     Sven Herzberg
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

#include <gfc-reader.h>
#include <gfc-test.h>

enum {
	FD_READ,
	FD_WRITE,
	N_FDS
};

struct GfcTestPipe {
	gint fds[N_FDS];
};

static gboolean
count (gpointer data)
{
	gint* counter = data;

	(*counter)++;

	return *counter < 10;
}

static gboolean
close_on_idle (gpointer data)
{
	g_main_loop_quit (data);
	return FALSE;
}

static gboolean
first_check (void)
{
	/* prepare */
	struct GfcTestPipe test = {
		{0,0}
	};
	gint counter = 0;
	gboolean passed = TRUE;
	GMainLoop* loop = g_main_loop_new (NULL, FALSE);

	pipe (test.fds);

	/* exercise */
	g_idle_add_full (G_PRIORITY_DEFAULT_IDLE,
			 count,
			 &counter,
			 NULL);
	g_idle_add_full (G_MAXINT,
			 close_on_idle,
			 loop,
			 NULL);
	g_main_loop_run (loop);

	/* verify */
	g_print ("counter: %d\n", counter);

	/* cleanup */
	g_main_loop_quit (loop);
	close (test.fds[FD_READ]);
	close (test.fds[FD_WRITE]);

	return passed;
}

int
main (int   argc,
      char**argv)
{
	gboolean passed = TRUE;

	gfc_test_init (&argc, &argv);
	g_type_init ();

	passed &= first_check ();
	
	return passed ? 0 : 1;
}

