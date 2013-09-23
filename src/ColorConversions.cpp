#include "ExecutableCommand.h"

using namespace cv;

RoopList ToGrayScale::execute(std::vector<EvalResult> arguments) {
  Mat result;
  Mat image = arguments[0].resultMat;
  cvtColor(image, result, CV_RGB2GRAY);
  return fromMatrix(result);
}

RoopList ToColor::execute(std::vector<EvalResult> arguments) {
  Mat result;
  Mat image = arguments[0].resultMat;
  cvtColor(image, result, CV_GRAY2RGB);
  return fromMatrix(result);
}

RoopList ToBinary::execute(RoopList arguments) {
  Mat result;
  Mat image = arguments[0].resultMat;
  int threshold = atoi(arguments[1].resultString.c_str());
  result = image > threshold;
  return fromMatrix(result);
}
