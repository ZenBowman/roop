#include "ExecutableCommand.h"

cv::Mat LoadImage::execute(std::vector<EvalResult> arguments) {
  cv::Mat image;
  std::cout << "Loading image " << arguments[0].resultString;
  image = cv::imread(arguments[0].resultString, 1);
  return image;
}
