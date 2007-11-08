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

#include <string.h>

#include <gfc-reader.h>
#include <gfc-test.h>
#include <gfc-test-main.h>

enum {
	FD_READ,
	FD_WRITE,
	N_FDS
};

struct GfcTestPipe {
	gint fds[N_FDS];
};

static struct GfcTestPipe test = {
	{0,0}
};

static inline ssize_t
gfc_strwrite (gint         fd,
	      gchar const* string)
{
	write (fd, string, strlen (string) + 1);
}

static gboolean
write_message (gpointer data)
{
	static gint i = 0;

	gfc_strwrite (test.fds[FD_WRITE], "Message\n");
	g_string_append_c (data, 'w');

	return ++i < 10;
}

static void
read_line_cb (GfcReader  * reader,
	      gchar const* line,
	      gpointer     data)
{
	g_string_append_c (data, 'r');
}

static gboolean
first_check (void)
{
	/* prepare */
	GfcReader* reader;
	GMainLoop* loop   = g_main_loop_new (NULL, FALSE);
	gboolean   passed = TRUE;
	GString  * string = g_string_new ("");

	pipe (test.fds);

	reader = gfc_reader_new (test.fds[FD_READ]);

	/* exercise */
	g_signal_connect (reader, "read-line",
			  G_CALLBACK (read_line_cb), string);
	g_idle_add_full (G_PRIORITY_LOW,
			 write_message,
			 string,
			 NULL);
	gfc_test_add_quit_handler (loop);
	g_main_loop_run (loop);

	/* verify */
	g_print ("%s\n", string->str);

	/* cleanup */
	g_string_free (string, TRUE);
	g_main_loop_quit (loop);
	close (test.fds[FD_READ]);
	close (test.fds[FD_WRITE]);
	g_object_unref (reader);

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

