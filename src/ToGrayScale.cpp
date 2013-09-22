#include "ExecutableCommand.h"

using namespace cv;

Mat ToGrayScale::execute(std::vector<EvalResult> arguments) {
  Mat result;
  Mat image = arguments[0].resultMat;
  cvtColor(image, result, CV_RGB2GRAY);
  return result;
}

Mat ToColor::execute(std::vector<EvalResult> arguments) {
  Mat result;
  Mat image = arguments[0].resultMat;
  cvtColor(image, result, CV_GRAY2RGB);
  return result;
}
