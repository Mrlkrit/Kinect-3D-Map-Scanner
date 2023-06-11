#include "wrapper.h"



void algorithmWrapper()
{
    OpenCVKinect mydatacap;
    Mat frame;
    int i = 0;
    bool pause = false;
    Mat rendered;
    Mat points;
    Mat normals;
    Mat cvt8;
    Mat outCopy;
    Mat datastream;



    setUseOptimized(true);
    bool read = false;
    bool write = false;
    readOrWrite(read, write);



    if (write==1)
    {
        cout << "acquire depth stream" << endl;
        mydatacap.setMode(0x02);

        if (!mydatacap.init())
        {
            std::cout << "error initializing" << endl;
            return;
        }
        frame = Mat::zeros(640,480, CV_8UC1);

        for (;;)
        {
            ostringstream name;
            frame = mydatacap.getData();
            name  << i <<".png";
            imwrite(name.str(), frame);
            i++;
            imshow("depth", frame);

            if (waitKey(1) == 27)//ESC
            {
                break;
            }
        }
        

    }
    else if (read==1)
    {
        Ptr<Params> params;
        Ptr<KinFu> kf;
        params = Params::coarseParams();
        params = Params::hashTSDFParams(true);

        updateParams(*params);
        display(*params);
        changeParams(*params);
        kf = KinFu::create(params);
        
        frame = Mat::zeros(640,480, CV_8UC1);
        display(*params);

        for (;;)
        {
            if (pause == 0)
            {
                ostringstream name;
                name << i << ".png";
                cout << "processing: " << i << endl;
                frame = imread(name.str(), CV_16UC1);
                
                if (frame.empty())
                    pause = true;
            }

            if (pause)
            {
                if (i == 0)
                {
                    cout << "No image";
                    return;
                }
                cout << "Press ESC to exit Else - resume" << endl;
                int a = waitKey(0);
                switch (a)
                {
                case 27:

                    return;
                default:
                    pause = false;
                    break;

                }



            }
            i++;
            float depthFactor = params->depthFactor;
            cv::convertScaleAbs(frame, cvt8, 0.25 * 256. / depthFactor);

            cv::imshow("depth", cvt8);
        
           
            if (!kf->update(frame))
            {
                cout << "Not eligible frame" << endl;
            }
            else if (!pause)
            {
                kf->render(rendered);//update map
                
               
            }

            cv::imshow("render", rendered);//show rendered map
            int c = waitKey(2);
            switch (c)
            {
            case 27:
                return;
            case 112:
                pause = true;
                break;
            default:
                kf->reset(); //uncomment
                break;
            }
           
        }


    }
    else
    {
        Ptr<Params> params;
        Ptr<KinFu> kf;

        params = Params::coarseParams();
        params = Params::hashTSDFParams(true);
        updateParams(*params);
        display(*params);
        changeParams(*params);
        kf = KinFu::create(params);

        cout << "Acquire depth stream" << std::endl;
        mydatacap.setMode(0x02);

        if (!mydatacap.init())
        {
            cout << "Error initializing" << std::endl;
            return;
        }
        frame = Mat::zeros(params->frameSize, CV_8UC1);
        display(*params);

        for (;;)
        {

            if (pause)
            {
                
                cout << "Press ESC to exit   Else - resume" << endl;
                int a = waitKey(0);
                switch (a)
                {
                case 27:
                    
                    return;
                default:
                    pause = false;
                    break;

                }
                

                
            }
                frame = mydatacap.getData();

                float depthFactor = params->depthFactor;
                convertScaleAbs(frame, cvt8, 0.25 * 256. / depthFactor);

                imshow("depth", cvt8);
            
            if (!kf->update(frame))
            {
                cout << "Not eligible frame" << endl;
            }
            else
            {
               
                kf->render(rendered);//update map
            }

            imshow("render", rendered);//show rendered map


           

            int c = waitKey(2);
            switch (c)
            {
            case 27:
                return;
            case 112:
                pause = true;
            default:
                kf->reset(); // uncomment 
                break;
            }
        }


    }

}
