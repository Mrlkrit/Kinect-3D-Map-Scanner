#include "defaultParamsAndUtilis.h"




void updateParams(Params& params)
{
    //frame size
    int w = 640;
    int h = 480;

    
    float fx = 0, fy = 0, cx = 0, cy = 0;
    float depthFactor = 3000.f;//max depth in mm
    Size frameSize;

    fx = fy = kinectDeviceDefaultParams::focal;
    cx = kinectDeviceDefaultParams::cx;
    cy = kinectDeviceDefaultParams::cy;

    frameSize = kinectDeviceDefaultParams::frameSize;



    frameSize = Size(w, h);


    Matx33f camMatrix = Matx33f(fx, 0, cx, 0, fy, cy, 0, 0, 1);

    params.frameSize = frameSize;
    params.intr = camMatrix;
    params.depthFactor = depthFactor;

}






