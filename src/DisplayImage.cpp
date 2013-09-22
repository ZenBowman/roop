#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

uchar clamp(uchar oldValue, uchar max) {
  if (oldValue > max) {
    return max;
  }
  return oldValue;
}

int main( int argc, char** argv )
{
  Mat image;
  image = imread( argv[1], 1 );

  if( argc != 2 || !image.data )
    {
      printf( "No image data \n" );
      return -1;
    }

  Mat image2(200, 200, CV_8UC3, Scalar(0, 255, 0));
  imshow("Test image", image2);
  waitKey(0);

  namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
  imshow( "Display Image", image );
  waitKey(0);

  std::cout << "The image has "<< image.rows << " rows"
	    << " and " << image.cols << " columns" << std::endl;

  Mat_<Vec3b> imageData = image;
  for (size_t i=0; i<image.rows; i++) {
    for (size_t j=0; j<image.cols; j++) {
      imageData(i, j)[0] = clamp(imageData(i, j)[0]+100, 255);
      imageData(i, j)[1] = clamp(imageData(i, j)[1], 200);
      imageData(i, j)[2] = clamp(imageData(i, j)[2], 200);
    }
    if (i % 100 == 0) {
      imshow("Display Image", image);
      waitKey(0);
    }
  }

  return 0;
}
