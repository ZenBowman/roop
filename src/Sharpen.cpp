#include <iostream>
#include <stdio.h>
#include "ExecutableCommand.h"
#include <opencv2/opencv.hpp>

using namespace cv;

void sharpen(Mat &input, Mat &output) {
  Mat mask = (Mat_<char>(3,3) << 
	      0, -1,  0,
	      -1,  5, -1,
	      0, -1,  0);
  filter2D(input, output, input.depth(), mask);
}

RoopList Sharpen::execute(RoopMachine &machine, RoopList arguments) {
  Mat output_image;
  Mat input_image = arguments[0].resultMat;
  sharpen(input_image, output_image);
  return fromMatrix(output_image);
}

