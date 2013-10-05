#include "ExecutableCommand.h"

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
