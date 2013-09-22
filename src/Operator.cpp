#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Blurrer.h"
#include "sexp.h"

using namespace cv;

const int erosion_type = MORPH_RECT;

int main( int argc, char** argv )
{
  char* operation = argv[1];

  Mat image1, image2;
  image1 = imread( argv[2], 1 );

  std::cout << "Performing operation " << operation << std::endl;

  imshow("Original", image1);
  waitKey(0);

  Mat element;

  if (strcmp(operation, "erode") == 0) {
    int erosion_size = atoi(argv[3]);
    int erosion_pt = atoi(argv[4]);
    element = getStructuringElement(erosion_type, Size(erosion_size, erosion_size), Point(erosion_pt,erosion_pt));
    erode(image1, image2, element);
    imshow("Erosion Demo", image2);
    waitKey(0);

    Mat image3 = image1 - image2;
    imshow("Original - erosion", image3);
    waitKey(0);

  }

 
  return 0;
}
