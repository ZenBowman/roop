#include "ExecutableCommand.h"
#include <list>
#include <vector>

using namespace cv;
using std::vector;

RoopList GetMoments::execute(RoopMachine &machine, RoopList arguments) {
  RoopList result;
  Mat image = arguments[0].resultMat;
  Moments m = moments(image, true);
  result.push_back(EvalResult(m.m20)); // Second order row moment
  result.push_back(EvalResult(m.m02)); // Second order column moment
  result.push_back(EvalResult(m.m11)); // Second order mixed moment
  return result;
}

RoopList GetCentroid::execute(RoopMachine &machine, RoopList arguments) {
  RoopList result;
  Mat image = arguments[0].resultMat;
  Moments m = moments(image, true);
  result.push_back(EvalResult(m.m10/m.m00));
  result.push_back(EvalResult(m.m01/m.m00));
  return result;
}

RoopList GetArea::execute(RoopMachine &machine, RoopList arguments) {
  RoopList result;
  Mat image = arguments[0].resultMat;
  vector< vector<Point> > contours;
  vector<Vec4i> hierarchy;
  std::list<double> sortedAreas;

  findContours(image, contours, hierarchy,
	       RETR_CCOMP, CHAIN_APPROX_SIMPLE);

  for (int i=0; i<contours.size(); i++) {
    sortedAreas.push_back(contourArea(contours[i]));
  }
  
  sortedAreas.sort();
  std::list<double>::iterator j;
  for (j=sortedAreas.begin(); j!=sortedAreas.end(); j++) {
    result.push_back(EvalResult(*j));
  }
  
  return result;
}
