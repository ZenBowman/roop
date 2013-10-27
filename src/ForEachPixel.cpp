#include "ForEachPixel.h"
#include "ExecutableCommand.h"
#include "math.h"
using namespace cv;

Mat doForEachPixel(Mat inputMat, RGBPointOperator &pointOperator) {
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

Mat doForEachPixel(Mat inputMat, PointOperator &pointOperator) {
  Mat output = inputMat.clone();
  float sumdiff = 0.0;

  uchar *rowData;
  for (size_t i=0; i<output.rows; i++) {
    rowData = output.ptr<uchar>(i);
    for (size_t j=0; j<output.cols; j++) {
      int intensity = rowData[j];
      int new_intensity = pointOperator.transform(intensity);
      sumdiff += abs(intensity-new_intensity);
      rowData[j] = new_intensity;
    }
  }

  std::cout << "Pixel change " << sumdiff << std::endl;
  return output;
}


class GammaCorrect: public PointOperator {
private:
  float power;
public:
  GammaCorrect(float pow);
  int transform(int);
};

GammaCorrect::GammaCorrect(float pow) {
  power = pow;
}

int GammaCorrect::transform(int intensity) {
  double scalified = intensity / 255.0;
  double new_val = pow(scalified, power);
  return (int) (new_val * 255.0);
}

RoopList GammaGray::execute(RoopMachine &machine, RoopList arguments) {
  Mat input = arguments[0].resultMat;
  float power = atof(arguments[1].resultString.c_str());
  GammaCorrect gammaCorrect(power);
  Mat result = doForEachPixel(input, gammaCorrect);
  return fromMatrix(result);
}
