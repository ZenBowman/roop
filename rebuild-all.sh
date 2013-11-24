#!/bin/bash

OS=uname

rm -rf build
rm -rf xcode-build

mkdir build
cd build
cmake .. -G "Unix Makefiles"
make

cd ..

if [ $OS == "darwin" ]
then
    mkdir xcode-build
    cd xcode-build
    cmake .. -G Xcode
    cd ..
fi

