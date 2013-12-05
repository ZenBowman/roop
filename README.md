roop
====

An s-expression language for image manipulation and computer vision built on OpenCV

Prerequisites:
-------------
'''
g++
cmake
opencv
boost
readline
'''

Installation
------------

Go to the main project directory, you should see the following:
'''  
	zenbowman@zenbowman-Pangolin-Performance:~/dev/github/roop$ ls	
	images          README.md   roopscripts     thirdparty
	CMakeLists.txt  LICENSE     rebuild-all.sh  src
'''

To build:
'''
bash rebuild-all.sh
'''  

Running examples:
-----------------
  From the build folder, try the following command:

> ./Roop ../roopscripts/demo3.cvl
    
  You should see the Canny edge detection algorithm in action


Attribution:
------------
This project uses Matt Sotille's excellent s-expression parser: http://syntacticsalt.com/software/
