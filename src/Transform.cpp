#include "Transform.h"
#include "ExecutableCommand.h"
#include "RoopCommon.h"
#include <iostream>
#include <sstream>
#include <boost/algorithm/string/replace.hpp>

std::string fromSexp(elt *sexp) {
  std::stringstream output; 
  if (sexp->ty == SEXP_LIST) {
    bool first = true;
    output << "(";
    elt *curr = sexp->list;
    while (curr != NULL) {
      if (first) {
	first = false;
      } else {
	output << " ";
      }
      output << fromSexp(curr);
      curr = curr->next;
    }
    output << ")";
  }
  else {
    output << sexp->val;
  }
  return output.str();
}

std::string Transform::defineTransform(RoopMachine &machine, sexp_t *command) {
  elt* curr = command->list->next;
  Transform t;
  t.transformName = curr->val;
  std::cout << "Defining transform with name " << t.transformName
	    << std::endl;

  curr = curr->next;
  
  while (curr->next != NULL){
    std::string newVariable = curr->val;
    std::cout << "Variable found " << newVariable << std::endl;
    t.variables.push_back(newVariable);
    curr = curr->next;
  }
  
  t.body = fromSexp(curr); 
  std::cout << "Transform body " << t.body << std::endl;

  machine.transforms[t.transformName] = t;

  return t.transformName;
}

RoopList Transform::execute(RoopMachine &machine, RoopList arguments) {
  RoopList result;
  std::map<std::string, std::string> environment;
  std::string executable = body;
  
  if ((arguments.size()) < variables.size()) {
    std::cout << "Not enough arguments for transform " << transformName
	      << std::endl << "Arguments needed = " << variables.size()
	      << std::endl << "Arguments supplied = " << arguments.size()
	      << std::endl;
    machine.exceptionBitSet = true;
  } else {
    for (size_t i=0; i<variables.size(); i++) {
      environment[variables[i]] = arguments[i].resultString;
      std::cout << "Bound variable " << variables[i] << " to "
		<< arguments[i].resultString << std::endl;

      boost::algorithm::replace_all(executable, variables[i], arguments[i].resultString);
    }
    
    std::cout << "About to execute " << executable << std::endl;
    result = machine.eval(executable);
  }

  return result;
}
