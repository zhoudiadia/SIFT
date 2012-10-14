#include "scale_space.h"
#include "gaussian_blur.h"

IplImage *** generate_scale_space(IplImage * img, int octaves, int scales)
{
  // scale_space[i][j] is the ith octave, jth scale (blur level)
  IplImage *** scale_space = new IplImage**[octaves];
  for(int i=0;i<octaves;++i)
  {
    scale_space[i] = new IplImage*[scales];
  }
  scale_space[0][0] = img;

  for(int i=1;i<octaves;++i)
  {
    IplImage * prev = scale_space[i-1][0];
    int new_height = (int)ceil(prev->height / sqrt(2.0));
    int new_width = (int)ceil(prev->width / sqrt(2.0));

    CvSize new_cvSize = {new_width, new_height};
    IplImage * resized = cvCreateImage(
      new_cvSize, prev->depth, prev->nChannels);

    cvResize(prev, resized);
    scale_space[i][0] = resized;
  }

  double sigma_step = 1 / sqrt(2.0);
  double k_step = 1 / sigma_step;
  for(int i=0;i<octaves;++i)
  {
    for(int j=1;j<scales;++j)
    {
      scale_space[i][j] = gaussianBlur(scale_space[i][j-1], sigma_step);
    }
    sigma_step *= k_step;
  }

  return scale_space;
}