//class functions
#include<opencv2/calib3d.hpp>
#include<opencv2/core/types.hpp>
#include<opencv2/core/persistence.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/core/types_c.h>
#include<iostream>
using namespace cv;
using namespace std;

class funciones{

 public:

    void ReadVideo();

    Mat ResizeImage(Mat &image, float scale);

    Mat bordes(Mat image,int level);

    Mat dilatacion(Mat image ,int dilation_size);

    Mat getCenter(Mat img,Point &pos);
    bool compare(Mat img1,Mat img2);
    bool compareColor(Mat img1,Mat img2);
};

