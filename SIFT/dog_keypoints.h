#include <cv.h>
#include <highgui.h>

#ifndef DOG_KEYPOINTS_SIFT
#define DOG_KEYPOINTS_SIFT

IplImage *** keypoint_dog(IplImage *** dog, int octaves, int scales);

#endif