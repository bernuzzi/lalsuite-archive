#!/bin/sh -x

## Perform the installation of LAL and LALApps.  The following commands
## will download, build, and install LAL and LALApps.  This requires
## the software installed in the pre-install to have been built and installed.
## If the software was not installed in a standard location, such as
## "/usr" or "/usr/local", then the location of the software must be specified.
## To do so, the location of this software is given by the environment variable
## "LSCSOFT_LOCATION" which must be set before these commands are executed.

# set "LSCSOFT_LOCATION" to the location where the required software
# (described in the pre-install instructions) has been installed
#ignore
if test -z "$LSCSOFT_LOCATION"; then
  echo "ERROR: environment variable LSCSOFT_LOCATION not defined" 1>&2
  exit 1
fi
#/ignore
#verbatim
PATH=$LSCSOFT_LOCATION/bin:$PATH
LD_LIBRARY_PATH=$LSCSOFT_LOCATION/lib:$LD_LIBRARY_PATH
PKG_CONFIG_PATH=$LSCSOFT_LOCATION/lib/pkgconfig:$PKG_CONFIG_PATH
export PATH LD_LIBRARY_PATH PKG_CONFIG_PATH
#/verbatim

# set "LAL_PREFIX" to the location where you wish to install lal and lalapps
#ignore
LAL_PREFIX=${LAL_PREFIX:-"$LSCSOFT_LOCATION/devel"}
### for example (don't actually do this)
if 0; then
#/ignore
#verbatim
LAL_PREFIX=$LSCSOFT_LOCATION/devel
#/verbatim
#ignore
fi
#/ignore


### the rest of this script should not need to be edited


### simple failure
#ignore
fail() {
  echo "!!! Failure" 1>&2
  exit 1
}
#/ignore

# build and install LAL (the "--with-gcc-flags" tells gcc to use flags
# that will produce warnings about possibly non-portable code)
#ignore
if test -x 00boot ; then # distribution from CVS
  ./00boot || fail
fi
#/ignore
#verbatim
./configure --prefix=$LAL_PREFIX --with-gcc-flags || fail
make || fail
make install || fail
#/verbatim

## Now LAL has been built and installed.  To use LAL you may want to set
## various environment variables.  If you are using a Bourne shell, put
## the following in your "./profile" file:
#ignore
if 0; then
#/ignore
#verbatim
LAL_LOCATION=<value of "LAL_PREFIX">
export LAL_LOCATION
. $LAL_LOCATION/etc/lal-user-env.sh
#/verbatim
#ignore
if 0; then
#/ignore

### all done
#ignore
exit 0
#/ignore
