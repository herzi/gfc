# To allow easy embedding into both recursive and non-recursive setups as well
# as a standalone build, we include Makefile.inc here.
#
# Recursive and standalone setups can easily use the Makefile.am while
# non-recursive setups can set $(gfc_src_dir) to the subfolder that contains
# the code and then just include Makefile.inc

check_PROGRAMS=
check_LTLIBRARIES=
TESTS=

AM_CPPFLAGS=$(GFC_CFLAGS)
LDADD=$(GFC_LIBS)

if WITH_VALGRIND
TESTS_ENVIRONMENT=G_SLICE=always-malloc G_DEBUG=gc-friendly $(top_builddir)/libtool --mode=execute valgrind --leak-check=full -q --suppressions=$(srcdir)/glib-2.0.supp
endif

gfc_src_dir=.
include Makefile.inc
