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
using namespace std;
using namespace cv;

funciones f;
vanishpoint vp;

Mat Frame;
Mat capFrame;
Mat refMask;
Size objectSize(40,40);
Point MroiPoint;

int main()
{
    int mParticles = 4000;
    Mat Mesampling;

    //VideoCapture cap("/home/yrsn/Videos/video_.mp4");
    VideoCapture cap("/home/fondecyt/Vídeos/video_.mp4");
    cap >> Frame;

    vp.vp(Frame,refMask);
    cv::cvtColor(refMask, refMask, cv::COLOR_GRAY2BGR);
    f.getCenter(refMask,MroiPoint);

    capFrame = refMask.clone();
    Particle MyparticleAlgo(refMask, capFrame, mParticles, objectSize, MroiPoint);


    while(!capFrame.empty())
    {
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
        if(waitKey(10) == 27) break;

        cap >> capFrame;
        imshow("frame",f.ResizeImage(capFrame,0.5));
        vp.vp(capFrame,refMask);
        cv::cvtColor(refMask, capFrame, cv::COLOR_GRAY2BGR);
    }


    waitKey(0);
    return 0;

}
