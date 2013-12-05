#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>
#include "ExecutableCommand.h"
#include "RoopCommon.h"
#include "Transform.h"

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
SaveImage saveImage;
FindConnected findConnected;
GetCentroid getCentroid;
GetArea getArea;
WriteParams writeParams(false);
GammaGray gammaGray;

std::auto_ptr<RoopMachine> defaultMachine;

bool isExitCommand(char *lineData) {
  return ((strcmp("exit", lineData) == 0) || (strcmp("(exit)", lineData) == 0));
}

bool isDisplayCommand(char *lineData) {
  return ((strcmp("display", lineData) == 0) || (strcmp("(display)", lineData) == 0));
}

void initRoop() {
  defaultMachine = std::auto_ptr<RoopMachine>(new RoopMachine());
}

RoopList evaluate(std::string command) {
  return defaultMachine->eval(command);
}

bool RoopMachine::imageExists(std::string imageName) {
  return (savedImages.find(imageName) != savedImages.end());
}

Mat RoopMachine::retrieveImage(std::string imageName) {
  return savedImages[imageName];
}


CommandMapIterators getCommandIterator() {
  return defaultMachine->getCommandIterator();
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
  commands["save"] = &saveImage;
  commands["find-connected"] = &findConnected;
  commands["centroid"] = &getCentroid;
  commands["area"] = &getArea;
  commands["writeparams"] = &writeParams;
  commands["gamma-correct-gray"] = &gammaGray;
}


CommandMapIterators RoopMachine::getCommandIterator() {
  CommandMapIterators ci;
  ci.start = commands.begin();
  ci.end = commands.end();
  return ci;
}

std::string toString(RoopList roopList) {
  std::stringstream sstream;
  for (size_t i=0; i<roopList.size(); i++) {
    EvalResult i_er = roopList[i];      
    if (i_er.resultType == RESULT_STRING) {
      sstream << i_er.resultString << "\t";
    } else {
      sstream << "MATRIX" << "\t";
    }
  }
  return sstream.str();
}

RoopList RoopMachine::eval(std::string _command) {
  RoopList result;
  sexp_t* command = parse_sexp((char*)_command.c_str(), strlen(_command.c_str()));

  if (command != NULL) {
    result = eval(command);
    destroy_sexp(command);
  } 

  return result;
}


RoopList RoopMachine::eval(sexp_t* command) {
  elt* current;
  std::string operation;
  RoopList arguments;
  RoopList result;
  
  if (command->ty == SEXP_LIST) {
    operation = command->list->val;
    
    if (operation == "deftransform") {
      std::string transformName = Transform::defineTransform(*this, command);
      result.push_back(EvalResult(transformName));
      return result;
    }

    if ((transforms.find(operation) == transforms.end()) && 
	(commands.find(operation) == commands.end())) {
      std::stringstream exception;
      exception << "Invalid operator " << operation << "found." << std::endl;
      exception >> exceptionMessage;
      exceptionBitSet = true;
      return result;
    }
    
    current = command->list->next;

    while (current != 0) {
      if (current->ty == SEXP_VALUE) {
        EvalResult er;
        er.resultString = current->val;
        if (imageExists(er.resultString)) {
          er.resultMat = retrieveImage(er.resultString);
          er.resultType = RESULT_MATRIX;
        } else {
          er.resultType = RESULT_STRING;
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
  }

  std::cout << "Processing operation " << operation << " with args: "
	    << toString(arguments) << std::endl;
  
  if (commands.find(operation) != commands.end()) {
    result = commands[operation]->execute(*this, arguments);
    std::cout << "Result=" << toString(result) << std::endl;
  }

  if (transforms.find(operation) != transforms.end()) {
    std::cout << "Applying transform " << operation << std::endl;
    result = transforms[operation].execute(*this, arguments);
  }

  return result;
}
