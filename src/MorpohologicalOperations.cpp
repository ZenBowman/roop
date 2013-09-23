#include "ExecutableCommand.h"

using namespace cv;

const int DEFAULT_STRUCTURING_ELEMENT_TYPE = MORPH_RECT;
const int DEFAULT_EROSION_SIZE = 3;

RoopList ErodeImage::execute(std::vector<EvalResult> arguments) {
  size_t argc = arguments.size();
  Mat image;
  int erosion_size = DEFAULT_EROSION_SIZE;
  int structuring_element = DEFAULT_STRUCTURING_ELEMENT_TYPE;
  
  if (argc > 1) {
    erosion_size = atoi(arguments[1].resultString.c_str());
  }
  
  Mat element2 = Mat::ones(erosion_size, erosion_size, CV_8UC1);
    
  Mat element = getStructuringElement(structuring_element, Size(erosion_size, erosion_size));
  erode(arguments[0].resultMat, image, element2);
  return fromMatrix(image);
}

RoopList DilateImage::execute(std::vector<EvalResult> arguments) {
  size_t argc = arguments.size();
  Mat image;
  int dilation_size = DEFAULT_EROSION_SIZE;
  int structuring_element = DEFAULT_STRUCTURING_ELEMENT_TYPE;
  
  if (argc > 1) {
    dilation_size = atoi(arguments[1].resultString.c_str());
  }
  
  Mat element = getStructuringElement(structuring_element, Size(dilation_size, dilation_size));
  dilate(arguments[0].resultMat, image, element);
  return fromMatrix(image);
}
