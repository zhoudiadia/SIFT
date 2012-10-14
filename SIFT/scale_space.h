#include <cv.h>
#include <highgui.h>

#ifndef SCALE_SPACE_SIFT
#define SCALE_SPACE_SIFT

IplImage *** generate_scale_space(IplImage * img, int octaves, int scales);

#endif