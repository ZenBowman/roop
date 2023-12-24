#include "ExecutableCommand.h"
#include "stdio.h"

using namespace cv;

RoopList ToGrayScale::execute(RoopMachine &machine, RoopList arguments) {
  Mat result;
  Mat image = arguments[0].resultMat;
  cvtColor(image, result, COLOR_RGB2GRAY);
  return fromMatrix(result);
}

RoopList ToColor::execute(RoopMachine &machine, RoopList arguments) {
  Mat result;
  Mat image = arguments[0].resultMat;
  cvtColor(image, result, COLOR_GRAY2RGB);
  return fromMatrix(result);
}

RoopList ToBinary::execute(RoopMachine &machine, RoopList arguments) {
  Mat result;
  Mat image = arguments[0].resultMat;
  int threshold = atoi(arguments[1].resultString.c_str());
  result = image > threshold;
  return fromMatrix(result);
}

std::string type2str(int type) {
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

RoopList ProbeMatrix::execute(RoopMachine &machine, RoopList arguments) {
  Mat image = arguments[0].resultMat;
  std::string typeDescription = type2str(image.type());
  std::cout << "Matrix type = " << typeDescription << std::endl;
  return arguments;
}
