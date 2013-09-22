#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>
#include "sexp.h"
#include "ExecutableCommand.h"

using namespace cv;

const int erosion_type = MORPH_RECT;
LoadImage loadImage;
ErodeImage erodeImage;
DilateImage dilateImage;
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

std::map<std::string, ExecutableCommand*> commands;

void init() {
  commands["load"] = &loadImage;
  commands["erode"] = &erodeImage;
  commands["subtract"] = &subtractImage;
  commands["add"] = &addImage;
  commands["set"] = &defImage;
  commands["get"] = &getImage;
  commands["enhance"] = &enhanceContrast;
  commands["sharpen"] = &sharpen;
  commands["blur"] = &blurOp;
  commands["filter"] = &filter3;
  commands["dilate"] = &dilateImage;
  commands["make-gray"] = &toGrayScale;
  commands["make-color"] = &toColor;
  commands["sobel"] = &sobel;
  commands["scharr"] = &scharr;
  commands["laplace"] = &laplace;
  commands["canny"] = &canny;
  commands["mult"] = &smultiply;
}

EvalResult eval(sexp_t* command) {
  elt* current;
  std::string operation;
  std::vector<EvalResult> arguments;
  EvalResult result;
  result.resultType = RESULT_MATRIX;

  if (command->ty == SEXP_LIST) {
    operation = command->list->val;
#ifdef VERBOSE_INTERACTIVE
    std::cout << "Found command: " << command->list->val << std::endl;
#endif
    current = command->list->next;
    while (current != 0) {
      if (current->ty == SEXP_VALUE) {

#ifdef VERBOSE_INTERACTIVE
	std::cout << "Found argument: " << current->val << std::endl;
#endif

	EvalResult er;
	er.resultString = current->val;

#ifdef VERBOSE_INTERACTIVE
	std::cout << "Added argument " << er.resultString << std::endl;
#endif
	er.resultType = RESULT_STRING;
	arguments.push_back(er);
      } else {
	arguments.push_back(eval(current));
      }
      current = current->next;
    }
    
#ifdef VERBOSE_INTERACTIVE
    std::cout << "Processing operation " << operation << " with args: "
	      << std::endl;
#endif

    for (size_t i=0; i<arguments.size(); i++) {
      EvalResult i_er = arguments[i];

#ifdef VERBOSE_INTERACTIVE
      if (i_er.resultType == RESULT_STRING) {
	std::cout << "string = " << i_er.resultString << std::endl;
      } else {
	std::cout << "MATRIX" << std::endl;
      }
#endif

    }

    if (commands.find(operation) != commands.end()) {
      result.resultMat = commands[operation]->execute(arguments);
    }
  }
  return result;
}
