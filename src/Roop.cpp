#define VERBOSE_INTERACTIVE 1
#include "RoopCommon.cpp"

int main( int argc, char** argv )
{
  init();
  cv::destroyWindow("win");
  char _command[256];
  sexp_t* command;
  EvalResult commandResult;
  std::string foo;
  
  namedWindow("Result", CV_WINDOW_AUTOSIZE);

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
      waitKey(0);
    }
    else {
      command = parse_sexp(_command, strlen(_command));
      commandResult = eval(command);
      imshow("Result", commandResult.resultMat);
      destroy_sexp(command);
    }
  }

  return 1;
}
