//
//  KinectBridge.h
//  KinectBridge
//
//  Created by Ryan Sjostrand on 12/14/14.
//  Copyright (c) 2014 Ryan Sjostrand. All rights reserved.
//

#ifndef KinectBridge_KinectBridge_h
#define KinectBridge_KinectBridge_h

#include <iostream>
#include <stdint.h>
#include <libfreenect/libfreenect.h>
#include <opencv2/core/core.hpp>
#include "org_nowireless_kinect_internal_Native.h"

void VideoCallBack(freenect_device *dev, void *rgb, uint32_t timestamp);

#endif
