#!/bin/bash

set -xe

mkdir build
cd build
export CMAKE_MAZEMAZE_FLAGS="-DCMAKE_VERBOSE_MAKEFILE=TRUE"
if [[ $WINDOWS = "TRUE" ]]
then
    CMAKE_MAZEMAZE_FLAGS="$CMAKE_MAZEMAZE_FLAGS \
        -DSFML_STATIC_LIBRARIES=TRUE" \
        -DMAZEMAZE_INSTALL_DIR=${MXE_DIR}/usr/$MXE_TARGET/opt
fi
$CMAKE $CMAKE_MAZEMAZE_FLAGS ..
$CMAKE --build .
sudo make install
cd ..

set +xe
