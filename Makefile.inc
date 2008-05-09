# vim:ft=automake:

noinst_LTLIBRARIES+=\
	libgfc.la \
	$(NULL)
gfc_tests=\
	check-gfc-main-loop \
	check-gfc-reader \
	$(NULL)

check_PROGRAMS+=$(gfc_tests)
check_LTLIBRARIES+=libgfc-test.la
TESTS+=$(gfc_tests)

libgfc_la_SOURCES=\
	$(gfc_src_dir)/gfc-job.c \
	$(gfc_src_dir)/gfc-job.h \
	$(gfc_src_dir)/gfc-reader.c \
	$(gfc_src_dir)/gfc-reader.h \
	$(gfc_src_dir)/gfc-desktop.h \
	$(NULL)
libgfc_la_CPPFLAGS=$(GFC_CFLAGS)
libgfc_la_LIBADD=$(GFC_LIBS)

if WITH_GNOME
libgfc_la_SOURCES+=$(gfc_src_dir)/gfc-desktop-gnome.c
endif
if WITH_OSX
libgfc_la_SOURCES+=$(gfc_src_dir)/gfc-desktop-osx.c
endif

libgfc_test_la_SOURCES=\
	$(gfc_src_dir)/gfc-test.c \
	$(gfc_src_dir)/gfc-test.h \
	$(gfc_src_dir)/gfc-test-io.c \
	$(gfc_src_dir)/gfc-test-io.h \
	$(gfc_src_dir)/gfc-test-main.c \
	$(gfc_src_dir)/gfc-test-main.h \
	$(NULL)
libgfc_test_la_CPPFLAGS=$(GFC_CFLAGS)
libgfc_test_la_LIBADD=$(GFC_LIBS)

check_gfc_reader_SOURCES=\
	$(gfc_src_dir)/check-gfc-reader.c \
	$(NULL)
check_gfc_reader_CPPFLAGS=$(GFC_CFLAGS) -I$(srcdir)/$(gfc_src_dir)
check_gfc_reader_LDADD=\
	libgfc.la \
	libgfc-test.la \
	$(GFC_LIBS) \
	$(NULL)

check_gfc_main_loop_SOURCES=\
	$(gfc_src_dir)/check-gfc-main-loop.c \
	$(NULL)
check_gfc_main_loop_CPPFLAGS=$(GFC_CFLAGS) -I$(srcdir)/$(gfc_src_dir)
check_gfc_main_loop_LDADD=\
	libgfc-test.la \
	$(GFC_LIBS) \
	$(NULL)

