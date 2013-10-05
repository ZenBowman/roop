#include "ExecutableCommand.h"
#include <map>
#include "RoopCommon.h"

using namespace cv;

RoopList DefImage::execute(RoopMachine &machine, RoopList arguments) {
  std::string name = arguments[0].resultString;
  Mat image = arguments[1].resultMat;
  machine.savedImages[name] = image;
  return fromMatrix(image);
}

RoopList GetImage::execute(RoopMachine &machine, RoopList arguments) {
  std::string name = arguments[0].resultString;
  return fromMatrix(machine.savedImages[name]);
}


