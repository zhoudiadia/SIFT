#include "diff_gauss.h"

IplImage * difference(IplImage * img1, IplImage * img2)
{
  int height = img1->height;
  int width = img1->width;
  assert(height == img2->height && width == img2->width);

  uchar * data1 = (uchar*)img1->imageData;
  uchar * data2 = (uchar*)img2->imageData;

  CvSize sz = {width, height};
  IplImage * difference = cvCreateImage(sz, img1->depth, 1);
  uchar * diff_data = (uchar*)difference->imageData;
  int width_step = img1->widthStep;


  for(int i=0;i<height;++i)
  {
    for(int j=0;j<width;++j)
    {
      int curr_px = i*width + j;
      diff_data[curr_px] = abs(data1[curr_px] - data2[curr_px]);
      if(diff_data[curr_px] < 16)
        diff_data[curr_px] *= diff_data[curr_px];
      else
        diff_data[curr_px] = 255;

      if(diff_data[curr_px] < 10)
        diff_data[curr_px] = 0;
    }
  }

  return difference;
}

IplImage ** difference_octave(IplImage ** octave, int scales)
{
  IplImage ** dog_octave = new IplImage*[scales-1];
  for(int i=0;i<scales-1;++i)
  {
    dog_octave[i] = difference(octave[i], octave[i+1]);
  }

  return dog_octave;
}

IplImage *** difference_scale_space(IplImage *** scale_space,
                                    int octaves,
                                    int scales)
{

  IplImage *** dog = new IplImage**[octaves];
  for(int i=0;i<octaves;++i)
  {
    dog[i] = difference_octave(scale_space[i], scales);
    std::cout << "difference of gaussian done for octave " << i+1 << std::endl;
  }
  return dog;
}