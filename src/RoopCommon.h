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
public:
  friend class DefImage;
  friend class GetImage;

  RoopMachine();
  RoopList eval(sexp_t* command);
  bool imageExists(std::string imageName);
  cv::Mat retrieveImage(std::string imageName);
  
private:
  std::map<std::string, cv::Mat> savedImages;
  std::map<std::string, ExecutableCommand*> commands;
  bool exceptionBitSet;
  std::string exceptionMessage;
};

#endif
