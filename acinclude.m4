dnl This file is part of libgfc
dnl
dnl AUTHORS
dnl     Sven Herzberg
dnl
dnl Copyright (C) 2007  Sven Herzberg
dnl
dnl This program is free software; you can redistribute it and/or
dnl modify it under the terms of the GNU Lesser General Public License as
dnl published by the Free Software Foundation; either version 2.1 of the
dnl License, or (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU Lesser General Public License for more details.
dnl
dnl You should have received a copy of the GNU Lesser General Public License
dnl along with this program; if not, write to the Free Software
dnl Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
dnl USA

dnl HERZI_PROG_VALGRIND
AC_DEFUN([HERZI_PROG_VALGRIND],[
	AC_ARG_ENABLE([valgrind],
		      AS_HELP_STRING([--disable-valgrind],[disable callgrind support even if available]),
		      [test_valgrind=$enableval],
		      [test_valgrind=yes])

	if test "x$test_valgrind" = "xyes"; then
		AC_CHECK_PROGS(VALGRIND,[valgrind])

		AC_CHECK_HEADER(valgrind/callgrind.h,
				[have_callgrind_h=1],
				[have_callgrind_h=0])
		AC_DEFINE(HAVE_CALLGRIND_H,[$have_callgrind_h],[Specify whether callgrind is available for test cases])
	fi
	AM_CONDITIONAL(WITH_VALGRIND,[test -n "$VALGRIND"])
])

