#include "ExecutableCommand.h"
#include <map>

using namespace cv;

std::map<std::string, Mat> savedImages;

Mat DefImage::execute(std::vector<EvalResult> arguments) {
  std::string name = arguments[0].resultString;
  Mat image = arguments[1].resultMat;
  savedImages[name] = image;
  return image;
}

Mat GetImage::execute(std::vector<EvalResult> arguments) {
  std::string name = arguments[0].resultString;
  return savedImages[name];
}
