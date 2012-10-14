#include <cv.h>
#include <highgui.h>

#ifndef GAUSSIAN_BLUR_SIFT
#define GAUSSIAN_BLUR_SIFT

IplImage * gaussianBlur(IplImage * const img, double sigma);

#endif