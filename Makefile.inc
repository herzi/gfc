noinst_LTLIBRARIES=libgfc.la
check_PROGRAMS+=check-gfc-reader
TESTS+=check-gfc-reader

libgfc_la_SOURCES=\
	$(gfc_src_dir)/gfc-job.c \
	$(gfc_src_dir)/gfc-job.h \
	$(gfc_src_dir)/gfc-reader.c \
	$(gfc_src_dir)/gfc-reader.h \
	$(NULL)

check_gfc_reader_SOURCES=\
	$(gfc_src_dir)/check-gfc-reader.c \
	$(NULL)

