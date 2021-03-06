#!/bin/bash

set -xeE
trap 'sleep 1' ERR

mkdir deploy

if [[ $WINDOWS = "TRUE" ]]
then
    ln -s ${MXE_DIR}/usr/$MXE_TARGET/opt/mazemaze mazemaze
    zip -r deploy/Mazemaze_${VERSION}_Windows_${ARCH_HUMAN}.zip mazemaze
else
    cd build
    $CMAKE $CMAKE_MAZEMAZE_FLAGS \
        -DCMAKE_INSTALL_PREFIX=/usr \
        -DMAZEMAZE_INSTALL_DIR=/opt \
        ..
    sudo make install DESTDIR=../deb
    cd ../deb
    md5deep -rl opt usr > DEBIAN/md5sums
    cat DEBIAN/md5sums
    cd ..
    fakeroot dpkg-deb --build deb
    mv deb.deb deploy/mazemaze_${VERSION}_${APT_ARCH}.deb

    tar -C /opt/ \
        -cvzf deploy/Mazemaze_${VERSION}_Linux_${ARCH_HUMAN}.tar.gz \
        mazemaze
fi

md5deep -rl deploy

set +xeE
