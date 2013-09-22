#ifndef BLURRER_H
#define BLURRER_H

#include <opencv2/opencv.hpp>

class Blurrer
{
 public:
  static void showWithGaussianBlur(cv::Mat original_image);
};

#endif
