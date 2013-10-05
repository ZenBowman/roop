#include "ExecutableCommand.h"

RoopList fromMatrix(cv::Mat matrix) {
  RoopList newList;
  EvalResult er;
  er.resultMat = matrix;
  newList.push_back(er);
  return newList;
}
