#pragma once
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/rgbd/kinfu.hpp>
#include <OpenNI.h>
#include "kinectData.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>


using namespace cv;
using namespace std;
using namespace openni;
using namespace cv::kinfu;

namespace kinectDeviceDefaultParams//my kinect specifications
{
    static const Size frameSize = Size(640, 480);
    static const float focal = 571.26f;
    static const float cx = 320.0f; //principal point x
    static const float cy = 240.0f; // principal point y

};

void updateParams(Params& params);//update my kinect parameters

