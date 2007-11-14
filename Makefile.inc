noinst_LTLIBRARIES=\
	libgfc.la \
	$(NULL)
gfc_tests=\
	check-gfc-main-loop \
	check-gfc-reader \
	$(NULL)

noinst_PROGRAMS+=demo-gfc-window
check_PROGRAMS+=$(gfc_tests)
check_LTLIBRARIES+=libgfc-test.la
TESTS+=$(gfc_tests)

libgfc_la_SOURCES=\
	$(gfc_src_dir)/gfc-job.c \
	$(gfc_src_dir)/gfc-job.h \
	$(gfc_src_dir)/gfc-reader.c \
	$(gfc_src_dir)/gfc-reader.h \
	$(NULL)

libgfc_test_la_SOURCES=\
	$(gfc_src_dir)/gfc-test.c \
	$(gfc_src_dir)/gfc-test.h \
	$(gfc_src_dir)/gfc-test-io.c \
	$(gfc_src_dir)/gfc-test-io.h \
	$(gfc_src_dir)/gfc-test-main.c \
	$(gfc_src_dir)/gfc-test-main.h \
	$(NULL)

check_gfc_reader_SOURCES=\
	$(gfc_src_dir)/check-gfc-reader.c \
	$(NULL)
check_gfc_reader_LDADD=\
	libgfc.la \
	libgfc-test.la \
	$(LDADD) \
	$(NULL)

check_gfc_main_loop_SOURCES=\
	$(gfc_src_dir)/check-gfc-main-loop.c \
	$(NULL)
check_gfc_main_loop_LDADD=\
	libgfc-test.la \
	$(LDADD) \
	$(NULL)

demo_gfc_window_SOURCES=\
	$(gfc_src_dir)/demo-gfc-window.c \
	$(NULL)
