#include "ExecutableCommand.h"

using namespace cv;

Mat ScalarMultiply::execute(std::vector<EvalResult> arguments) {
  Mat image = arguments[0].resultMat;
  float scaleFactor = atof(arguments[1].resultString.c_str());
  Mat result = image * scaleFactor;
  return result;
}
