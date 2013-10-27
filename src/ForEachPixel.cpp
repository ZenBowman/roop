#include "ForEachPixel.h"
using namespace cv;

Mat doForEachPixel(Mat inputMat, PointOperator &pointOperator) {
  Mat output = inputMat.clone();
  Mat_<Vec3b> imageData = output;

  for (size_t i=0; i<output.rows; i++) {
    for (size_t j=0; j<output.cols; j++) {
      RGB rgb;
      rgb.r = imageData(i, j)[0];
      rgb.g = imageData(i, j)[1];
      rgb.b = imageData(i, j)[2];
      RGB new_rgb = pointOperator.transform(rgb);
      imageData(i, j)[0] = new_rgb.r;
      imageData(i, j)[1] = new_rgb.g;
      imageData(i, j)[2] = new_rgb.b;
    }
  }
  return output;
}
