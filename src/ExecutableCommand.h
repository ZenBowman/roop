#ifndef EXECUTABLE_COMMAND_H
#define EXECUTABLE_COMMAND_H

#include <opencv2/opencv.hpp>

class RoopMachine;

enum ResultType {
  RESULT_MATRIX,
  RESULT_STRING
};

struct EvalResult {
  cv::Mat resultMat;
  std::string resultString;
  ResultType resultType;

  EvalResult();
  EvalResult(double dValue);
  EvalResult(std::string resultString);
};

typedef std::vector<EvalResult> RoopList;

RoopList fromMatrix(cv::Mat matrix);

class ExecutableCommand {
 public:
  virtual RoopList execute(RoopMachine &machine, RoopList arguments) = 0;
};

class ResizeImage: public ExecutableCommand {
public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class LoadImage: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class ErodeImage: public ExecutableCommand {
public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class DilateImage: public ExecutableCommand {
public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};


class SubtractImage: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class AddImage: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class DefImage: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class GetImage: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class EnhanceContrast: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class Sharpen: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};


class Blur: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class Filter3: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};


class ToColor: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class ToGrayScale: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

enum SobelType {
  SOBEL,
  SCHARR
};

class SobelOperator: public ExecutableCommand {
 public:
  SobelOperator(SobelType type);
  RoopList execute(RoopMachine &machine, RoopList arguments);
 private:
  SobelType type;
};

class LaplaceOperator: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};


class CannyOperator: public ExecutableCommand {
 public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class ScalarMultiply: public ExecutableCommand {
public:
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class ToBinary: public ExecutableCommand {
public:
    RoopList execute(RoopMachine &machine, RoopList arguments);
};

class GetForegroundMaskGrabcut: public ExecutableCommand {
public:
    RoopList execute(RoopMachine &machine, RoopList arguments);
};

class RemoveBackgroundGrabcut: public ExecutableCommand {
public:
    RoopList execute(RoopMachine &machine, RoopList arguments);
};

class InvertImage: public ExecutableCommand {
public:
    RoopList execute(RoopMachine &machine, RoopList arguments);
};

class AndImage: public ExecutableCommand {
public:
    RoopList execute(RoopMachine &machine, RoopList arguments);
};

class SaveImage: public ExecutableCommand {
public:
    RoopList execute(RoopMachine &machine, RoopList arguments);
};

class FindConnected: public ExecutableCommand {
public:
    RoopList execute(RoopMachine &machine, RoopList arguments);
};

class GetCentroid: public ExecutableCommand {
public:
    RoopList execute(RoopMachine &machine, RoopList arguments);
};

class GetArea: public ExecutableCommand {
public:
    RoopList execute(RoopMachine &machine, RoopList arguments);
};

class GetMoments: public ExecutableCommand {
public:
    RoopList execute(RoopMachine &machine, RoopList arguments);
};

class WriteParams: public ExecutableCommand {
 private:
  bool append;
 public:
  WriteParams(bool newFile);
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

class GammaGray: public ExecutableCommand {
  RoopList execute(RoopMachine &machine, RoopList arguments);
};

#endif
