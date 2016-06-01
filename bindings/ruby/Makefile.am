if HAVE_EASY_BINDINGS
if HAVE_RUBY

swigdatadir = @SWIG_DATA_DIR@/ruby
dist_swigdata_DATA = libidmefcpp-ruby.i

EXTRA_DIST = libidmefcpp-ruby.i LibIdmef.cxx

rbexec_LTLIBRARIES = LibIdmef.la
LibIdmef_la_CPPFLAGS = $(RUBY_INCLUDES) $(RUBY_CCFLAGS) -I@top_builddir@ -I$(top_srcdir)/src/include -I$(top_builddir)/src/include -I@top_builddir@/src/libidmef-error -I$(top_srcdir)/bindings/c++/include
LibIdmef_la_LDFLAGS = -module -avoid-version
LibIdmef_la_LIBADD = $(top_builddir)/bindings/c++/.libs/libidmefcpp.la $(RUBY_LIBS)
nodist_LibIdmef_la_SOURCES = LibIdmef.cxx

LibIdmef.cxx: $(top_srcdir)/bindings/c++/include/*.hxx $(top_srcdir)/bindings/libidmefcpp.i libidmefcpp-ruby.i 
if HAVE_SWIG
	$(SWIG) -c++ -DSWIG_COMPILE_LIBIDMEF -I$(top_srcdir)/bindings -I$(top_srcdir)/bindings/c++/include -I$(top_srcdir)/src/include -I$(top_srcdir)/src/libidmef-error -ruby -o $@ $(top_srcdir)/bindings/libidmefcpp.i
endif

endif
endif

-include $(top_srcdir)/git.mk
