
#include <opencv2/opencv.hpp>
#include <iostream>
#include "VanishingPoint/vanishpoint.h"


 using namespace cv;
 using namespace std;

/* -------------------------------------- main --------------------------------------------*/
 int main()
 {
   vanishpoint vp;

     vp.init("/home/yrsn/Videos/video_.mp4");

    return 0;
}
