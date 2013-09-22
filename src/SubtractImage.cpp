#include "ExecutableCommand.h"

using namespace cv;

Mat SubtractImage::execute(std::vector<EvalResult> arguments) {
  Mat image = arguments[0].resultMat - arguments[1].resultMat;
  return image;
}
