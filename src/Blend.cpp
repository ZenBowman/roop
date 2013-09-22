#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;


int main( int argc, char** argv )
{
  Mat image1, image2, image3;
  float alpha;

  image1 = imread( argv[1], 1 );
  image2 = imread( argv[2], 1);
  alpha = atof(argv[3]);

  imshow("First", image1);
  waitKey(0);

  addWeighted(image1, alpha, image2, 1.0-alpha, 0.0, image3);

  imshow("Blended", image3);
  waitKey(0);
 
  return 0;
}
