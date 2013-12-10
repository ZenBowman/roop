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
std::vector<std::string> getCommandList();

class RoopMachine {
public:
  friend class DefImage;
  friend class GetImage;
  friend class Transform;
  friend class ResizeImage;

  RoopMachine();
  bool imageExists(std::string imageName);
  cv::Mat retrieveImage(std::string imageName);
  RoopList eval(std::string command);
  std::vector<std::string> getCommandList();

private:
  RoopList eval(std::vector<std::string> commands);
  RoopList eval(sexp_t* command);
  std::map<std::string, cv::Mat> savedImages;
  CommandMap commands;
  std::vector<std::string> commandList;
  std::map<std::string, Transform> transforms;

  bool exceptionBitSet;
  std::string exceptionMessage;
};

#endif
