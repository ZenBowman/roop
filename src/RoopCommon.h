#ifndef Roop_RoopCommon_h
#define Roop_RoopCommon_h

#include <map>
#include <string>
#include "ExecutableCommand.h"
#include "sexp.h"
#include "Transform.h"

typedef std::map<std::string, ExecutableCommand*> CommandMap;

struct CommandMapIterators {
  CommandMap::iterator start;
  CommandMap::iterator end;
};

RoopList evaluate(std::string command);
void initRoop();
bool isExitCommand(char *lineData);
bool isDisplayCommand(char *lineData);
CommandMapIterators getCommandIterator();

class RoopMachine {
public:
  friend class DefImage;
  friend class GetImage;
  friend class Transform;

  RoopMachine();
  bool imageExists(std::string imageName);
  cv::Mat retrieveImage(std::string imageName);
  RoopList eval(std::string command);
  CommandMapIterators getCommandIterator();

private:
  RoopList eval(std::vector<std::string> commands);
  RoopList eval(sexp_t* command);
  std::map<std::string, cv::Mat> savedImages;
  CommandMap commands;
  std::map<std::string, Transform> transforms;

  bool exceptionBitSet;
  std::string exceptionMessage;
};

#endif
