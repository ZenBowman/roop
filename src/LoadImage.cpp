#include "ExecutableCommand.h"

RoopList LoadImage::execute(std::vector<EvalResult> arguments) {
  cv::Mat image;
  std::cout << "Loading image " << arguments[0].resultString;
  image = cv::imread(arguments[0].resultString, 1);
  return fromMatrix(image);
}

RoopList ResizeImage::execute(RoopList arguments) {
  cv::Mat newImage;
  cv::Mat original = arguments[0].resultMat;
  int newSize = atoi(arguments[1].resultString.c_str());
  cv::resize(original, newImage, cv::Size(newSize, newSize));
  return fromMatrix(newImage);
}