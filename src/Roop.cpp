#define VERBOSE_INTERACTIVE 1
#include "RoopCommon.h"
#include <fstream>

using namespace cv;

int main( int argc, char** argv )
{
  initRoop();
  cv::destroyWindow("win");
  char _command[256];
  sexp_t* command;
  EvalResult commandResult;
  
  namedWindow("Result", CV_WINDOW_AUTOSIZE);

  if (argc > 1) {
    char *initScriptFilename = argv[1];
    std::cout << "Recieved initializer file: " << initScriptFilename << std::endl;
    // Load initializer commands
    std::ifstream inputFile(initScriptFilename);
    while (inputFile.getline(_command, 256)) {
      if (strcmp("(display)", _command) != 0) {
        command = parse_sexp(_command, strlen(_command));
        eval(command);
      }
    }
  }
  
  while(true) {
    std::cout << "Enter command:\t";
    std::cin.getline(_command, 256);
    std::cout << "COMMAND = [" << _command << "]" << std::endl;
    if (strcmp("", _command) == 0) {
      return 1;
    }
    else if (strcmp("(exit)", _command) == 0) {
      break;
    }
    else if (strcmp("(display)", _command) == 0) {
      imshow("Result", commandResult.resultMat);
      waitKey(0);
    }
    else {
      command = parse_sexp(_command, strlen(_command));
      commandResult = eval(command)[0];
      destroy_sexp(command);
    }
  }

  return 1;
}
