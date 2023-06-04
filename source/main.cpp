#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "LaneDetection/laneDetection.h"
#include "utils/calibration.h"
#include "utils/functions.h"
//#include "vanishpoint.h"
#include "utils/transformation.h"


char key = 0;
int main(int argc, char **argv)
{
    cout<<argv[1]<<endl;


    cv::VideoCapture cap("/home/fondecyt/Vídeos/video_.mp4");

    // Verifica si se puede abrir el video de entrada
    if (!cap.isOpened()) {
        std::cerr << "Error al abrir el video de entrada." << std::endl;
        return -1;
    }

    // Procesa el video cuadro por cuadro
    cv::Mat frame;
    while (cap.read(frame)) {
        // Procesa el cuadro aquí
        // ...

        // Muestra el cuadro procesado en una ventana
        cv::imshow("Video", frame);

        // Espera 25 milisegundos para que se muestre el cuadro en la ventana
        cv::waitKey(25);
    }

    // Libera los recursos
    cap.release();
    cv::destroyAllWindows();
    return 0;

}
