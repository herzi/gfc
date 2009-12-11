# To allow easy embedding into both recursive and non-recursive setups as well
# as a standalone build, we include Makefile.inc here.
#
# Recursive and standalone setups can easily use the Makefile.am while
# non-recursive setups can set $(gfc_src_dir) to the subfolder that contains
# the code and then just include Makefile.inc

check_PROGRAMS=
check_LTLIBRARIES=
noinst_LTLIBRARIES=
noinst_PROGRAMS=gfc-demo
TESTS=

lib_LTLIBRARIES=libgfc.la

pkgconfigdir=$(libdir)/pkgconfig
pkgconfig_DATA=gfc-@MILESTONE@.pc

gfc_HEADERS=\
	gfc.h \
	$(NULL)
gfcdir=$(includedir)/gfc-@MILESTONE@

gfc_demo_SOURCES=\
	demo/main.c \
	$(NULL)
gfc_demo_CPPFLAGS=\
	-I$(top_srcdir) \
	$(libgfc_la_CPPFLAGS) \
	$(NULL)
gfc_demo_LDADD=\
	libgfc.la \
	$(NULL)

CLEANFILES=$(pkgconfig_DATA)

libgfc_ladir=$(gfcdir)/gfc

gfc-@MILESTONE@.pc: gfc.pc Makefile
	cmp -s $< $@ || cp $< $@

AM_CPPFLAGS=$(GFC_CFLAGS)
LDADD=$(GFC_LIBS)

if WITH_VALGRIND
TESTS_ENVIRONMENT=G_SLICE=always-malloc G_DEBUG=gc-friendly $(top_builddir)/libtool --mode=execute valgrind --leak-check=full -q --suppressions=$(srcdir)/glib-2.0.supp
endif

gfc_src_dir=.
include Makefile.inc

EXTRA_DIST=glib-2.0.supp
