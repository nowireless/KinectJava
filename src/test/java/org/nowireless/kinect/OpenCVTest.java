package org.nowireless.kinect;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.nowireless.kinect.internal.Native;
import org.opencv.core.Core;
import org.opencv.core.Mat;

public class OpenCVTest {

	
	public static Logger log = LogManager.getLogger("OpenCV");
	public static void main(String[] args) {
		System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
		Kinect.loadLibrary();
		
		Native.test();
		
		Mat dst = new Mat();
		Native.openCVTestImage(dst.nativeObj);
		log.info("Info: {}", dst.toString());
	}

}
