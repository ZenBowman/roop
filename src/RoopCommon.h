#ifndef Roop_RoopCommon_h
#define Roop_RoopCommon_h

#include <map>
#include <string>
#include "ExecutableCommand.h"
#include "sexp.h"

RoopList eval(sexp_t* command);
void initRoop();

#endif
