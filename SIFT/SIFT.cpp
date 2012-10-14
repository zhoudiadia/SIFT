#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include <string>
#include "gaussian_blur.h"
#include "scale_space.h"
#include "greyscale.h"
#include "diff_gauss.h"
#include "dog_keypoints.h"

int main(int argc, char *argv[])
{
	// load an image
	std::string file_path = "C:\\sp\\p.jpg";
	IplImage * img = cvLoadImage(file_path.c_str());
	if(!img){
		printf("Could not load image file: %s\n", file_path.c_str());
		exit(-1);
	}

  IplImage * full_color_img = img;
  img = greyscale(full_color_img);

	// get the image data
	int height    = img->height;
	int width     = img->width;
	int channels  = img->nChannels;
	printf("Processing a %dx%d image with %d channels\n",height,width,channels); 

	// create a window
	cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
	cvMoveWindow("mainWin", 400, 30);

  int octaves = 4;
  int scales = 5;
  IplImage *** scale_space = generate_scale_space(img, octaves, scales);
  IplImage *** diff_of_gauss = 
    difference_scale_space(scale_space, octaves, scales);
  IplImage *** keypoint_imgs = keypoint_dog(diff_of_gauss, octaves, scales);

  std::ofstream fout("C:\\sp\\mc.txt");
  uchar * sample = (uchar*)diff_of_gauss[3][2]->imageData;
  for(int i=0;i<diff_of_gauss[3][2]->height;++i)
  {
    for(int j=0;j<diff_of_gauss[3][2]->width;++j)
    {
      fout << (int)sample[i*diff_of_gauss[3][2]->widthStep + j] << " ";
    }
    fout << "\n";
  }
  fout.flush();
  fout.close();

  IplImage * display_image = keypoint_imgs[ 3][0];
	cvShowImage("mainWin", display_image);

  const char * outfile = "C:\\sp\\out.jpg";
  const char * del_outfile = "DEL /F C:\\sp\\out.jpg";
  std::ifstream fin(outfile);
  if (fin)
  {
      std::cout << "File found, deleting..." << std::endl;
      system(del_outfile);
      fin.close();
  }
  
  if(!cvSaveImage(outfile, display_image)) 
    printf("Could not save: %s\n", outfile);

	// wait for a key
	cvWaitKey(0);

	// release the image
	cvReleaseImage(&img);
	return 0;
}