#include "dog_keypoints.h"

IplImage *** keypoint_dog(IplImage *** dog, int octaves, int scales)
{
  --scales; // We lost a scale when applying diff of gaussians.
  IplImage *** keypoint_dog = new IplImage**[octaves];
  for(int i=0;i<octaves;++i)
  {
    keypoint_dog[i] = new IplImage*[scales-2];
    for(int j=0;j<scales-2;++j)
    {
      CvSize sz = {dog[i][0]->width, dog[i][0]->height};
      keypoint_dog[i][j] = cvCreateImage(sz, dog[i][0]->depth, 1);
    }
  }

  for(int i=0;i<octaves;++i)
  {
    for(int j=1;j<scales-1;++j) // Skip first and last
    {
      IplImage * curr_image = dog[i][j];
      uchar * data = (uchar*)curr_image->imageData;
      int height = curr_image->height;
      int width = curr_image->width;
      int width_sz = curr_image->widthStep;
      std::cout << width << " " << width_sz << std::endl;

      uchar * keypoint_data = (uchar*)keypoint_dog[i][j-1]->imageData;
      for(int a=1;a<height-1;++a)
      {
        for(int b=1;b<width_sz-1;++b)
        {
          uchar curr_px = data[a*width_sz + b];

          bool max = true;
          bool min = true;
          for(int d=-1;d<=1;++d)
          {
            for(int dd=-1;dd<=1;++dd) 
            {
              for(int ddd=-1;ddd<=1;++ddd) if(d || dd || ddd)
              {
                IplImage * curr_test_image = dog[i][j+d];
                uchar * curr_test_data = (uchar*)curr_test_image->imageData;
                if(curr_px < curr_test_data[(a+dd)*width_sz + (b + ddd)])
                  max = false;

                if(curr_px > curr_test_data[(a+dd)*width_sz + (b + ddd)])
                  min = false;
              }
           } 
          }

          bool is_keypoint = max ||  min;

          keypoint_data[a*width_sz + b] =
            is_keypoint ? data[a*width_sz + b] : 0;
        }
      }
    }
  }
  return keypoint_dog;
}