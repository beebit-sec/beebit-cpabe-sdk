dnl Check for GNU MP (at least version 4.0) and set GMP_CFLAGS and
dnl GMP_LIBS appropriately.

AC_DEFUN([GMP_4_0_CHECK],
[

AC_MSG_CHECKING(for GMP version >= 4.0.0 or later)

AC_ARG_WITH(
  gmp-include,
  AC_HELP_STRING(
    [--with-gmp-include=DIR],
    [look for the header gmp.h in DIR rather than the default search path]),
  [GMP_CFLAGS="-I$withval"], [GMP_CFLAGS=""])

AC_ARG_WITH(
  gmp-lib,
  AC_HELP_STRING([--with-gmp-lib=DIR],
    [look for libgmp.so in DIR rather than the default search path]),
  [
    case $withval in
      /* ) true;;
      *  ) AC_MSG_ERROR([

You must specify an absolute path for --with-gmp-lib.
]) ;;
    esac
    GMP_LIBS="-L$withval -Wl,-rpath $withval -Wl,-rpath /usr/local/lib -lgmp"
  ], [GMP_LIBS="-Wl,-rpath /usr/local/lib -lgmp"])

BACKUP_CFLAGS=${CFLAGS}
BACKUP_LIBS=${LIBS}

CFLAGS="${CFLAGS} ${GMP_CFLAGS}"
LIBS="${LIBS} ${GMP_LIBS}"

AC_TRY_LINK(
  [#include <gmp.h>],
  [mpz_t a; mpz_init (a);],
  [
    AC_TRY_RUN(
      [
#include <gmp.h>
int main() { if (__GNU_MP_VERSION < 4) return -1; else return 0; }
],
      [
        AC_MSG_RESULT(found)
        AC_SUBST(GMP_CFLAGS)
        AC_SUBST(GMP_LIBS)
        AC_DEFINE(HAVE_GMP,1,[Defined if GMP is installed])
      ],
      [
        AC_MSG_RESULT(old version)
        AC_MSG_ERROR([

Your version of the GNU Multiple Precision library (libgmp) is too
old! Please install a more recent version from http://gmplib.org/ and
try again. If more than one version is installed, try specifying a
particular version with

  ./configure --with-gmp-include=DIR --with-gmp-lib=DIR

See ./configure --help for more information.
])
      ])
  ],
  [
    AC_MSG_RESULT(not found)
    AC_MSG_ERROR([

The GNU Multiple Precision library (libgmp) was not found on your
system! Please obtain it from http://gmplib.org/ and install it before
trying again. If libgmp is already installed in a non-standard
location, try again with

  ./configure --with-gmp-include=DIR --with-gmp-lib=DIR

If you already specified those arguments, double check that gmp.h can
be found in the first path and libgmp.a can be found in the second.

See ./configure --help for more information.
])
  ])

CFLAGS=${BACKUP_CFLAGS}
LIBS=${BACKUP_LIBS}

])

dnl Check for libpbc and set PBC_CFLAGS and PBC_LIBS
dnl appropriately.

AC_DEFUN([PBC_CHECK],
[

AC_MSG_CHECKING(for the PBC library)

AC_ARG_WITH(
  pbc-include,
  AC_HELP_STRING(
    [--with-pbc-include=DIR],
    [look for the header pbc.h in DIR rather than the default search path]),
  [PBC_CFLAGS="-I$withval"], [PBC_CFLAGS="-I/usr/include/pbc -I/usr/local/include/pbc"])

AC_ARG_WITH(
  pbc-lib,
  AC_HELP_STRING(
    [--with-pbc-lib=DIR],
    [look for libpbc.so in DIR rather than the default search path]),
  [
    case $withval in
      /* ) true;;
      *  ) AC_MSG_ERROR([

You must specify an absolute path for --with-pbc-lib.
]) ;;
    esac
    PBC_LIBS="-L$withval -Wl,-rpath $withval -Wl,-rpath /usr/local/lib -lpbc"
  ], [PBC_LIBS="-Wl,-rpath /usr/local/lib -lpbc"])

BACKUP_CFLAGS=${CFLAGS}
BACKUP_LIBS=${LIBS}

CFLAGS="${CFLAGS} ${PBC_CFLAGS} ${GMP_CFLAGS}"
LIBS="${LIBS} ${PBC_LIBS} ${GMP_LIBS}"

AC_TRY_LINK(
  [#include <pbc.h>],
  [pairing_t p; pairing_init_set_buf(p, "", 0);],
  [
    AC_MSG_RESULT(found)
    AC_SUBST(PBC_CFLAGS)
    AC_SUBST(PBC_LIBS)
    AC_DEFINE(HAVE_PBC,1,[Defined if PBC is installed])
  ],
  [
    AC_MSG_RESULT(not found)
    AC_MSG_ERROR([

The PBC library was not found on your system! Please obtain it from

  http://crypto.stanford.edu/pbc/

and install it before trying again. If libpbc is already
installed in a non-standard location, try again with

  ./configure --with-pbc-include=DIR --with-pbc-lib=DIR

If you already specified those arguments, double check that pbc.h can
be found in the first path and libpbc.a can be found in the second.

See ./configure --help for more information.
])
  ])

CFLAGS=${BACKUP_CFLAGS}
LIBS=${BACKUP_LIBS}

])

dnl Check for libbswabe and set BSWABE_CFLAGS and BSWABE_LIBS
dnl appropriately.

AC_DEFUN([BSWABE_CHECK],
[

AC_MSG_CHECKING(for libbswabe)

AC_ARG_WITH(
  bswabe-include,
  AC_HELP_STRING(
    [--with-bswabe-include=DIR],
    [look for the header bswabe.h in DIR rather than the default search path]),
  [BSWABE_CFLAGS="-I$withval"], [BSWABE_CFLAGS=""])

AC_ARG_WITH(
  bswabe-lib,
  AC_HELP_STRING(
    [--with-bswabe-lib=DIR],
    [look for libbswabe.a in DIR rather than the default search path]),
  [
    case $withval in
      /* ) true;;
      *  ) AC_MSG_ERROR([

You must specify an absolute path for --with-bswabe-lib.
]) ;;
    esac
    BSWABE_LIBS="-L$withval -lbswabe"
  ], [BSWABE_LIBS="-lbswabe"])

BACKUP_CFLAGS=${CFLAGS}
BACKUP_LIBS=${LIBS}

CFLAGS="${CFLAGS} ${BSWABE_CFLAGS} ${PBC_CFLAGS} ${GMP_CFLAGS} ${GLIB_CFLAGS}"
LIBS="${LIBS} ${BSWABE_LIBS} ${PBC_LIBS} ${GMP_LIBS} ${GLIB_LIBS}"

AC_TRY_LINK(
  [#include <glib.h>
   #include <pbc.h>
   #include <bswabe.h>],
  [bswabe_pub_t* p;
   bswabe_pub_free(p);],
  [
    AC_MSG_RESULT(found)
    AC_SUBST(BSWABE_CFLAGS)
    AC_SUBST(BSWABE_LIBS)
    AC_DEFINE(HAVE_BSWABE,1,[Defined if libbswabe is installed])
  ],
  [
    AC_MSG_RESULT(not found)
    AC_MSG_ERROR([

The library libbswabe was not found on your system! Please obtain it
from

  http://acsc.csl.sri.com/cpabe/

and install it before trying again. If libbswabe is already
installed in a non-standard location, try again with

  ./configure --with-bswabe-include=<path> --with-bswabe-lib=<path>

If you already specified those arguments, double check that bswabe.h
can be found in the first path and libbswabe.a can be found in the
second.

See ./configure --help for more information.
])
  ])

CFLAGS=${BACKUP_CFLAGS}
LIBS=${BACKUP_LIBS}

])
