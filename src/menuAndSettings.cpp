#include "menuAndSettings.h"
#include "defaultParamsAndUtilis.h"

void display(Params& params)
{
    system("clear");
    cout << "Exiting without changing parameters results in"<<endl;
    cout << "using default kinfu algorithm parameters for kinect 360 sensor"<<endl;
    cout << endl;

    cout << "1. Voxel Size:  " << params.voxelSize << endl;
    cout << "2. TSDF truncation distance:  " << params.tsdf_trunc_dist << endl;
    cout << "3. TSDF minimal camera movement [meters]:  " << params.tsdf_min_camera_movement << endl;
    cout << "4. TSDF max weight:  " << params.tsdf_max_weight << endl;
    cout << "5. ICP angle threshold [radians]:  " << params.icpAngleThresh << endl;
    cout << "6. ICP distance threshold [meters]:  " << params.icpDistThresh << endl;
    cout << "7. Bilateral kernel size [pixels]:  " << params.bilateral_kernel_size << endl;
    cout << "8. Bilateral sigma depth [meter]:  " << params.bilateral_sigma_depth << endl;
    cout << "9. Bilateral sigma spatial [pixels]:   " << params.bilateral_sigma_spatial << endl;
    cout << "10. Depth Factor:  " << params.depthFactor << endl;
    cout << "11. Pyramid levels:  " << params.pyramidLevels << endl;
    cout << "12. Raycast step factor:  " << params.raycast_step_factor << endl;
    cout << "13. Truncate threshold [meters]:  " << params.truncateThreshold << endl;
    cout << "14. Volume dimension:  " << params.volumeDims << endl;
    cout << "15. Camera Parameters:  " << params.intr << endl;
    cout << "16. Light Pose [meters]:  " << params.lightPose << endl;
    cout << "17. Use my default parameters:  " << endl;
    cout << "18. Exit " << endl << endl << endl;

}

void changeParams(Params& params)
{
    display(params);
    float fx = 0, fy = 0, cx = 0, cy = 0;
    Matx33f camMatrix;
    float cubeSize = 1.0f;


    cv::setUseOptimized(true);

    
    int choose;
    cin >> choose;
    switch (choose)
    {
    case 1:
        cout << "Voxel Size:  ";
        cin >> params.voxelSize;
        changeParams(params);
	break;
    case 2:
        cout << "TSDF truncation distance:  ";
        cin >> params.tsdf_trunc_dist;
        changeParams(params);
	break;
    case 3:
        cout << "TSDF minimal camera movement:  ";
        cin >> params.tsdf_min_camera_movement;
        changeParams(params);
	break;
    case 4:
        cout << "TSDF max weight:  ";
        cin >> params.tsdf_max_weight;
        changeParams(params);
	break;
    case 5:
        cout << "ICP angle threshold:  ";
        cin >> params.icpAngleThresh;
        changeParams(params);
	break;
    case 6:
        cout << "ICP distance threshold:  ";
        cin >> params.icpDistThresh;
        changeParams(params);
	break;
    case 7:
        cout << "Bilateral kernel size:  ";
        cin >> params.bilateral_kernel_size;
        changeParams(params);
	break;
    case 8:
        cout << "Bilateral sigma depth:  ";
        cin >> params.bilateral_sigma_depth;
        changeParams(params);
	break;
    case 9:
        cout << "Bilateral sigma spatial:  ";
        cin >> params.bilateral_sigma_spatial;
        changeParams(params);
	break;
    case 10:
        cout << "Depth Factor:  ";
        cin >> params.depthFactor;
        changeParams(params);
	break;
    case 11:
        cout << "Pyramid levels:  ";
        cin >> params.pyramidLevels;
        changeParams(params);
	break;
    case 12:
        cout << "Raycast step factor:  ";
        cin >> params.raycast_step_factor;
        changeParams(params);
	break;
    case 13:
        cout << "Truncate threshold:  ";
        cin >> params.truncateThreshold;
        changeParams(params);
	break;
    case 14:
        cout << "Volume dimension:  " << endl;
	cout << "Insert three values" << endl;
        int dim;
        for (int i = 0; i < 3; i++)
        {
            cin >> dim;
            params.volumeDims[i] = dim;
        }
        changeParams(params);
	break;

    case 15:
        cout << "Camera Parameters:  " << endl;
	cout << "Insert four parameters" << endl;
	cout << "focal length x / focal length y / principal point x / principal point y" << endl;

        cin >> fx >> fy >> cx >> cy;
        camMatrix = { fx, 0, cx, 0, fy, cy, 0, 0, 1 };
        params.intr = camMatrix;
        changeParams(params);
	break;
    case 16:
        cout << "Light Pose:  " << endl;
	cout << "Insert three parameters" << endl;
        cin >> params.lightPose[0] >> params.lightPose[1] >> params.lightPose[2];
        changeParams(params);

    case 17:
        params.voxelSize = 0.01f; //meters
        params.tsdf_trunc_dist = 0.01f; //meters
        params.tsdf_min_camera_movement = 0;
        params.tsdf_max_weight = 16;//max number of frames per voxel
        params.icpAngleThresh = 0.50f;
        params.icpDistThresh = 0.5f; //meters
        params.volumePose = Affine3f().translate(Vec3f(-cubeSize / 2.f, -cubeSize / 2.f, 0.25f)); //meters
        params.bilateral_kernel_size = 3;
        params.bilateral_sigma_depth = 0.04;
        params.bilateral_sigma_spatial = 4.5;
        params.pyramidLevels = 3;
        params.raycast_step_factor = 0.75;
        params.truncateThreshold = 1.0f;
        params.depthFactor = 2000.0f;
        changeParams(params);
	break;
    case 18:
        cout << "Exiting:" << endl << endl;
        break;
    default:
        break;
        
    }
   


}


void readOrWrite(bool & read, bool & write)
{
    
    cout << "Choose what do you want to do:" << endl;
    cout << "1.Write to file  2. Read from file   3. Default scanning mode" << endl;
    int n;
    
    
    cin >> n;
    while (n != 1 && n != 2 && n != 3)
    {
        cin >> n;
    }

    switch (n)
    {
    case 1:
        write = true;
        break;
    case 2:
        read = true;
        break;
    default:
        break;
    }
    system("pause");
}
