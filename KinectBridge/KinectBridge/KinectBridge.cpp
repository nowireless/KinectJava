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

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectInit
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_nowireless_kinect_internal_Native_freenectInit(JNIEnv *, jclass) {
    freenect_context *ret = NULL;
    int status = freenect_init(&ret, NULL);
    if(status < 0) {
        std::cout << "freenect_init failed with " << status << std::endl;
        return 0;
    }
    return (jlong)ret;
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectSetLogLevel
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freenectSetLogLevel(JNIEnv *, jclass, jlong context, jint level) {
    freenect_set_log_level((freenect_context*) context, (freenect_loglevel)level);
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectProcessEvents
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectProcessEvents(JNIEnv *, jclass, jlong context) {
    return freenect_process_events((freenect_context*) context);
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectNumDevices
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectNumDevices(JNIEnv *, jclass clazz, jlong context) {
    return freenect_num_devices((freenect_context*)context);
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectOpenDevice
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_org_nowireless_kinect_internal_Native_freenectOpenDevice(JNIEnv *, jclass, jlong context, jint index) {
    freenect_device *ret = NULL;
    int status = freenect_open_device((freenect_context*)context, &ret, index);
    if(status < 0) {
        std::cout << "freenect_open_device failed with " << status << std::endl;
        return 0;
    }
    return (jlong)ret;
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectCloseDevice
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectCloseDevice(JNIEnv *, jclass) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectCloseDevice" << std::endl;
    return -1;
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectStartDepth
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectStartDepth(JNIEnv *, jclass, jlong) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectStartDepth" << std::endl;
    return -1;
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectStartVideo
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectStartVideo(JNIEnv *, jclass, jlong) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectStartVideo" << std::endl;
    return -1;
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectStopDepth
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectStopDepth(JNIEnv *, jclass, jlong) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectStopDepth" << std::endl;
    return -1;
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectStopVideo
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectStopVideo(JNIEnv *, jclass, jlong) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectStopVideo" << std::endl;
    return -1;
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectSetTiltDegs
 * Signature: (JD)I
 */
JNIEXPORT jint JNICALL Java_org_nowireless_kinect_internal_Native_freenectSetTiltDegs(JNIEnv *, jclass, jlong, jdouble) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectSetTiltDegs" << std::endl;
    return -1;
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freencetTiltStatusCode
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freencetTiltStatusCode(JNIEnv *, jclass) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freencetTiltStatusCode" << std::endl;
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectSetLed
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freenectSetLed(JNIEnv *, jclass) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectSetLed" << std::endl;
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectGetVideoModeCount
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freenectGetVideoModeCount(JNIEnv *, jclass) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectGetVideoModeCount" << std::endl;
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectGetDepthModeCount
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freenectGetDepthModeCount(JNIEnv *, jclass) {
    std::cout << "Not Implemented yet: Java_org_nowireless_kinect_internal_Native_freenectGetDepthModeCount" << std::endl;
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectSelectMotorAndCamera
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freenectSelectMotorAndCamera(JNIEnv *, jclass, jlong context) {
    freenect_select_subdevices((freenect_context*)context, (freenect_device_flags) (FREENECT_DEVICE_CAMERA | FREENECT_DEVICE_MOTOR));
}

/*
 * Class:     org_nowireless_kinect_internal_Native
 * Method:    freenectShutDown
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_nowireless_kinect_internal_Native_freenectShutDown(JNIEnv *, jclass, jlong context) {
    freenect_shutdown((freenect_context*) context);
}
