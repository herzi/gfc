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

enum {
	FD_READ,
	FD_WRITE,
	N_FDS
};

struct GfcTestPipe {
	gint fds[N_FDS];
};

static gboolean
first_check (void)
{
	struct GfcTestPipe test = {
		{0,0}
	};
	pipe (test.fds);

	;

	close (test.fds[FD_READ]);
	close (test.fds[FD_WRITE]);
	return TRUE;
}

int
main (int   argc,
      char**argv)
{
	gboolean passed = TRUE;

	g_type_init ();

	passed &= first_check ();
	
	return passed ? 0 : 1;
}

