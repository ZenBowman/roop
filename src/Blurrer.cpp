#include "Blurrer.h"
#include <stdio.h>

void Blurrer::showWithGaussianBlur(cv::Mat original_image) {
  cv::Mat blurred_image;
  GaussianBlur(original_image, blurred_image, cv::Size(9, 9), 0, 0);
  imshow("Blurred", blurred_image);
  cv::waitKey(0);
}
