AC_INIT(autotool,0.0.1,mailto:herzi@gnome-de.org)
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

CXX=no
F77=no

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_LIBTOOL
HERZI_PROG_VALGRIND

PKG_CHECK_MODULES(GFC,[glib-2.0 gobject-2.0])

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
fi

AC_OUTPUT(Makefile)
