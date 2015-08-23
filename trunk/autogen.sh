#!/bin/sh
# Run this to generate all the initial makefiles, etc.

aclocal  
libtoolize --automake

touch AUTHORS
touch COPYING
touch ChangeLog
touch INSTALL
touch NEWS
touch README

automake -a
autoconf

