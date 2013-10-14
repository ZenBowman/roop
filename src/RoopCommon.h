#ifndef Roop_RoopCommon_h
#define Roop_RoopCommon_h

#include <map>
#include <string>
#include "ExecutableCommand.h"
#include "sexp.h"
#include "Transform.h"

RoopList evaluate(std::string command);
void initRoop();
bool isExitCommand(char *lineData);
bool isDisplayCommand(char *lineData);

class RoopMachine {
public:
  friend class DefImage;
  friend class GetImage;
  friend class Transform;

  RoopMachine();
  bool imageExists(std::string imageName);
  cv::Mat retrieveImage(std::string imageName);
  RoopList eval(std::string command);

private:
  RoopList eval(std::vector<std::string> commands);
  RoopList eval(sexp_t* command);
  std::map<std::string, cv::Mat> savedImages;
  std::map<std::string, ExecutableCommand*> commands;
  std::map<std::string, Transform> transforms;

  bool exceptionBitSet;
  std::string exceptionMessage;
};

#endif
