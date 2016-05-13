SUBDIRS = libidmef-error include

AM_CPPFLAGS = @PCFLAGS@ -I$(srcdir)/include -I$(top_builddir) -I$(top_builddir)/src/include -I$(srcdir)/libidmef-error \
-I$(top_builddir)/libmissing -I$(top_srcdir)/libmissing $(LTDLINCL) @LIBIDMEF_CFLAGS@ @LIBGCRYPT_CFLAGS@ 

pkgconfigdir = $(libdir)/pkgconfig

libidmefincludedir = $(includedir)/
libidmef_la_LIBADD = @LIBIDMEF_LIBS@ $(LIBLTDL) $(top_builddir)/libmissing/libmissing.la libidmef-error/libidmef-error.la
libidmef_la_LDFLAGS = $(GETADDRINFO_LIB) $(GETHOSTNAME_LIB) $(HOSTENT_LIB) $(INET_NTOP_LIB) $(INET_PTON_LIB) $(LIBSOCKET) $(LIB_POLL) $(LIB_SELECT) $(LTLIBINTL) $(LTLIBTHREAD) $(SERVENT_LIB) -no-undefined -version-info @LIBIDMEF_SONAME@ -export-symbols-regex "^(idmef|_?prelude)_"
lib_LTLIBRARIES = libidmef.la
BUILT_SOURCES = $(LTDLDEPS) 

AM_YFLAGS = -d
LEX_OUTPUT_ROOT = lex.yy

libidmef_la_SOURCES = 		\
	common.c			\
	ntp.c				\
	variable.c			\
	prelude-hash.c			\
	prelude-ident.c			\
	prelude-io.c			\
	prelude-log.c			\
	prelude-string.c		\
	idmef-additional-data.c		\
	idmef-class.c			\
	idmef-criteria.c		\
	idmef-criteria-string.yac.y	\
	idmef-criteria-string.lex.l	\
	idmef-criterion-value.c		\
	idmef-data.c			\
	idmef-message-helpers.c		\
	idmef-message-read-json.c		\
	idmef-message-print.c		\
	idmef-message-print-json.c		\
	idmef-message-write.c		\
	idmef-object.c			\
	idmef-path.c			\
	idmef-time.c			\
	idmef-tree-wrap.c		\
	idmef-value.c			\
	idmef-value-type.c		

-include $(top_srcdir)/git.mk
