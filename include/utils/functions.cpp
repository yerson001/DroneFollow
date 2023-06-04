// .cpp functions file
#include "functions.h"

void funciones::ReadVideo()
{
    Point2f perspectiveSrc[] = {
        Point2f(570,300),
        Point2f(1000,300),
        Point2f(170,698),
        Point2f(1300,698)
    };

    Point2f perspectiveDst[] = {
        Point2f(0,0),
        Point2f(1280,0),
        Point2f(0,720),
        Point2f(1280,720)
    };
   Mat temp,temp1;
    VideoCapture cap("/home/yrsn/Videos/video_.mp4");
    int lowH = 0; int highH = 26;
    int lowS = 98; int highS = 118;
    int lowV = 71;  int highV = 183;
    while(1){
       Mat frame;
       Mat frame1;
       Mat output;
       Mat edgeImage;
       cap >> frame;
       if (frame.empty())
         break;

       frame1  = frame.clone();

       circle(frame1,perspectiveSrc[0], 3, Scalar(0,255,0), FILLED);
       circle(frame1,perspectiveSrc[1], 3, Scalar(0,255,0), FILLED);
       circle(frame1,perspectiveSrc[3], 3, Scalar(0,255,0), FILLED);
       circle(frame1,perspectiveSrc[2], 3, Scalar(0,255,0), FILLED);
       line(frame1, perspectiveSrc[0], perspectiveSrc[1], Scalar(255,0,0), 1);
       line(frame1, perspectiveSrc[1], perspectiveSrc[3], Scalar(255,0,0), 1);
       line(frame1, perspectiveSrc[3], perspectiveSrc[2], Scalar(255,0,0), 1);
       line(frame1, perspectiveSrc[2], perspectiveSrc[0], Scalar(255,0,0), 1);


       Mat Matrix = getPerspectiveTransform(perspectiveSrc,perspectiveDst);
       warpPerspective(frame, output, Matrix,Size(1280,720));


       //temp = bordes(frame,62);
       //temp1 = dilatacion(temp,1.5);
       imshow( "scena-with-roci estract", frame1);
      // imshow( "original - video", frame);
       imshow( "perspective transforme", output);

       Mat imgHSV;
       cvtColor(output, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV color space

       Mat imgThresholded;
       inRange(imgHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), imgThresholded);
       imshow("imagethres",imgThresholded);

       //bool check = imwrite("/home/yrsn/Dev/PFCII/img/line.jpg", output);

//           Canny(output, edgeImage, 100, 150, 3);
//           temp = bordes(output,40);
//           temp1 = dilatacion(temp,1);

       //imshow( "canny-filter", edgeImage);
       //imshow( "final result", temp1);
       //imshow( "Frame", frame);
       char c=(char)waitKey(25);
       if(c==27)
         break;
     }
     cap.release();
     destroyAllWindows();
}

Mat funciones::ResizeImage(Mat &image, float scale)
{
    Mat resized;
    resize(image, resized, Size(image.cols*scale, image.rows*scale), INTER_LINEAR);
    return resized;
}

Mat funciones::bordes(Mat image,int level)
{
   Mat gray,canny,dst,out;
   cvtColor(image,gray,COLOR_BGR2GRAY);
   blur(gray,canny,cv::Size(3,3));

   Canny(canny,out,level,level*3,3);
   dst.create(image.size(),image.type());
   return out;
}

Mat funciones::dilatacion(Mat image ,int dilation_size)
{
   Mat out,dilation_dst;
   int dilation_type = MORPH_RECT;

   Mat element = getStructuringElement(
         dilation_type,Size(2*dilation_size+1,2*dilation_size+1),
         Point(dilation_size,dilation_size)
         );
   dilate(image,out,element);
  return out;
}

Mat funciones::getCenter(Mat img,Point &pos)
{
  Mat grayImage;
  cvtColor(img, grayImage, COLOR_BGR2GRAY);

  cv::Mat binary_image;
  cv::threshold(grayImage, binary_image, 128, 255, cv::THRESH_BINARY);

  // Encontrar los contornos de la imagen
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(binary_image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  // Recorrer los contornos encontrados
  for (int i = 0; i < contours.size(); i++) {
      // Calcular el centro del objeto
      cv::Moments moments = cv::moments(contours[i]);
      double cx = moments.m10 / moments.m00;
      double cy = moments.m01 / moments.m00;

      // Dibujar el centro del objeto en la imagen
      cv::circle(grayImage, cv::Point(cx, cy), 5, cv::Scalar(255), -1);

      // Dibujar el contorno del objeto en la imagen
      cv::drawContours(grayImage, contours, i, cv::Scalar(255), 2);
      pos.x = cx;
      pos.y = cy;
  }

  // Mostrar la imagen con el centro y el contorno del objeto
  //cv::imshow("Image", img);
  return grayImage;
}



bool funciones::compare(Mat img1,Mat img2)
{
  // Verificar si las imágenes tienen el mismo tamaño
  if (img1.size() != img2.size()) {
      std::cout << "Las imágenes no son iguales: tienen tamaños diferentes." << std::endl;
      //return 0;
  }

  // Comparar las imágenes pixel por pixel
  for (int i = 0; i < img1.rows; i++) {
      for (int j = 0; j < img1.cols; j++) {
          if (img1.at<cv::Vec3b>(i,j) != img2.at<cv::Vec3b>(i,j)) {
              std::cout << "Las imágenes no son iguales: los valores de píxeles difieren." << std::endl;
              return 0;
          }
      }
  }

  std::cout << "Las imágenes son iguales." << std::endl;
  return 1;
}


bool funciones::compareColor(Mat img1,Mat img2)
{

  // Obtener los espacios de color de las imágenes
//  int colorSpace1;
//  colorSpace1 = cv::cvtColor(img1, img1, cv::COLOR_BGR2GRAY);
//  int colorSpace2 = cv::cvtColor(img2, img2, cv::COLOR_BGR2GRAY);

//  // Verificar si los espacios de color son iguales
//  if (colorSpace1 != colorSpace2) {
//      std::cout << "Las imágenes no están en el mismo espacio de color." << std::endl;
//      return 0;
//  }

//  std::cout << "Las imágenes están en el mismo espacio de color." << std::endl;
  return 1;
}
