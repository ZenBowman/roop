#ifndef FOR_EACH_PIXEL_H
#define FOR_EACH_PIXEL_H

#include <opencv2/opencv.hpp>

using namespace cv;

struct RGB {
  int r;
  int g;
  int b;
};

class PointOperator {
 public:
  virtual int transform(int intensity) = 0;
};

class RGBPointOperator {
 public:
  virtual RGB transform(RGB pixelValue) = 0; 
};

Mat doForEachPixel(Mat inputMat, RGBPointOperator &pointOperator);
Mat doForEachPixel(Mat inputMat, PointOperator &pointOperator);

#endif
