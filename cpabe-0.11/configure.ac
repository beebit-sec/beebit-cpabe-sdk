dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.61)
AC_INIT([cpabe], [0.11], [bethenco@cs.berkeley.edu])
AC_CONFIG_SRCDIR([common.h])

dnl First, standard system stuff.

dnl  language and compiler support
AC_MSG_CHECKING(whether to enable debugging)
debug_default="no"
AC_ARG_ENABLE(debug, [  --enable-debug=[no/yes]  turn on debugging
                          [default=$debug_default]],, enable_debug=$debug_default)
if test "x$enable_debug" = "xyes"; then
  CFLAGS="-g -Wall"
  LDFLAGS="-g -Wall"
  AC_MSG_RESULT(yes)
else
  CFLAGS="-O3 -Wall"
  LDFLAGS="-O3 -Wall"
  AC_MSG_RESULT(no)
fi
AC_PROG_YACC
AC_PROG_CC
AC_LANG(C)
AC_C_CONST
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

dnl  standard headers
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stddef.h string.h],,
 [AC_MSG_ERROR([could not find all required headers fcntl.h, stddef.h, string.h])])

dnl  specific library functions
AC_FUNC_MALLOC
AC_FUNC_STAT
AC_FUNC_VPRINTF
AC_CHECK_LIB(crypto, SHA1,,
 [AC_MSG_ERROR([please install the OpenSSL crypto library, libcrypto.])])
AC_CHECK_LIB(crypto, EVP_aes_128_cbc,,
 [AC_MSG_ERROR([please install the OpenSSL crypto library, libcrypto.])])
AC_CHECK_FUNCS([strchr strdup memset],,
 [AC_MSG_ERROR([could not link to required functions strchr, strdup, memset])])

dnl Now, we check for specific packages we need.
AM_PATH_GLIB_2_0([2.0.0])
GMP_4_0_CHECK
PBC_CHECK
BSWABE_CHECK

dnl Specify the output.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
