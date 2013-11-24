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
    mkdir xcode-project
    cd xcode-project
    cmake ../src -G Xcode
    cd ..
else
    mkdir eclipse-project
    cd eclipse-project
    cmake ../src -G "Eclipse CDT4 - Unix Makefiles" 
fi

