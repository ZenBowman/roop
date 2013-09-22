#include "ExecutableCommand.h"

using namespace cv;

const int dilation_type = MORPH_RECT;

Mat DilateImage::execute(std::vector<EvalResult> arguments) {
  Mat image;
  int dilation_size = atoi(arguments[1].resultString.c_str());
  int dilation_pt = atoi(arguments[2].resultString.c_str());
  Mat element = getStructuringElement(dilation_type, 
				  Size(dilation_size, dilation_size),
				  Point(dilation_pt, dilation_pt));
  dilate(arguments[0].resultMat, image, element);
  return image;
}
