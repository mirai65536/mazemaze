#!/bin/bash

set -xe

mkdir deploy

if [[ $WINDOWS = "TRUE" ]]
then
    ln -s ${MXE_DIR}/usr/$MXE_TARGET/mazemaze mazemaze
    zip -r deploy/mazemaze-0.2-amd64-windows.zip mazemaze
else
    cd deb
    mkdir opt
    cp -r /opt/mazemaze opt
    mkdir -p usr/share/applications/
    cp ~/.local/share/applications/mazemaze.desktop usr/share/applications/
    md5deep -rl opt usr > DEBIAN/md5sums
    cat DEBIAN/md5sums
    cd ..
    fakeroot dpkg-deb --build deb
    mv deb.deb deploy/mazemaze_0.2_amd64.deb

    tar -C /opt/ -cvzf deploy/mazemaze-0.2-amd64-linux.tar.gz mazemaze
fi

md5deep -rl deploy

set +xe