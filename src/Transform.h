#ifndef Roop_UserDefinedTransform_h
#define Roop_UserDefinedTransform_h

#include <string>
#include <vector>
#include "sexp.h"
#include "ExecutableCommand.h"
class RoopMachine;

class Transform: ExecutableCommand {
 public:
  static std::string defineTransform(RoopMachine &machine, sexp_t *command);
  RoopList execute(RoopMachine &machine, RoopList arguments);
 private:
  std::string transformName;
  std::vector<std::string> variables;
  std::string body;
};

#endif
