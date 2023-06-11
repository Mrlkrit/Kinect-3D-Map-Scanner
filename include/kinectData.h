#pragma once
#include <OpenNI.h>
#include <opencv2/opencv.hpp>
#include <vector>


using namespace openni;
using namespace std;
using namespace cv;

class OpenCVKinect
{
	Status kinectStatus; 
	Device kinect;
	VideoStream depthStream, ** kinectStreams;
	VideoFrameRef depthFrame;
	uint64_t TimeStamp; // to indicate if frames are flowing 
	Mat depthImage; // output depth image
	bool streamStatus; // status of data acquirement
	int currentStream;
public:
	OpenCVKinect(void);
	bool setMode(int inMode);//declare getting depth mode only
	bool init();//initialize kinect device
	Mat getData();//get depth image
	~OpenCVKinect(void);
};