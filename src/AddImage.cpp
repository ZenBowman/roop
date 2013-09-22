#include "ExecutableCommand.h"

using namespace cv;

RoopList AddImage::execute(RoopList arguments) {
  Mat image = arguments[0].resultMat + arguments[1].resultMat;
  return fromMatrix(image);
}
