#include "ExecutableCommand.h"

using namespace cv;

const int DEFAULT_BORDER = 10;

Mat removeBackgroundFromImage(Mat image, int backgroundBorder) {
  Mat mask;
  Mat bgdModel, fgdModel;
  Rect rect(backgroundBorder, backgroundBorder, 
	    image.cols-(2*backgroundBorder), 
	    image.rows-(2*backgroundBorder));
  grabCut(image, mask, rect, bgdModel, fgdModel, 1, GC_INIT_WITH_RECT);
  return mask > 2;
}

RoopList GetForegroundMaskGrabcut::execute(RoopMachine &machine, RoopList arguments) {
  Mat image = arguments[0].resultMat;
  int numBorderPixels = DEFAULT_BORDER;
  Mat result = removeBackgroundFromImage(image, numBorderPixels);
  return fromMatrix(result);
}

RoopList RemoveBackgroundGrabcut::execute(RoopMachine &machine, RoopList arguments){
  Mat image = arguments[0].resultMat;
  int numBorderPixels = DEFAULT_BORDER;
  Mat mask = removeBackgroundFromImage(image, numBorderPixels);
  Mat result;
  image.copyTo(result, mask);
  return fromMatrix(result);
}
