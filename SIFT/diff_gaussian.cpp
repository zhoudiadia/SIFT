#include "diff_gaussian.h"

IplImage *** diff_of_gaussian(IplImage *** const scale_space,
                              int octaves, 
                              int scales)
{
  IplImage *** dog = new IplImage**[octaves];
  for(int i=0;i<octaves-1;++i)
  {
    dog[i] = new IplImage*[scales-1];
  }


}