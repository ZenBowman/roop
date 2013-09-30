#include "ExecutableCommand.h"

using namespace cv;

RoopList AddImage::execute(RoopList arguments) {
  Mat image = arguments[0].resultMat + arguments[1].resultMat;
  return fromMatrix(image);
}

RoopList InvertImage::execute(RoopList arguments) {
  return fromMatrix(arguments[0].resultMat < 128);
}

RoopList AndImage::execute(RoopList arguments) {
  Mat image = arguments[0].resultMat;
  Mat mask = arguments[1].resultMat;
  Mat result;
  image.copyTo(result, mask);
  return fromMatrix(result);
}

RoopList SubtractImage::execute(std::vector<EvalResult> arguments) {
  Mat image = arguments[0].resultMat - arguments[1].resultMat;
  return fromMatrix(image);
}
