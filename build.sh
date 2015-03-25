#!/bin/bash


fname="version-increment"

THIS_FILE=$(basename $0)
THIS_PATH=$(realpath $0)

GCC_BIN=$(which gcc)
INSTALL_PATH=/usr/bin
BUILD_PATH="./build"


if [ -f "$BUILD_PATH" ]; then
  mkdir -p "$BUILD_PATH"
fi


function perform_action()
{
  cmdStarting=$1
  cmdEndSuccess=$2
  cmdEndFailedFmt=$3
  fname=$4
  build_command=$5

  printf "$cmdStarting '$fname'..."
  $($build_command)
  error_code=$?
  if [ $error_code == 0 ]; then
    printf "$cmdEndSuccess.\n"
  else
    printf "$cmdEndFailed\n" "$error_code"
  fi
}

perform_action "Compiling" "done" "failed (code: %d)." $fname "$GCC_BIN -O1 $fname.c -o $BUILD_PATH/$fname"
perform_action "Stripping" "done" "failed (code: %d)." $fname "strip --strip-all $BUILD_PATH/$fname"


#----------
if [ "$1" == "install" ]; then
  echo "Attempting to install $fname..."

  if [ ! -f $INSTALL_PATH/$fname ]; then
    sudo mv $BUILD_PATH/$fname $INSTALL_PATH/$fname
    echo "Successfully installed $fname into $INSTALL_PATH!"
  else
    echo "Could not install: $INSTALL_PATH/$fname already exists!"
  fi
fi

#----------
if [ "$1" == "archive" ]; then
  printf "Creating archive of the current directory..."
  curpath=$(pwd)
  basepath=$(basename "$curpath")

  cd .. >/dev/null
  $(tar -czf $basepath.tar.gz --exclude=build/* $basepath/ >/dev/null)
  mv "$basepath.tar.gz" "$basepath/$BUILD_PATH/$basepath.tar.gz" >/dev/null
  cd - >/dev/null

  echo "done."
  echo "Archive saved to \"$BUILD_PATH/$basepath.tar.gz\"."

fi
#----------
