if HAVE_EASY_BINDINGS

SUBDIRS = include

lib_LTLIBRARIES = libidmefcpp.la
libidmefcpp_ladir = ${prefix}/lib
libidmefcpp_la_SOURCES = \
	libidmef-error.cxx \
	idmef.cxx \
	idmef-class.cxx \
	idmef-criteria.cxx \
	idmef-path.cxx \
	idmef-time.cxx \
	idmef-value.cxx

libidmefcpp_la_LDFLAGS = -no-undefined -version-info @LIBIDMEFCPP_SONAME@
libidmefcpp_la_LIBADD  = $(top_builddir)/src/.libs/libidmef.la
libidmefcpp_la_CPPFLAGS = -I$(top_builddir) -I$(top_builddir)/src/include -I$(top_srcdir)/src/include -I$(top_builddir)/src/libidmef-error -I$(top_builddir)/bindings/c++/include -I$(top_srcdir)/bindings/c++/include 

endif

-include $(top_srcdir)/git.mk
