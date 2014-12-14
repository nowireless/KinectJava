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