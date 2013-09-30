#include "ExecutableCommand.h"

using namespace cv;

const int DEFAULT_STRUCTURING_ELEMENT_TYPE = MORPH_RECT;
const int DEFAULT_EROSION_SIZE = 3;

int getStructuringElementTypeFromString(std::string elemType) {
  if (elemType == "ellipse") {
    return MORPH_ELLIPSE;
  } else if (elemType == "rect") {
    return MORPH_RECT;
  } else {
    std::cerr << "Invalid element type " << elemType << " - using default" << std::endl;
    return MORPH_RECT;
  }
}


RoopList SquareErodeImage::execute(std::vector<EvalResult> arguments) {
  size_t argc = arguments.size();
  Mat image;
  int erosion_size = DEFAULT_EROSION_SIZE;
  int structuring_element = DEFAULT_STRUCTURING_ELEMENT_TYPE;
  
  if (argc > 1) {
    erosion_size = atoi(arguments[1].resultString.c_str());
  }
  if (argc > 2) {
    structuring_element = getStructuringElementTypeFromString(arguments[2].resultString);
  }
   
  Mat element = getStructuringElement(structuring_element, Size(erosion_size, erosion_size));
  erode(arguments[0].resultMat, image, element);
  return fromMatrix(image);
}

RoopList SquareDilateImage::execute(std::vector<EvalResult> arguments) {
  size_t argc = arguments.size();
  Mat image;
  int dilation_size = DEFAULT_EROSION_SIZE;
  int structuring_element = DEFAULT_STRUCTURING_ELEMENT_TYPE;
  
  if (argc > 1) {
    dilation_size = atoi(arguments[1].resultString.c_str());
  }

  if (argc > 2) {
    structuring_element = getStructuringElementTypeFromString(arguments[2].resultString);
  }
  
  Mat element = getStructuringElement(structuring_element, Size(dilation_size, dilation_size));
  dilate(arguments[0].resultMat, image, element);
  return fromMatrix(image);
}

