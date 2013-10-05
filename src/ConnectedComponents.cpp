#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "ExecutableCommand.h"

using namespace cv;
using namespace std;

RNG rng(12345);

RoopList FindConnected::execute(RoopMachine &machine, RoopList arguments) {
  vector< vector<Point> > contours;
  vector<Vec4i> hierarchy;

  Mat image = arguments[0].resultMat.clone();
  findContours(image, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

  Mat filledContours = Mat::zeros(image.size(), CV_8UC3);
  for( int i = 0; i< contours.size(); i++) {
    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    drawContours( filledContours, contours, i, color, CV_FILLED, 8, hierarchy, 0, Point() );
  }
  return fromMatrix(filledContours);
}
