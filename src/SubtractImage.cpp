#include "ExecutableCommand.h"

using namespace cv;

RoopList SubtractImage::execute(std::vector<EvalResult> arguments) {
  Mat image = arguments[0].resultMat - arguments[1].resultMat;
  return fromMatrix(image);
}
