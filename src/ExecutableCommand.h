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

class ExecutableCommand {
 public:
  virtual cv::Mat execute(std::vector<EvalResult> arguments) = 0;
};

class LoadImage: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class ErodeImage: public ExecutableCommand {
public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class DilateImage: public ExecutableCommand {
public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};


class SubtractImage: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class AddImage: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class DefImage: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class GetImage: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class EnhanceContrast: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class Sharpen: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};


class Blur: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class Filter3: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};


class ToColor: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class ToGrayScale: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

enum SobelType {
  SOBEL,
  SCHARR
};

class SobelOperator: public ExecutableCommand {
 public:
  SobelOperator(SobelType type);
  cv::Mat execute(std::vector<EvalResult> arguments);
 private:
  SobelType type;
};

class LaplaceOperator: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};


class CannyOperator: public ExecutableCommand {
 public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

class ScalarMultiply: public ExecutableCommand {
public:
  cv::Mat execute(std::vector<EvalResult> arguments);
};

#endif
