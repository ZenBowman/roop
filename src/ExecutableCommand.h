#ifndef EXECUTABLE_COMMAND_H
#define EXECUTABLE_COMMAND_H

#include <opencv2/opencv.hpp>

enum ResultType {
  RESULT_MATRIX,
  RESULT_STRING
};

struct EvalResult {
  cv::Mat resultMat;
  std::string resultString;
  ResultType resultType;
};

typedef std::vector<EvalResult> RoopList;

RoopList fromMatrix(cv::Mat matrix);

class ExecutableCommand {
 public:
  virtual RoopList execute(RoopList arguments) = 0;
};

class LoadImage: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};

class ErodeImage: public ExecutableCommand {
public:
  RoopList execute(RoopList arguments);
};

class DilateImage: public ExecutableCommand {
public:
  RoopList execute(RoopList arguments);
};


class SubtractImage: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};

class AddImage: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};

class DefImage: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};

class GetImage: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};

class EnhanceContrast: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};

class Sharpen: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};


class Blur: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};

class Filter3: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};


class ToColor: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};

class ToGrayScale: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};

enum SobelType {
  SOBEL,
  SCHARR
};

class SobelOperator: public ExecutableCommand {
 public:
  SobelOperator(SobelType type);
  RoopList execute(RoopList arguments);
 private:
  SobelType type;
};

class LaplaceOperator: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};


class CannyOperator: public ExecutableCommand {
 public:
  RoopList execute(RoopList arguments);
};

class ScalarMultiply: public ExecutableCommand {
public:
  RoopList execute(RoopList arguments);
};

#endif
