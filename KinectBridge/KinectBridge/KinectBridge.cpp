//
//  KinectBridge.cpp
//  KinectBridge
//
//  Created by Ryan Sjostrand on 12/14/14.
//  Copyright (c) 2014 Ryan Sjostrand. All rights reserved.
//

#include "KinectBridge.h"

uint8_t *rgbFreenect;
//uint8_t *rgbCallBack;
uint8_t *depthFreenct;
//uint8_t *depthCallBack;
cv::Mat *videoBuff;
int isImageRead;

void VideoCallBack(freenect_device *dev, void *rgb, uint32_t timestamp) {
    cv::Mat temp(480, 640, CV_8UC3, cv::Scalar(0,0,0));
    std::cout << "Video Callback is called!!!" << std::endl;
    uint8_t *rbgCast = static_cast<uint8_t*>(rgb);
    temp.data = rbgCast;
    cv::Mat &buf = *(cv::Mat*)videoBuff;
    temp.copyTo((buf));
    isImageRead = 1;
    std::cout << "VideoBuff " << videoBuff->empty() << std::endl;
}

JNIEXPORT jlong JNICALL Java_org_nowireless_kinect_internal_Native_opencvGetVideoBuffer(JNIEnv *, jclass) {
    return (jlong) videoBuff;
}


JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_opencvImageHasBeenRead(JNIEnv *, jclass) {
    isImageRead = 0;
}

JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_opencvIsImageUnread(JNIEnv *, jclass) {
    return isImageRead;
}

JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_test(JNIEnv *, jclass) {
    std::cout << "Hello From C++!" << std::endl;
}

JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_openCVTestImage(JNIEnv *, jclass, jlong dst) {
    if(dst == 0) {
        std::cout << "DST is NULL!" << std::endl;
        return;
    }
    
    cv::Mat &dstMat = *(cv::Mat*)dst;
    cv::Mat testImage(640,480, CV_8UC3, cv::Scalar(255,255,255));
    testImage.copyTo(dstMat);
}

JNIEXPORT jlong JNICALL Java_org_nowireless_kinect_internal_Native_freenectInit(JNIEnv *, jclass) {
    freenect_context *ret = NULL;
    int status = freenect_init(&ret, NULL);
    if(status < 0) {
        std::cout << "freenect_init failed with " << status << std::endl;
        return 0;
    }
    return (jlong)ret;
}

JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freenectSetLogLevel(JNIEnv *, jclass, jlong context, jint level) {
    std::cout << "Ignoreing Loging Level" << std::endl;
    freenect_set_log_level((freenect_context*) context, FREENECT_LOG_INFO);
}

JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectProcessEvents(JNIEnv *, jclass, jlong context) {
    return freenect_process_events((freenect_context*) context);
}

JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectNumDevices(JNIEnv *, jclass clazz, jlong context) {
    return freenect_num_devices((freenect_context*)context);
}

JNIEXPORT jlong JNICALL Java_org_nowireless_kinect_internal_Native_freenectOpenDevice(JNIEnv *, jclass, jlong context, jint index) {
    freenect_device *ret = NULL;
    int status = freenect_open_device((freenect_context*)context, &ret, index);
    if(status < 0) {
        std::cout << "freenect_open_device failed with " << status << std::endl;
        return 0;
    }
    
    std::cout << "Opened Device "<< ret << std::endl;
    
    return (jlong)ret;
}

JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectSetTiltDegs(JNIEnv *, jclass, jlong device, jdouble angle) {
    std::cout << "Device " << device << " Angle " << angle << std::endl;
    freenect_set_tilt_degs((freenect_device*) device, angle);
    return -1;
}

JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freenectSelectMotorAndCamera(JNIEnv *, jclass, jlong context) {
    freenect_select_subdevices((freenect_context*)context, (freenect_device_flags) (FREENECT_DEVICE_CAMERA | FREENECT_DEVICE_MOTOR));
}

JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freenectShutDown(JNIEnv *, jclass, jlong context) {
    freenect_shutdown((freenect_context*) context);
}

JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectCloseDevice(JNIEnv *, jclass) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectCloseDevice" << std::endl;
    return -1;
}

JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectStartDepth(JNIEnv *, jclass, jlong) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectStartDepth" << std::endl;
    return -1;
}

JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectStartVideo(JNIEnv *, jclass, jlong device) {
    rgbFreenect = (uint8_t*)malloc(640*480*3);
    videoBuff = new cv::Mat();
    isImageRead = 0;
    freenect_set_video_buffer((freenect_device*)device, rgbFreenect);
    freenect_set_video_mode((freenect_device*)device, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB));
    freenect_set_video_callback((freenect_device*)device, VideoCallBack);
    return freenect_start_video((freenect_device*)device);
}

JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectStopDepth(JNIEnv *, jclass, jlong) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectStopDepth" << std::endl;
    return -1;
}

JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectStopVideo(JNIEnv *, jclass, jlong) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectStopVideo" << std::endl;
    return -1;
}

JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freencetTiltStatusCode(JNIEnv *, jclass) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freencetTiltStatusCode" << std::endl;
}

JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freenectSetLed(JNIEnv *, jclass) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectSetLed" << std::endl;
}

JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freenectGetVideoModeCount(JNIEnv *, jclass) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectGetVideoModeCount" << std::endl;
}

JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freenectGetDepthModeCount(JNIEnv *, jclass) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectGetDepthModeCount" << std::endl;
}
