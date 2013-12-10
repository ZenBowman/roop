#include "ExecutableCommand.h"
#include <iostream>
#include <fstream>
#include "RoopCommon.h"

RoopList LoadImage::execute(RoopMachine &machine, RoopList arguments) {
  cv::Mat image;
  std::cout << "Loading image " << arguments[0].resultString;
  image = cv::imread(arguments[0].resultString, 1);
  return fromMatrix(image);
}

RoopList ResizeImage::execute(RoopMachine &machine, RoopList arguments) {
  const size_t argsize = arguments.size();
  cv::Mat newImage;
  cv::Mat original = arguments[0].resultMat;

  int newSizeX;
  int newSizeY;

  if (argsize < 2) {
    machine.exceptionBitSet = true;
    return RoopList();
  }
  else if (argsize == 2) {
    newSizeX = argAsInt(arguments[1]);
    newSizeY = argAsInt(arguments[1]);
  } else {
    newSizeX = argAsInt(arguments[1]);
    newSizeY = argAsInt(arguments[2]);
  }

  cv::resize(original, newImage, cv::Size(newSizeX, newSizeY));
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
