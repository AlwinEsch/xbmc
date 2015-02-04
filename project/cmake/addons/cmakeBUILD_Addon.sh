#!/bin/sh

#
# Helper file to create and install downloaded and builded addons
# to KODI's addon base directory in source
#
# Following DSP addons are currently available and must be set
# to end of this build file
#
# adsp.basic
# adsp.freesurround
# adsp.template
#

if [ -z "$1" ]; then
  echo "You must give one of addon names to build"
  exit 1
elif [ "$1" = "help" ]; then
  echo "This script create your requested addon and copy it to your source directory in addon folder "
  exit 0
fi

echo "Starting creation of $1"

if [ -f "Makefile" ]; then 
  make clean
fi

cmake -DPACKAGE_ZIP=1 -DADDONS_TO_BUILD=$1 -DCMAKE_INSTALL_PREFIX=../../../addons

make
