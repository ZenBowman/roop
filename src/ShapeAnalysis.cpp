#include "ExecutableCommand.h"

using namespace cv;

RoopList GetCentroid::execute(RoopMachine &machine, RoopList arguments) {
  RoopList result;
  Mat image = arguments[0].resultMat;
  Moments m = moments(image, true);
  result.push_back(EvalResult(m.m10/m.m00));
  result.push_back(EvalResult(m.m01/m.m00));
  return result;
}

