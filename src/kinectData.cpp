#include "kinectData.h"

OpenCVKinect::OpenCVKinect(void)
{
	TimeStamp = 0;
	streamStatus = false;
}

bool OpenCVKinect::setMode(int inMode)
{

	if ((inMode & 0x02) == 0x02)
	{
		cout << "DEPTH" << endl;
		streamStatus = true;
		return true;
	}
	else
	{
		cout << "Depth not acquired" << endl;
		return false;
	}
	return false;
}

bool OpenCVKinect::init()
{

	kinectStatus = STATUS_OK;
	const char* device = ANY_DEVICE;//search for any kinect like device

	kinectStatus = OpenNI::initialize();//load drivers

	cout << "After initialization: " << endl;
	cout << OpenNI::getExtendedError() << endl;


	kinectStatus = kinect.open(device);
	if (kinectStatus != STATUS_OK)
	{
		cout << "OpenCVKinect: Device open failed: " << endl;
		cout << OpenNI::getExtendedError() << endl;
		OpenNI::shutdown();//unload drivers
		return false;

	}
	if (streamStatus)
	{
		
		kinectStatus = depthStream.create(kinect, SENSOR_DEPTH);//create depth object
		if (kinectStatus == STATUS_OK)
		{
			kinectStatus = depthStream.start();//start 
			if (kinectStatus != STATUS_OK)
			{
				cout << "OpenCVKinect: Could not start depth stream: " << endl;
				cout << OpenNI::getExtendedError() << endl;
				depthStream.destroy();//kill data acquisition
				return false;
			}
		}
		else
		{
			cout << "OpenCVKinect: Could not find depth stream: " << endl;
			cout << OpenNI::getExtendedError() << endl;
			return false;

		}


		if (!depthStream.isValid())// check if object is initialised
		{
			cout << "OpenCVKinect: No valid streams. Exiting" << endl;
			OpenNI::shutdown();
			return false;
		}

		this->kinectStreams = new VideoStream * [1];
		kinectStreams[0] = &depthStream;

		return true;
	}


}
	Mat OpenCVKinect::getData()
	{
		
		bool depthCaptured = false;


		if (this->streamStatus)
		{
			while (!depthCaptured)
			{
				kinectStatus = OpenNI::waitForAnyStream(kinectStreams,1, &currentStream, 2000);
				if (kinectStatus != openni::STATUS_OK)
				{
					cout << "OpenCVKinect: Unable to wait for streams. Exiting" << endl;
					exit(EXIT_FAILURE);
				}

				switch (currentStream)
				{
				case 0:
					depthStream.readFrame(&depthFrame);
					depthImage.create(depthFrame.getHeight(), depthFrame.getWidth(), CV_16UC1);
					depthImage.data = (uchar*)depthFrame.getData();
					this->TimeStamp ++;//to know if depth data is flowing
					cout << "Timestamp: " << this->TimeStamp << endl;
					depthCaptured = true;
					break;
				default:
					break;
				}

			}


			return depthImage;
		}
		else
		{

			depthImage = cv::Mat::zeros(10, 10, CV_8UC1);

		}


		return depthImage;
	}


OpenCVKinect::~OpenCVKinect(void)
{
	this->depthFrame.release();
	this->depthStream.stop();
	openni::OpenNI::shutdown();
	this->kinect.close();
}
