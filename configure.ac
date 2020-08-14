#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Fibonacci number], [1.0.0], [https://github.com/solnone/fibonacci])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11 -Wall])
# Checks for programs.
AC_PROG_CC

AC_LANG(C++)
AC_PROG_CXX

# Checks for libraries.

AC_CHECK_LIB([gmp], [__gmpz_init])
# AC_CHECK_LIB([gmpxx], [__gmpz_init])

# PKG_CHECK_MODULES([GMP], [gmp >= 6.0])
# PKG_CHECK_MODULES([GMPXX], [gmpxx >= 6.0])
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.3.0  gthread-2.0])

# Checks for header files.
AC_CHECK_HEADERS([limits.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile scripts/Makefile tests/Makefile])
AC_OUTPUT
