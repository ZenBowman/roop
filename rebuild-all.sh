#!/bin/bash

OS=uname

rm -rf build
rm -rf debug
rm -rf release
rm -rf xcode-build

mkdir debug
cd debug
cmake ../src -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
make
cd ..

mkdir release
cd release
cmake ../src -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
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
    cd ..
fi

