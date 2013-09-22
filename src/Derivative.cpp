#include "ExecutableCommand.h"

using namespace cv;

int scale = 1;
int delta = 0;
int ddepth = CV_16S;

Mat LaplaceOperator::execute(std::vector<EvalResult> arguments) {
  Mat result, tempr;
  Mat src_gray = arguments[0].resultMat;
  int kernel_size = atoi(arguments[1].resultString.c_str());
  Laplacian( src_gray, tempr, ddepth, kernel_size, 
     scale, delta, BORDER_DEFAULT );
  convertScaleAbs(tempr , result);
  return result;
}

SobelOperator::SobelOperator(SobelType _type): type(_type) {
}

Mat SobelOperator::execute(std::vector<EvalResult> arguments) {
  Mat grad_x, grad_y, abs_grad_x, abs_grad_y;
  Mat grad;
  Mat src_gray = arguments[0].resultMat;

  /// Gradient X
  if (type == SCHARR) {
    Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
  } else {
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
  }
  convertScaleAbs( grad_x, abs_grad_x );

  /// Gradient Y
  if (type == SCHARR) {
    Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
  } else {
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
  }
  convertScaleAbs( grad_y, abs_grad_y );

  /// Total Gradient (approximate)
  addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

  return grad;
}

