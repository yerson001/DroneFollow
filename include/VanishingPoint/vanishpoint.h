// vanishpoint clas// vanishpoint classs
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ios>
#include <opencv2/imgproc/imgproc_c.h>
//#include "main_func.h"
#define CENTER_RANGE 0.1
#define PI 3.1415926

using namespace std;
using namespace cv;

class vanishpoint
{
private:
  Point current;
public:

  bool hough_line_detect(Mat & image, Mat & cdst, vector<Vec2f> & left_lines, vector<Vec2f> & right_lines);

  bool draw_line(Mat & image, vector<Vec2f> & vec_lines, Scalar color);

  Point get_vanish_point(vector<Point> & points);

  Point vanish_point_detection(Mat & image, Mat & cdst);

  Point vp(Mat image,Mat &);

  void init(string name);
};
