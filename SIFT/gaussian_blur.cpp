#include "gaussian_blur.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include <string>

IplImage * gaussianBlur(IplImage * const img, double sigma)
{
	IplImage * img_copy = cvCloneImage(img);
  uchar * data = (uchar *)img_copy->imageData;
  uchar * ori_data = (uchar *)img->imageData;
  int step_sz = img_copy->widthStep;

  const int kernal_sz = (int)ceil(6*sigma);
  const int center = kernal_sz / 2;

  std::cout << "Kernal sz: " << kernal_sz << std::endl;

  double PI = std::atan(1.0)*4.0;
  double normalization_factor = 2.0*PI*sigma*sigma;
  double ** kernal = new double*[kernal_sz];
  for(int i=0;i<kernal_sz;++i)
  {
    kernal[i] = new double[kernal_sz];
    for(int j=0;j<kernal_sz;++j)
    {
      double x = std::abs(i-center);
      double y = std::abs(j-center);
      kernal[i][j] = exp(-1.0 * (x*x + y*y) / (2*sigma*sigma));
      kernal[i][j] /= normalization_factor;
    }
  }

  int channels = img_copy->nChannels;
	for(int i=0;i<img_copy->height;++i)
	{
		for(int j=0;j<img_copy->width;++j)
		{
      for(int k=0;k<channels;++k)
      {
        double kernal_total = 0;
        for(int a=0;a<kernal_sz;++a)
        {
          for(int b=0;b<kernal_sz;++b)
          {
            int delta_j = b - center;
            int delta_i = a - center;
            if(i + delta_i >= 0 && i + delta_i < img_copy->height &&
              j + delta_j >= 0 && j + delta_j < img_copy->width)
            {
              kernal_total += kernal[a][b];
            }
          }
        }

        double compensation = 1.0 / kernal_total;
        double new_value = 0;
        for(int a=0;a<kernal_sz;++a)
        {
          for(int b=0;b<kernal_sz;++b)
          {
            int delta_j = b - center;
            int delta_i = a - center;
            if(i + delta_i >= 0 && i + delta_i < img_copy->height &&
              j + delta_j >= 0 && j + delta_j < img_copy->width)
            {
              double curr_value = 
                ori_data[(i+delta_i)*step_sz + (j+delta_j)*channels + k];
              new_value += curr_value*kernal[a][b]*compensation;
            }
          }
        }
        data[i*step_sz + j*channels + k] = new_value;
      }
		}
	}
	return img_copy;
}