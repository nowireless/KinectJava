package org.nowireless.kinect.internal;

public class Native {
	public static native long freenectInit();
	public static native void freenectShutDown(long context);
	public static native void freenectSetLogLevel(long context, int level);
	public static native void freenectSelectMotorAndCamera(long context);
	public static native int freenectProcessEvents(long context);
	//NO static native void freenectProceesEventsTimeout();
	public static native int freenectNumDevices(long context);
	//Latter static native int freenectSupportedSubDevices();
	//Latter static native void freenectEnabledSubDevices();
	public static native long freenectOpenDevice(long context, int index);
	public static native int freenectCloseDevice();
	public static native int freenectStartDepth(long handle);
	public static native int freenectStartVideo(long handle);
	public static native int freenectStopDepth(long handle);
	public static native int freenectStopVideo(long handle);
	public static native int freenectSetTiltDegs(long handle, double angle);
	//static native void freenectGetTiltDegs();
	public static native void freencetTiltStatusCode();
	public static native void freenectSetLed();
	public static native void freenectGetVideoModeCount();
	public static native void freenectGetDepthModeCount();
	
	public static native void test();
}