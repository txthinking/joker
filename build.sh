#!/bin/bash

if [ $# -ne 1 ]; then
    echo "./build.sh version"
    exit
fi

rm -rf _
mkdir _

make clean
make CC="zig cc -target x86_64-linux-gnu"
mv joker _/joker_linux_amd64_gnu
make clean
make CC="zig cc -target x86_64-linux-musl"
mv joker _/joker_linux_amd64
make clean
make CC="zig cc -target aarch64-linux-gnu"
mv joker _/joker_linux_arm64_gnu
make clean
make CC="zig cc -target aarch64-linux-musl"
mv joker _/joker_linux_arm64

zig cc -o joker -target x86_64-macos-none main.c run.c
mv joker _/joker_darwin_amd64
zig build-exe -lc --name joker -target aarch64-macos-none -O ReleaseSafe main.c run.c
mv joker _/joker_darwin_arm64

if [ "$1" = "dev" ]
then
    exit
fi

nami release github.com/txthinking/joker $1 _

rm -rf _
