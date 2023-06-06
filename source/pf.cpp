// .pf.cpp
#include <iostream>
#include <random>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "ParticleFilter/particle.h"
#include "utils/functions.h"
#include "VanishingPoint/vanishpoint.h"
#include <opencv2/imgproc/types_c.h>
#include "control/ctello.h"

using namespace std;
using namespace cv;

funciones f;
vanishpoint vp;

Mat Frame;
Mat capFrame;
Mat refMask;
Size objectSize(40,40);
Point MroiPoint;

//drone config
const char* const TELLO_STREAM_URL{"udp://0.0.0.0:11111"};
ctello::Tello tello;

using ctello::Tello;
using cv::CAP_FFMPEG;
using cv::imshow;
using cv::VideoCapture;
using cv::waitKey;


int main()
{
    if (!tello.Bind())
        {
            return 0;
        }

    tello.SendCommand("streamon");
    while (!(tello.ReceiveResponse()));

    int mParticles = 4000;
    Mat Mesampling;



    //VideoCapture cap("/home/yerson/Videos/video_.mp4");
    VideoCapture capture{TELLO_STREAM_URL, CAP_FFMPEG};
    //VideoCapture cap("/home/fondecyt/Vídeos/video_.mp4");

    /*
    cap >> Frame;





    vp.vp(Frame,refMask);
    cv::cvtColor(refMask, refMask, cv::COLOR_GRAY2BGR);
    f.getCenter(refMask,MroiPoint);

    capFrame = refMask.clone();
    Particle MyparticleAlgo(refMask, capFrame, mParticles, objectSize, MroiPoint);
*/

    while(!capFrame.empty())
    {
        cv::Mat frame;
        capture >> frame;

        /*
        // Listen response
        if (const auto response = tello.ReceiveResponse())
        {
            std::cout << "Tello: " << *response << std::endl;
            busy = false;
        }


        Mesampling = capFrame.clone();
        //To initialize the particles
        if(cap.get(CAP_PROP_POS_FRAMES)==1)
        {
            MyparticleAlgo.setInputImage(capFrame);
            MyparticleAlgo.generateParticlesInit();
            Mesampling = MyparticleAlgo.getParticleImage().clone();
            namedWindow("MParticles",WINDOW_NORMAL);
            imshow("MParticles", Mesampling);
            capFrame = MyparticleAlgo.getTarget().clone();
        }
        //Frame by frame tracking
        if(cap.get(CAP_PROP_POS_FRAMES)>1)
        {
            MyparticleAlgo.setInputImage(capFrame);
            MyparticleAlgo.particleAlgo();
            capFrame = MyparticleAlgo.getTarget().clone();
            Mesampling = MyparticleAlgo.getParticleImage().clone();
            imshow("MParticles", Mesampling);
        }

        imshow("track frame",capFrame);
        */


          imshow("frame",frame);
        if(waitKey(10) == 27) break;

        /*
        cap >> capFrame;
        imshow("frame",f.ResizeImage(capFrame,0.5));
        vp.vp(capFrame,refMask);
        cv::cvtColor(refMask, capFrame, cv::COLOR_GRAY2BGR);

        */
    }


    waitKey(0);
    return 0;

}
