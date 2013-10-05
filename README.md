roop
====

An s-expression language for image manipulation and computer vision built on OpenCV

Installation:
 - Requires Cmake
 - Requires OpenCV

Go to the main project directory, you should see the following:
  
zenbowman@zenbowman-Pangolin-Performance:~/dev/github/roop$ ls
images          README.md   roopscripts     thirdparty
CMakeLists.txt  LICENSE     rebuild-all.sh  src

Type the following:
  bash rebuild-all.sh
  
If you have cmake and opencv installed, it should build fine.

Running examples:
  From the build folder, try the following command:
    ./Roop ../roopscripts/demo3.cvl
    
  You should see the Canny edge detection algorithm in action


