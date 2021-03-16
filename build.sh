#!/bin/bash

if [ $# -ne 1 ]; then
    echo "./build.sh version"
    exit
fi

mkdir _

make clean
make
mv joker _/joker_linux_amd64

make clean
docker run -it --rm -v $(pwd):/workdir -e CROSS_TRIPLE=x86_64-apple-darwin multiarch/crossbuild make
mv joker _/joker_darwin_amd64

nami release github.com/txthinking/joker $1 _

rm -rf _
