// .cpp file
#include "vanishpoint.h"

bool vanishpoint::hough_line_detect(Mat & image, Mat & cdst, vector<Vec2f> & left_lines, vector<Vec2f> & right_lines)
{
    //imshow("img",image);
    Mat dst;

    Mat img_blur;
    GaussianBlur(image, img_blur, Size(3,3), 7);


    // int lowH = 0; int highH = 26;
    // int lowS = 98; int highS = 118;
    // int lowV = 71;  int highV = 183;

    // //canny
    // Mat oriImageGray;
    // //imshow("recibido",oriImage);
    // cvtColor(image, oriImageGray, COLOR_RGB2GRAY);


    // //Canny(oriImageGray, edgeImage, 100, 150, 3);
    // Mat imgHSV;

    // cvtColor(image, imgHSV, COLOR_BGR2HSV);
    //imshow("erode",imgHSV);

    Canny(img_blur, dst, 25, 90, 3);
    //imshow("canni",dst);

    //  cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
    //  cv::Mat dstt;
    //  cv::dilate(dst, dstt, kernel, cv::Point(-1, -1), 1);

    //cvtColor(dst, cdst, COLOR_GRAY2BGR);

    vector<Vec2f> lines;
    // detect lines


    HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0);
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        if (10 * PI / 180 < theta && theta < 60 * PI / 180) {
            left_lines.push_back(lines[i]);
        } else if (110 * PI / 180 < theta && theta < 170 * PI / 180) {
            right_lines.push_back(lines[i]);
        }
    }
    return true;
}

bool vanishpoint::draw_line(Mat & image, vector<Vec2f> & vec_lines, Scalar color)
{
    for (size_t i = 0; i < vec_lines.size(); ++i) {
        float rho = vec_lines[i][0], theta = vec_lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        cv::line(image, pt1, pt2, color, 3, LINE_AA);
    }
    return true;
}


Point vanishpoint::get_vanish_point(vector<Point> & points)
{
    long x = 0, y = 0;
    if (points.size() == 0) {
        return Point(0, 0);
    }
    for (size_t i = 0; i < points.size(); ++i) {
        x += points[i].x;
        y += points[i].y;
    }
    x /= points.size();
    y /= points.size();
    Point vp(x, y);
    //circle(cdst, vp, 5, Scalar(0, 0, 0),5 );
    return vp;
}

Point vanishpoint::vanish_point_detection(Mat & image, Mat & cdst)
{
    Mat dst;
    vector<Vec2f> left_lines;
    vector<Point> Intersection;
    vector<Vec2f> right_lines;
    hough_line_detect(image, cdst, left_lines, right_lines);
    draw_line(cdst, left_lines, Scalar(0, 255, 0));
    draw_line(cdst, right_lines, Scalar(255, 0, 0));
    size_t i = 0, j = 0;
    //long sum_x = 0;
    //long sum_y = 0;
    double x = 0;
    double y = 0;
    Canny(image, dst, 25, 90, 3);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);

    vector<Vec2f> lines;
    //detect lines
    HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0);

    //// draw lines
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        if (10 * PI / 180 < theta && theta < 60 * PI / 180) {
            line(image, pt1, pt2, Scalar(0, 255, 0), 3, LINE_AA);
        } else if (110 * PI / 180 < theta && theta < 170 * PI / 180) {
            line(image, pt1, pt2, Scalar(255, 0, 0), 3, LINE_AA);
        } else {
            line(image, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
        }
    }
    for (i = 0; i < left_lines.size(); ++i) {
        for (j = 0; j < right_lines.size(); ++j) {
            float rho_l = left_lines[i][0], theta_l = left_lines[i][1];
            float rho_r = right_lines[j][0], theta_r = right_lines[j][1];
            double denom = (sin(theta_l) * cos(theta_r) - cos(theta_l) * sin(theta_r));
            x = (rho_r * sin(theta_l) - rho_l * sin(theta_r)) / denom;
            y = (rho_l * cos(theta_r) - rho_r * cos(theta_l)) / denom;
            //cout<<"("<<x<<","<<y<<")"<<endl;
            Point pt(x, y);
            Intersection.push_back(pt);
            circle(image, pt, 5, Scalar(0, 0, 0),5 );
        }
    }
    // ************************++image with lines*******************************
    imshow("lines",image);


    return get_vanish_point(Intersection);
}


Point vanishpoint::vp(Mat image,Mat &maskara){
    Point mark_point, current_point;
    Mat outImage;
    Mat imresize;

    Mat dst, cdst;
    cv::Mat mask(image.size(), CV_8UC1, cv::Scalar(0));
    float size = 50;
    size = size/100;

    //    cout<<"size: "<<size<<endl;
    resize(image, outImage, cv::Size(), size, size);
    resize(mask, maskara, cv::Size(),0.5, 0.5);
    //    cout<<outImage.cols<<endl;
    //    cout<<outImage.rows<<endl;
    mark_point = vanish_point_detection(outImage, cdst);

    resize(image, imresize, cv::Size(),0.5, 0.5);



    line(imresize, Point(mark_point.x + 25, image.rows/4), Point(mark_point.x - 25, image.rows/4), Scalar(0, 0, 255),1);
    line(imresize, Point(mark_point.x, image.rows/4 + 25), Point(mark_point.x, image.rows/4 - 25), Scalar(0, 0, 255),1);
    circle(imresize,Point(mark_point.x,image.rows/4), 20, Scalar(60,233,239), FILLED);

    line(imresize, Point(10,180), Point(630,180), Scalar(0, 120, 25),1);
    line(imresize, Point(320,10), Point(320,350), Scalar(0, 120, 25),1);
    //circle(imresize,Point(vpts.x,im.rows/4), 20, Scalar(60,233,239),1);
    //  //******************************* final mask to show*******************************
    imshow("VP", imresize);

    line(maskara, Point(mark_point.x + 25, image.rows/4), Point(mark_point.x - 25, image.rows/4), Scalar(0, 0, 255),1);
    line(maskara, Point(mark_point.x, image.rows/4 + 25), Point(mark_point.x, image.rows/4 - 25), Scalar(0, 0, 255),1);
    circle(maskara,Point(mark_point.x,image.rows/4), 20, Scalar(200,233,239), FILLED);

    //******************************* final mask to show*******************************
    // cv::imshow("Mask", maskara);

    return mark_point;
}

void vanishpoint::init(string name)
{
    VideoCapture cap;
    Mat im;
    Mat imresize;
    Mat grayresize;
    cap.open(name);
    char key = 0;
    //cv::VideoWriter writer("salida.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 25.0, cv::Size(1280, 720));

    while (key != 27) // press esc to stop
    {
        cap >> im;

        // Crea una máscara del mismo tamaño que la imagen
        cv::Mat mask(im.size(), CV_8UC1, cv::Scalar(0));
        cv::Mat maskara;

        //      // Asigna el valor 255 a los píxeles de la máscara que deseas conservar
        //      cv::Rect roi(100, 100, 200, 200);
        //      mask(roi).setTo(255);

        resize(mask, maskara, cv::Size(),0.5, 0.5);
        //cv::imshow("Mascara", maskara);


        Point vpts = vp(im,maskara);

        resize(im, imresize, cv::Size(),0.5, 0.5);
        cvtColor(imresize, grayresize, COLOR_BGR2GRAY);


        line(imresize, Point(vpts.x + 25, im.rows/4), Point(vpts.x - 25, im.rows/4), Scalar(0, 0, 255),1);
        line(imresize, Point(vpts.x, im.rows/4 + 25), Point(vpts.x, im.rows/4 - 25), Scalar(0, 0, 255),1);
        circle(imresize,Point(vpts.x,im.rows/4), 20, Scalar(60,233,239), FILLED);
        //circle(imresize,Point(vpts.x,im.rows/4), 20, Scalar(60,233,239),1);
        //imshow("VP", imresize);

        line(maskara, Point(vpts.x + 25, im.rows/4), Point(vpts.x - 25, im.rows/4), Scalar(0, 0, 255),1);
        line(maskara, Point(vpts.x, im.rows/4 + 25), Point(vpts.x, im.rows/4 - 25), Scalar(0, 0, 255),1);
        circle(maskara,Point(vpts.x,im.rows/4), 20, Scalar(200,233,239), FILLED);
        // cv::imshow("Mask", maskara);

        key = waitKey(10);
    }
    cap.release();
    //writer.release();
}



