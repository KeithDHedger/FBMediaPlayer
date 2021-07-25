#
#
AC_INIT([FBMediaPlayer],[0.2.1],[PROJ],[FBMediaPlayer])

AC_CONFIG_HEADER([config.h])
AC_PROG_CXX

AM_INIT_AUTOMAKE

AC_PROG_CC
AC_HEADER_STDC

AC_CONFIG_MACRO_DIR([./localm4s])

AC_SUBST(CFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)

CURSESTOOLKIT_MODULES="cursestoolkit >= 3.0.0"
PKG_CHECK_MODULES(CURSESTOOLKIT, $CURSESTOOLKIT_MODULES)
AC_SUBST(CURSESTOOLKIT_CFLAGS)
AC_SUBST(CURSESTOOLKIT_LIBS)

#IMAGEMAGICK_MODULES="Magick++ >= 7.0.0"
#PKG_CHECK_MODULES(IMAGEMAGICK,$IMAGEMAGICK_MODULES)
#AC_SUBST(IMAGEMAGICK_CFLAGS)
#AC_SUBST(IMAGEMAGICK_LIBS)

AX_BOOST_BASE([1.63],, [AC_MSG_ERROR([FBMediaPlayer needs Boost, but it was not found in your system])])
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM

AC_MSG_CHECKING(whether to build debug functions)
AC_ARG_ENABLE(debug,AS_HELP_STRING([--enable-debug],[Enable debug code]),
    [enable_debug=$enableval],
    [enable_debug="no"])
AC_MSG_RESULT($enable_debug)
if test "$enable_debug" = "yes"; then
	USEDEBUG="-D_DEBUGCODEFB_"
	AC_SUBST(USEDEBUG)
fi

AC_MSG_CHECKING(whether to warn about debug functions)
AC_ARG_ENABLE(warn-debug,AS_HELP_STRING([--enable-warn-debug],[Enable warn debug code]),
    [enable_warn_debug=$enableval],
    [enable_warn_debug="no"])
AC_MSG_RESULT($enable_warn_debug)

if test "$enable_warn_debug" = "yes"; then
	WARNDEBUG="-D_WARN_ENABLEDEBUGFB_"
	AC_SUBST(WARNDEBUG)
fi

AC_OUTPUT(Makefile FBMediaPlayer/app/Makefile)


