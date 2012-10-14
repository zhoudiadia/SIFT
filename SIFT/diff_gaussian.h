#include <cv.h>
#include <highgui.h>

#ifndef DIFF_GAUSSIAN_SIFT
#define DIFF_GAUSSIAN_SIFT

IplImage *** diff_of_gaussian(IplImage *** const scale_space, 
                              int octaves, 
                              int scales);

#endif