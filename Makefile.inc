# vim:ft=automake:

gfc_tests=\
	check-gfc-main-loop \
	check-gfc-reader \
	$(NULL)

check_PROGRAMS+=$(gfc_tests)
check_LTLIBRARIES+=libgfc-test.la
TESTS+=$(gfc_tests)

libgfc_la_HEADERS=\
	gfc/desktop.h \
	gfc/gtk-window.h \
	gfc/job.h \
	gfc/reader.h \
	gfc/spawn-screen.h \
	gfc/spawn-simple.h \
	gfc/spawn-strategy.h \
	gfc/window.h \
	$(NULL)

libgfc_la_SOURCES=\
	$(libgfc_la_HEADERS) \
	gfc/gtk-window.c \
	gfc/job.c \
	gfc/reader.c \
	gfc/spawn-screen.c \
	gfc/spawn-simple.c \
	gfc/spawn-strategy.c \
	gfc/window.c \
	$(NULL)
libgfc_la_CPPFLAGS=$(GFC_CFLAGS) -I$(srcdir)/$(gfc_src_dir)
libgfc_la_LIBADD=$(GFC_LIBS)
libgfc_la_LDFLAGS=-release $(MILESTONE)

if WITH_GNOME
libgfc_la_SOURCES+=gfc/desktop-gnome.c
endif
if WITH_OSX
libgfc_la_SOURCES+=gfc/desktop-osx.m
endif

libgfc_test_la_SOURCES=\
	$(gfc_src_dir)/gfc-test.c \
	$(gfc_src_dir)/gfc-test.h \
	$(gfc_src_dir)/gfc-test-io.c \
	$(gfc_src_dir)/gfc-test-io.h \
	$(gfc_src_dir)/gfc-test-main.c \
	$(gfc_src_dir)/gfc-test-main.h \
	$(NULL)
libgfc_test_la_CPPFLAGS=$(GFC_CFLAGS) -I$(srcdir)/$(gfc_src_dir)
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

