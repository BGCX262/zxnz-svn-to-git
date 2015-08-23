bin_PROGRAMS = console test
console_SOURCES = zz-log.c console.c guessnum.c guessnum.h zz-log.h debug.h
test_SOURCES = test.c debug.h zz-log.c zz-log.h
console_LDADD = $(top_builddir)/lib/libexp.a \
	       -L/usr/local/lib -lgobject-2.0 -lglib-2.0 -lreadline -lncurses
console_CPPFLAGS = -I $(top_srcdir)/lib -I/usr/local/include/glib-2.0 -I/usr/local/lib/glib-2.0/include


test_LDADD = $(top_builddir)/lib/libexp.a \
	       -L/usr/local/lib -lgobject-2.0 -lglib-2.0
test_CPPFLAGS = -I $(top_srcdir)/lib -I/usr/local/include/glib-2.0 -I/usr/local/lib/glib-2.0/include
