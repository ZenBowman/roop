roop
====

Roop is a language and execution environment designed for image processing and computer vision. It is designed to encourage quick exploration and implementation, and built on top of [OpenCV][1].

[1]: http://opencv.org

Motivating examples
---------
Resizing an image to 1024x768 
```
(set resized-image (resize (load images/foo.jpg) 1024 768))
```

Applying the Canny edge detecting algorithm on an image (the last argument controls how aggressively edges are detected - lower implies more edges will be found)
```
(canny (load images/foo.jpg) 20)
```

A documentation of all the functions in roop is found [here][2].

[2]: docs/Functions.md

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
