#include "greyscale.h"

IplImage * greyscale(IplImage * img)
{
  CvSize sz = {img->width, img->height};
  IplImage * grey = cvCreateImage(sz, img->depth, 1);
  cvCvtColor( img, grey, CV_RGB2GRAY );
  return grey;
}