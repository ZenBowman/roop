#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>
#include "ExecutableCommand.h"
#include "RoopCommon.h"

using namespace cv;

const int erosion_type = MORPH_RECT;
LoadImage loadImage;
SquareErodeImage erodeImage;
SquareDilateImage dilateImage;
SubtractImage subtractImage;
AddImage addImage;
DefImage defImage;
GetImage getImage;
EnhanceContrast enhanceContrast;
Sharpen sharpen;
Blur blurOp;
Filter3 filter3;
ToGrayScale toGrayScale;
SobelOperator sobel(SOBEL);
SobelOperator scharr(SCHARR);
LaplaceOperator laplace;
CannyOperator canny;
ScalarMultiply smultiply;
ToColor toColor;
ToBinary toBinary;
ResizeImage resizeImage;

std::map<std::string, ExecutableCommand*> commands;

const char *DISPLAY_COMMAND = "(display)";
const char *EXIT_COMMAND = "(exit)";


bool isExitCommand(char *lineData) {
  return (strcmp(EXIT_COMMAND, lineData) == 0);
}

bool isDisplayCommand(char *lineData) {
  return (strcmp(DISPLAY_COMMAND, lineData) == 0);
}

void initRoop() {
  commands["resize"] = &resizeImage;
  commands["load"] = &loadImage;
  commands["sq-erode"] = &erodeImage;
  commands["subtract"] = &subtractImage;
  commands["add"] = &addImage;
  commands["set"] = &defImage;
  commands["get"] = &getImage;
  commands["enhance"] = &enhanceContrast;
  commands["sharpen"] = &sharpen;
  commands["blur"] = &blurOp;
  commands["filter"] = &filter3;
  commands["sq-dilate"] = &dilateImage;
  commands["make-gray"] = &toGrayScale;
  commands["make-color"] = &toColor;
  commands["sobel"] = &sobel;
  commands["scharr"] = &scharr;
  commands["laplace"] = &laplace;
  commands["canny"] = &canny;
  commands["mult"] = &smultiply;
  commands["binarize"] = &toBinary;
}


RoopList eval(sexp_t* command) {
  elt* current;
  std::string operation;
  std::vector<EvalResult> arguments;
  RoopList result;
  
  if (command->ty == SEXP_LIST) {
    operation = command->list->val;

    if (commands.find(operation) == commands.end()) {
      std::cout << "Invalid operator " << operation << "found." << std::endl;
      return result;
    }
    
    current = command->list->next;
    while (current != 0) {
      if (current->ty == SEXP_VALUE) {

        std::cout << "Found argument: " << current->val << std::endl;

        EvalResult er;
        er.resultString = current->val;

        std::cout << "Added argument " << er.resultString << std::endl;
        er.resultType = RESULT_STRING;
        arguments.push_back(er);
      } else {
        RoopList tempRes = eval(current);
        if (tempRes.size() == 0) {
          return result;  // Some invalid operation found
        }
        arguments.insert(arguments.end(), tempRes.begin(), tempRes.end());
      }
      current = current->next;
    }
    
    std::cout << "Processing operation " << operation << " with args: "
	      << std::endl;

    for (size_t i=0; i<arguments.size(); i++) {
      EvalResult i_er = arguments[i];

      if (i_er.resultType == RESULT_STRING) {
        std::cout << "string = " << i_er.resultString << std::endl;
      } else {
        std::cout << "MATRIX" << std::endl;
      }

    }

    if (commands.find(operation) != commands.end()) {
      result = commands[operation]->execute(arguments);
    }
  }
  return result;
}
