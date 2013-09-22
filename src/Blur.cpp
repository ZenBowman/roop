#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "ExecutableCommand.h"

using namespace cv;

Mat Blur::execute(std::vector<EvalResult> arguments) {
  Mat blurred_image;
  Mat original_image = arguments[0].resultMat;
  int blur_size = atoi(arguments[1].resultString.c_str());
  GaussianBlur(original_image, blurred_image, cv::Size(blur_size, blur_size), 0, 0);
  return blurred_image;
}
