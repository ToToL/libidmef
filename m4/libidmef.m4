dnl Autoconf macros for libidmef
dnl $id$

# Modified for LIBIDMEF -- Yoann Vandoorselaere
# Modified for LIBGNUTLS -- nmav
# Configure paths for LIBGCRYPT
# Shamelessly stolen from the one of XDELTA by Owen Taylor
# Werner Koch   99-12-09

dnl AM_PATH_LIBIDMEF([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND ]]], THREAD_SUPPORT)
dnl Test for libidmef, and define LIBIDMEF_PREFIX, LIBIDMEF_CFLAGS, LIBIDMEF_PTHREAD_CFLAGS,
dnl LIBIDMEF_LDFLAGS, and LIBIDMEF_LIBS
dnl
AC_DEFUN([AM_PATH_LIBIDMEF],
[dnl
dnl Get the cflags and libraries from the libidmef-config script
dnl
AC_ARG_WITH(libidmef-prefix, AC_HELP_STRING(--with-libidmef-prefix=PFX,
            Prefix where libidmef is installed (optional)),
            libidmef_config_prefix="$withval", libidmef_config_prefix="")

  if test x$libidmef_config_prefix != x ; then
     if test x${LIBIDMEF_CONFIG+set} != xset ; then
        LIBIDMEF_CONFIG=$libidmef_config_prefix/bin/libidmef-config
     fi
  fi

  AC_PATH_PROG(LIBIDMEF_CONFIG, libidmef-config, no)
  if test "$LIBIDMEF_CONFIG" != "no"; then
  	if $($LIBIDMEF_CONFIG --thread > /dev/null 2>&1); then
        	LIBIDMEF_PTHREAD_CFLAGS=`$LIBIDMEF_CONFIG --thread --cflags`

        	if test x$4 = xtrue || test x$4 = xyes; then
                	libidmef_config_args="--thread"
        	else
                	libidmef_config_args="--no-thread"
        	fi
  	else
        	LIBIDMEF_PTHREAD_CFLAGS=`$LIBIDMEF_CONFIG --pthread-cflags`
  	fi
  fi

  min_libidmef_version=ifelse([$1], ,0.1.0,$1)
  AC_MSG_CHECKING(for libidmef - version >= $min_libidmef_version)
  no_libidmef=""
  if test "$LIBIDMEF_CONFIG" = "no" ; then
    no_libidmef=yes
  else
    LIBIDMEF_CFLAGS=`$LIBIDMEF_CONFIG $libidmef_config_args --cflags`
    LIBIDMEF_LDFLAGS=`$LIBIDMEF_CONFIG $libidmef_config_args --ldflags`
    LIBIDMEF_LIBS=`$LIBIDMEF_CONFIG $libidmef_config_args --libs`
    LIBIDMEF_PREFIX=`$LIBIDMEF_CONFIG $libidmef_config_args --prefix`
    LIBIDMEF_CONFIG_PREFIX=`$LIBIDMEF_CONFIG $libidmef_config_args --config-prefix`
    libidmef_config_version=`$LIBIDMEF_CONFIG $libidmef_config_args --version`


      ac_save_CFLAGS="$CFLAGS"
      ac_save_LDFLAGS="$LDFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $LIBIDMEF_CFLAGS"
      LDFLAGS="$LDFLAGS $LIBIDMEF_LDFLAGS"
      LIBS="$LIBS $LIBIDMEF_LIBS"
dnl
dnl Now check if the installed libidmef is sufficiently new. Also sanity
dnl checks the results of libidmef-config to some extent
dnl
      rm -f conf.libidmeftest
      AC_TRY_RUN([
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libidmef/libidmef.h>

int
main ()
{
    system ("touch conf.libidmeftest");

    if( strcmp( libidmef_check_version(NULL), "$libidmef_config_version" ) )
    {
      printf("\n*** 'libidmef-config --version' returned %s, but LIBIDMEF (%s)\n",
             "$libidmef_config_version", libidmef_check_version(NULL) );
      printf("*** was found! If libidmef-config was correct, then it is best\n");
      printf("*** to remove the old version of LIBIDMEF. You may also be able to fix the error\n");
      printf("*** by modifying your LD_LIBRARY_PATH enviroment variable, or by editing\n");
      printf("*** /etc/ld.so.conf. Make sure you have run ldconfig if that is\n");
      printf("*** required on your system.\n");
      printf("*** If libidmef-config was wrong, set the environment variable LIBIDMEF_CONFIG\n");
      printf("*** to point to the correct copy of libidmef-config, and remove the file config.cache\n");
      printf("*** before re-running configure\n");
    }
    else if ( strcmp(libidmef_check_version(NULL), LIBIDMEF_VERSION ) ) {
        printf("\n*** LIBIDMEF header file (version %s) does not match\n", LIBIDMEF_VERSION);
        printf("*** library (version %s)\n", libidmef_check_version(NULL) );
    }
    else {
      if ( libidmef_check_version( "$min_libidmef_version" ) )
        return 0;
      else {
        printf("no\n*** An old version of LIBIDMEF (%s) was found.\n",
                libidmef_check_version(NULL) );
        printf("*** You need a version of LIBIDMEF newer than %s. The latest version of\n",
               "$min_libidmef_version" );
        printf("*** LIBIDMEF is always available from https://www.libidmef-siem.org/project/libidmef/files\n");
        printf("*** \n");
        printf("*** If you have already installed a sufficiently new version, this error\n");
        printf("*** probably means that the wrong copy of the libidmef-config shell script is\n");
        printf("*** being found. The easiest way to fix this is to remove the old version\n");
        printf("*** of LIBIDMEF, but you can also set the LIBIDMEF_CONFIG environment to point to the\n");
        printf("*** correct copy of libidmef-config. (In this case, you will have to\n");
        printf("*** modify your LD_LIBRARY_PATH enviroment variable, or edit /etc/ld.so.conf\n");
        printf("*** so that the correct libraries are found at run-time))\n");
      }
    }
    return 1;
}
],, no_libidmef=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       CFLAGS="$ac_save_CFLAGS"
       LIBS="$ac_save_LIBS"
       LDFLAGS="$ac_save_LDFLAGS"
  fi

  if test "x$no_libidmef" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])
  else
     if test -f conf.libidmeftest ; then
        :
     else
        AC_MSG_RESULT(no)
     fi
     if test "$LIBIDMEF_CONFIG" = "no" ; then
       echo "*** The libidmef-config script installed by LIBIDMEF could not be found"
       echo "*** If LIBIDMEF was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the LIBIDMEF_CONFIG environment variable to the"
       echo "*** full path to libidmef-config."
     else
       if test -f conf.libidmeftest ; then
        :
       else
          echo "*** Could not run libidmef test program, checking why..."
          CFLAGS="$CFLAGS $LIBIDMEF_CFLAGS"
          LDFLAGS="$LDFLAGS $LIBIDMEF_LDFLAGS"
          LIBS="$LIBS $LIBIDMEF_LIBS"
          AC_TRY_LINK([
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libidmef/libidmef.h>
],      [ return !!libidmef_check_version(NULL); ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding LIBIDMEF or finding the wrong"
          echo "*** version of LIBIDMEF. If it is not finding LIBIDMEF, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
          echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"
          echo "***" ],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means LIBIDMEF was incorrectly installed"
          echo "*** or that you have moved LIBIDMEF since it was installed. In the latter case, you"
          echo "*** may want to edit the libidmef-config script: $LIBIDMEF_CONFIG" ])
          CFLAGS="$ac_save_CFLAGS"
          LDFLAGS="$ac_save_LDFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     LIBIDMEF_CFLAGS=""
     LIBIDMEF_LDFLAGS=""
     LIBIDMEF_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  rm -f conf.libidmeftest
  AC_SUBST(LIBIDMEF_CFLAGS)
  AC_SUBST(LIBIDMEF_PTHREAD_CFLAGS)
  AC_SUBST(LIBIDMEF_LDFLAGS)
  AC_SUBST(LIBIDMEF_LIBS)
  AC_SUBST(LIBIDMEF_PREFIX)
  AC_SUBST(LIBIDMEF_CONFIG_PREFIX)

  m4_ifdef([LT_INIT],
           [AC_DEFINE([LIBIDMEF_APPLICATION_USE_LIBTOOL2], [], [Define whether application use libtool >= 2.0])],
           [])

])

dnl *-*wedit:notab*-*  Please keep this as the last line.
