#include "ExecutableCommand.h"
#include <map>

using namespace cv;

std::map<std::string, Mat> savedImages;

RoopList DefImage::execute(RoopList arguments) {
  std::string name = arguments[0].resultString;
  Mat image = arguments[1].resultMat;
  savedImages[name] = image;
  return fromMatrix(image);
}

RoopList GetImage::execute(std::vector<EvalResult> arguments) {
  std::string name = arguments[0].resultString;
  return fromMatrix(savedImages[name]);
}

bool imageExists(std::string imageName) {
  return (savedImages.find(imageName) != savedImages.end());
}

Mat retrieveImage(std::string imageName) {
  return savedImages[imageName];
}
