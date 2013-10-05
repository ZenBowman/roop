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

int main( int argc, char** argv )
{
  initRoop();
  cv::destroyWindow("win");
  char _command[256];
  sexp_t* command;
  EvalResult commandResult;
  std::string lastCommand;
  
  //namedWindow("Result", CV_WINDOW_AUTOSIZE);

  if (argc > 1) {
    char *initScriptFilename = argv[1];
    std::cout << "Recieved initializer file: " << initScriptFilename << std::endl;
    // Load initializer commands
    std::ifstream inputFile(initScriptFilename);
    int line_number = 0;
    bool shouldDisplay = false;
    while (inputFile.getline(_command, 256)) {
      
      if (!isSkippableLine(_command)) {
        command = parse_sexp(_command, strlen(_command));
        if (command == NULL) {
          std::cout << "Invalid s-expression on line " << line_number << " - skipping line" << std::endl;
        } else if (isDisplayCommand(_command)) {
	  imshow(lastCommand.c_str(), commandResult.resultMat);
	  shouldDisplay = true;
	} else if (isExitCommand(_command)) {
	  std::cout << "Exit found" << std::endl;
	  return 0;
	}
	else {
	  RoopList result = eval(command);
	  if (result.size() > 0) {
	    commandResult = eval(command)[0];
	    lastCommand = _command;
	  }
	}
        line_number ++;
      }
    }
    waitKey(0);
  }
  
  while(true) {
    std::cout << "Enter command:\t";
    std::cin.getline(_command, 256);
    std::cout << "COMMAND = [" << _command << "]" << std::endl;
    
    if (isExitCommand(_command)) {
      break;
    }
    else if (isDisplayCommand(_command)) {
      imshow(lastCommand.c_str(), commandResult.resultMat);
      waitKey(0);
    }
    else {
      command = parse_sexp(_command, strlen(_command));
      if (command == NULL) {
        std::cout << "Invalid s-expression" << std::endl;
      }
      else {
        RoopList result = eval(command);
        if (result.size() > 0) {
          commandResult = eval(command)[0];
	  lastCommand = _command;
        }
        destroy_sexp(command);
      }
    }
  }

  return 1;
}
