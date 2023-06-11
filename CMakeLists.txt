cmake_minimum_required(VERSION 3.0.0)


project(KinFu_Scanner)



include_directories(include)

include_directories("/usr/local/include/opencv4/") #opencv libraries
include_directories("/home/konrad/OpenNI2-master/Include") #openni libraries



add_executable(KinFu_Scanner "src/main.cpp" "src/defaultParamsAndUtilis.cpp" "src/kinectData.cpp" "src/wrapper.cpp" "src/menuAndSettings.cpp" )




target_link_libraries(KinFu_Scanner "/home/konrad/OpenNI2-master/Bin/x64-Release/libOpenNI2.so") #openni library
target_link_libraries(KinFu_Scanner "/usr/local/lib/libopencv_rgbd.so.4.5") #opencv rgbd library
target_link_libraries(KinFu_Scanner "/usr/local/lib/libopencv_highgui.so.4.5") #opencv highgui
target_link_libraries(KinFu_Scanner "/usr/local/lib/libopencv_calib3d.so.4.5") #opencv calib3d
target_link_libraries(KinFu_Scanner "/usr/local/lib/libopencv_core.so.4.5") #opencv core
target_link_libraries(KinFu_Scanner "/usr/local/lib/libopencv_imgproc.so.4.5") #opencv imgproc
target_link_libraries(KinFu_Scanner "/usr/local/lib/libopencv_imgcodecs.so.4.5") #opencv imgcodecs
