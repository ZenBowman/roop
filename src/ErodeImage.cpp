#include "ExecutableCommand.h"

using namespace cv;

const int erosion_type = MORPH_RECT;

RoopList ErodeImage::execute(std::vector<EvalResult> arguments) {
  Mat image;
  int erosion_size = atoi(arguments[1].resultString.c_str());
  int erosion_pt = atoi(arguments[2].resultString.c_str());
  Mat element = getStructuringElement(erosion_type, 
				  Size(erosion_size, erosion_size),
				  Point(erosion_pt, erosion_pt));
  erode(arguments[0].resultMat, image, element);
  return fromMatrix(image);
}
