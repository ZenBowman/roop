#define VERBOSE_INTERACTIVE 1
#include "RoopCommon.h"
#include <fstream>
#include <string>

using namespace cv;


bool isCommentOrWhitespace(char *lineData) {
  std::string line = lineData;
  bool allWhitespace = true;
  for (std::string::iterator ss = line.begin(); ss != line.end(); ss++) {
    if (*ss == ';') {
      return true; //is comment
    }
    else if (*ss != ' ') {
      allWhitespace = false;
      break;
    }
  }
  return allWhitespace;
}

bool isSkippableLine(char *lineData) {
  return isCommentOrWhitespace(lineData); 
}

bool processLine(char* _command, EvalResult &commandResult,
		 std::string &lastCommand, int &line_number,
		 bool &shouldDisplay) 
{
  sexp_t* command = NULL;

  if (!isSkippableLine(_command)) {
    if (isDisplayCommand(_command)) {
      imshow(lastCommand.c_str(), commandResult.resultMat);
      shouldDisplay = true;
    } 
    else if (isExitCommand(_command)) {
      std::cout << "Exit found" << std::endl;
      return true;
    }
    else {
      command = parse_sexp(_command, strlen(_command));
      if (command == NULL) {
	std::cout << "Invalid s-expression on line " 
		  << line_number << " - skipping line" << std::endl;
      }   

      RoopList result = evaluate(command);
      if (result.size() > 0) {
	commandResult = result[0];
	lastCommand = _command;
      }
    }
  }    

  if (command != NULL) {
    destroy_sexp(command);
  }

  return false;
}

int main( int argc, char** argv )
{
  initRoop();
  cv::destroyWindow("win");
  char _command[256];
  sexp_t* command;
  EvalResult cResult;
  std::string lastCommand;
  bool shouldDisplay = false;
    
  if (argc > 1) {
    char *initScriptFilename = argv[1];
    std::cout << "Recieved initializer file: " << initScriptFilename << std::endl;
    // Load initializer commands
    std::ifstream inputFile(initScriptFilename);
    int line_number = 0;
    while (inputFile.getline(_command, 256)) {
      if (processLine(_command, cResult, lastCommand, 
		      line_number, shouldDisplay)) {
	return 0;
      }
      line_number ++;
    }
    if (shouldDisplay) {
      waitKey(0);
    }
  }
 
  
  while(true) {
    std::cout << "Enter command:\t";
    std::cin.getline(_command, 256);
    std::cout << "COMMAND = [" << _command << "]" << std::endl;
    shouldDisplay = false;
    int lnum = 0;
    if (processLine(_command, cResult, lastCommand, lnum, shouldDisplay)) {
      return 0;
    }
    if (shouldDisplay) {
      waitKey(0);
    }
   }

  return 0;
}
