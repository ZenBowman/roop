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
ToBinary toBinary;
ResizeImage resizeImage;
RemoveBackgroundGrabcut removeBackgroundGrabcut;
GetForegroundMaskGrabcut getForegroundMaskGrabcut;
InvertImage invertImage;
AndImage andImage;

std::auto_ptr<RoopMachine> defaultMachine;

bool isExitCommand(char *lineData) {
  return (strcmp("exit", lineData) == 0);
}

bool isDisplayCommand(char *lineData) {
  return ((strcmp("display", lineData) == 0) || (strcmp("(display)", lineData) == 0));
}

void initRoop() {
  defaultMachine = std::auto_ptr<RoopMachine>(new RoopMachine());
}

RoopList eval(sexp_t* command) {
  return defaultMachine->eval(command);
}

bool RoopMachine::imageExists(std::string imageName) {
  return (savedImages.find(imageName) != savedImages.end());
}

Mat RoopMachine::retrieveImage(std::string imageName) {
  return savedImages[imageName];
}

RoopMachine::RoopMachine() : exceptionBitSet(false)
{
  commands["resize"] = &resizeImage;
  commands["load"] = &loadImage;
  commands["erode"] = &erodeImage;
  commands["subtract"] = &subtractImage;
  commands["invert"] = &invertImage;
  commands["and"] = &andImage;
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
  commands["binarize"] = &toBinary;
  commands["remove-background"] = &removeBackgroundGrabcut;
  commands["get-foreground-mask"] = &getForegroundMaskGrabcut;
}

RoopList RoopMachine::eval(sexp_t* command) {
  elt* current;
  std::string operation;
  RoopList arguments;
  RoopList result;
  
  if (command->ty == SEXP_LIST) {
    operation = command->list->val;
    
    if (commands.find(operation) == commands.end()) {
      std::stringstream exception;
      exception << "Invalid operator " << operation << "found." << std::endl;
      exception >> exceptionMessage;
      exceptionBitSet = true;
      return result;
    }
    
    current = command->list->next;
    while (current != 0) {
      if (current->ty == SEXP_VALUE) {
        std::cout << "Found argument: " << current->val << std::endl;
        
        EvalResult er;
        er.resultString = current->val;
        if (imageExists(er.resultString)) {
          er.resultMat = retrieveImage(er.resultString);
          er.resultType = RESULT_MATRIX;
          std::cout << "Added matrix argument " << er.resultString << std::endl;
        } else {
          er.resultType = RESULT_STRING;
          std::cout << "Added literal argument " << er.resultString << std::endl;
        }
        
        arguments.push_back(er);
      } else {
        RoopList tempRes = eval(current);
        if (exceptionBitSet) {
          return result;  // Some invalid operation found
        }
        arguments.insert(arguments.end(), tempRes.begin(), tempRes.end());
      }
      current = current->next;
    }
    
    std::cout << "Processing operation " << operation << " with args: " << std::endl;
    
    for (size_t i=0; i<arguments.size(); i++) {
      EvalResult i_er = arguments[i];
      
      if (i_er.resultType == RESULT_STRING) {
        std::cout << "string = " << i_er.resultString << std::endl;
      } else {
        std::cout << "MATRIX" << std::endl;
      }
      
    }
    
    if (commands.find(operation) != commands.end()) {
      result = commands[operation]->execute(*this, arguments);
    }
  }
  return result;
}
