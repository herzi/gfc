noinst_LTLIBRARIES=\
	libgfc.la \
	libgfc-test.la \
	$(NULL)
gfc_tests=\
	check-gfc-main-loop \
	check-gfc-reader \
	$(NULL)

check_PROGRAMS+=$(gfc_tests)
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
	$(NULL)

check_gfc_reader_SOURCES=\
	$(gfc_src_dir)/check-gfc-reader.c \
	$(NULL)
check_gfc_reader_LDADD=\
	libgfc-test.la \
	$(LDADD) \
	$(NULL)

check_gfc_main_loop_SOURCES=\
	$(gfc_src_dir)/check-gfc-main-loop.c \
	$(NULL)

