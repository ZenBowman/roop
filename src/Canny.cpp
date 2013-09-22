#include "ExecutableCommand.h"
#include <iostream>

using namespace cv;

const int edgeThresh = 1;
const int ratio = 3;
const int kernel_size = 3;

Mat CannyOperator::execute(std::vector<EvalResult> arguments) {
  Mat result, detected_edges, src_gray;

  Mat src = arguments[0].resultMat;
  int low_threshold = atoi(arguments[1].resultString.c_str());

  //  std::cout << "Applying canny with low threshold =" << low_threshold
  //	    << std::endl;
  cvtColor(src, src_gray, CV_BGR2GRAY);
  blur( src_gray, detected_edges, Size(3,3) );

  Canny(detected_edges, detected_edges, 
	 low_threshold, low_threshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  result = Scalar::all(0);

  src.copyTo(result, detected_edges);
  return result;
}
