roop
====

Roop is a language and execution environment designed for image processing and computer vision. It is designed to encourage quick exploration and implementation, and built on top of [OpenCV][1].

[1]: http://opencv.org

Examples
---------

Prerequisites
-------------
 * g++
 * cmake
 * opencv
 * boost
 * readline

### Getting the prerequisites on Fedora
```
sudo yum instal gcc-g++ cmake opencv-devel boost-devel readline-devel
```


Installation
------------

Go to the main project directory, you should see the following:
```  
zenbowman@zenbowman-Pangolin-Performance:~/dev/github/roop$ ls	
images          README.md   roopscripts     thirdparty
CMakeLists.txt  LICENSE     rebuild-all.sh  src
```

To build:
```
bash rebuild-all.sh
```  

Running examples:
-----------------
  From the build folder, try the following command:

> ./Roop ../roopscripts/demo3.cvl
    
  You should see the Canny edge detection algorithm in action


Attribution:
------------
This project uses Matt Sotille's excellent s-expression parser: http://syntacticsalt.com/software/
