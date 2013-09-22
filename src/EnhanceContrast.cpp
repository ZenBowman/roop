#include "ExecutableCommand.h"
using namespace cv;

RoopList EnhanceContrast::execute(std::vector<EvalResult> arguments) {
  Mat image = arguments[0].resultMat.clone();
  int boost = atoi(arguments[1].resultString.c_str());
  
  Mat_<Vec3b> imageData = image;
  
  for (size_t i=0; i<image.rows; i++) {
    for (size_t j=0; j<image.cols; j++) {
      int r = imageData(i, j)[0];
      int g = imageData(i, j)[1];
      int b = imageData(i, j)[2];
      
      if ((r >= g) && (r >= b)) {
	imageData(i, j)[0] = imageData(i, j)[0]+boost;
      } else if ((g >= r) && (g >= b)) {
	imageData(i, j)[1] = imageData(i, j)[1]+boost;
      } else {
	imageData(i, j)[2] = imageData(i, j)[2]+boost;      
      }
    }
  }

  return fromMatrix(image);
}
