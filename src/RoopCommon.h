#ifndef Roop_RoopCommon_h
#define Roop_RoopCommon_h

#include <map>
#include <string>
#include "ExecutableCommand.h"
#include "sexp.h"

RoopList eval(sexp_t* command);
void initRoop();

bool isExitCommand(char *lineData);
bool isDisplayCommand(char *lineData);

class RoopMachine {
private:
  std::map<std::string, cv::Mat> savedImages;
  
};

#endif
