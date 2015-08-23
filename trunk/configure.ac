dnl Process this file with autoconf to produce a configure script
AC_PREREQ(2.53)
AC_INIT(app)
AM_INIT_AUTOMAKE(zxnz, 0.1.00)
AC_PROG_CC

dnl Checks for libraries.
AC_CHECK_FUNC(sin,[],LIBS=-lm)
AC_CHECK_LIB(ncurses,tparm,TERMLIB=-lncurses,
	       AC_CHECK_LIB(termcap,tgetent,TERMLIB=-ltermcap))
saved_LIBS="$LIBS"
LIBS="$LIBS $TERMLIB"
AC_CHECK_LIB(readline,readline,
	       [AC_CHECK_HEADER(readline/readline.h,
		  LIBS="$saved_LIBS -lreadline $TERMLIB";DEFIS="$DEFIS -DREADLINE")],
		    LIBS="$saved_LIBS")

AC_CHECK_LIB(glib-2.0, g_free,[],AC_MSG_ERROR("glib-2.0 not found"))
AC_CHECK_LIB(expat, XML_ParserCreate, [],AC_MSG_ERROR("Expat library not found. You may need to use the --with-expat-lib\[=path\] command line switch to specify which directory the expat libraries are located"))


AC_PROG_RANLIB
AC_OUTPUT(app/Makefile lib/Makefile Makefile)
