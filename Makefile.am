# To allow easy embedding into both recursive and non-recursive setups as well
# as a standalone build, we include Makefile.inc here.
#
# Recursive and standalone setups can easily use the Makefile.am while
# non-recursive setups can set $(gfc_src_dir) to the subfolder that contains
# the code and then just include Makefile.inc

AM_CPPFLAGS=$(GFC_CFLAGS)
LDADD=$(GFC_LIBS)

gfc_src_dir = .
include Makefile.inc
