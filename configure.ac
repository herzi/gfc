AC_INIT(gfc,0.0.4,mailto:herzi@gnome-de.org)
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

MILESTONE=0.2
AC_SUBST(MILESTONE)

CXX=no
F77=no

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_LIBTOOL
HERZI_PROG_VALGRIND

dnl FIXME: split gdk stuff into libgfc-ui
PKG_CHECK_MODULES(GFC,[glib-2.0 gobject-2.0 gtk+-2.0])

gfc_has_gconf=
PKG_CHECK_MODULES(GCONF,[gconf-2.0],[gfc_has_gconf=yes],[gfc_has_gconf=no])
AM_CONDITIONAL(WITH_GNOME,[test "x$gfc_has_gconf" = "xyes"])
AM_CONDITIONAL(WITH_OSX,[test "x$gfc_has_gconf" != "xyes"])

if test "x${gfc_has_gconf}" != "xyes"; then
	AC_PROG_OBJC

	PLATFORM_CFLAGS=
	PLATFORM_LIBS="-framework AppKit"
	AC_SUBST(PLATFORM_CFLAGS)
	AC_SUBST(PLATFORM_LIBS)
else
	GFC_CFLAGS="$GFC_CFLAGS $GCONF_CFLAGS"
	GFC_LIBS="$GFC_LIBS $GCONF_LIBS"
	AC_SUBST(GFC_CFLAGS)
	AC_SUBST(GFC_LIBS)

	OBJC='$(CC)'
	AC_SUBST(OBJC)
	AM_CONDITIONAL(am__fastdepOBJC,true)
fi

AC_OUTPUT([Makefile
	   gfc.pc])
