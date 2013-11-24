#!/bin/bash

OS=uname

rm -rf build
rm -rf xcode-build

mkdir build
cd build
cmake ../src -G "Unix Makefiles"
make

cd ..

if [ $OS == "darwin" ]
then
    mkdir xcode-build
    cd xcode-build
    cmake ../src -G Xcode
    cd ..
fi

