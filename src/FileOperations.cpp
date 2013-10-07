#include "ExecutableCommand.h"
#include <iostream>
#include <fstream>

RoopList LoadImage::execute(RoopMachine &machine, RoopList arguments) {
  cv::Mat image;
  std::cout << "Loading image " << arguments[0].resultString;
  image = cv::imread(arguments[0].resultString, 1);
  return fromMatrix(image);
}

RoopList ResizeImage::execute(RoopMachine &machine, RoopList arguments) {
  cv::Mat newImage;
  cv::Mat original = arguments[0].resultMat;
  int newSize = atoi(arguments[1].resultString.c_str());
  cv::resize(original, newImage, cv::Size(newSize, newSize));
  return fromMatrix(newImage);
}

RoopList SaveImage::execute(RoopMachine &machine, RoopList arguments) {
  cv::Mat image = arguments[0].resultMat;
  std::string filename = arguments[1].resultString;
  cv::imwrite(filename, image);
  return fromMatrix(image);
}

WriteParams::WriteParams(bool newFile): append(!newFile) {
}

RoopList WriteParams::execute(RoopMachine &machine, RoopList arguments) {
  std::string filename = arguments[0].resultString;
  
  std::ofstream appender(filename.c_str(), std::ios::out | std::ios::app);
  for (int i=1; i<arguments.size(); i++) {
    appender << arguments[i].resultString << " ";
  }
  appender << std::endl;
  appender.close();
  return arguments;
}
