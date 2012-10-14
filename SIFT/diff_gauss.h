#include <cv.h>
#include <highgui.h>

#ifndef DIFF_GAUSS_SIFT
#define DIFF_GAUSS_SIFT

IplImage * difference(IplImage * img1, IplImage * img2);

IplImage ** difference_octave(IplImage ** octave, int scales);

IplImage *** difference_scale_space(IplImage *** scale_space,
                                    int octaves,
                                    int scales);

#endif