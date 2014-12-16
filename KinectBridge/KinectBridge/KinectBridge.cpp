//
//  KinectBridge.cpp
//  KinectBridge
//
//  Created by Ryan Sjostrand on 12/14/14.
//  Copyright (c) 2014 Ryan Sjostrand. All rights reserved.
//

#include "KinectBridge.h"

JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_test(JNIEnv *, jclass) {
    std::cout << "Hello From C++" << std::endl;
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
    freenect_set_log_level((freenect_context*) context, FREENECT_LOG_SPEW);
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

JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectStartVideo(JNIEnv *, jclass, jlong) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectStartVideo" << std::endl;
    return -1;
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
