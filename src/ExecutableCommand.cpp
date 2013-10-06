#include "ExecutableCommand.h"

#include <sstream>

RoopList fromMatrix(cv::Mat matrix) {
  RoopList newList;
  EvalResult er;
  er.resultMat = matrix;
  newList.push_back(er);
  return newList;
}

EvalResult::EvalResult() :resultString("NULL")
{
}

EvalResult::EvalResult(double dValue) 
  :resultType(RESULT_STRING)
{
  std::stringstream dStream;
  dStream << dValue;
  dStream >> resultString;
}

EvalResult::EvalResult(std::string _resultString) 
  :resultString(_resultString), resultType(RESULT_STRING)
{
}
