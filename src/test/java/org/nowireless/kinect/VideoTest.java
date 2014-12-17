package org.nowireless.kinect;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.nowireless.kinect.Kinect.Context;
import org.nowireless.kinect.Kinect.ContextThread;
import org.nowireless.kinect.Kinect.Device;
import org.nowireless.kinect.Kinect.LogLevel;
import org.opencv.core.Core;

public class VideoTest {
	
	public static Logger log = LogManager.getLogger("VideoTest");
	public static void main(String[] args) {
		log.info("Loading Native Library");
		System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
		Kinect.loadLibrary();
		
		log.info("Creating context");
		Context cxt = Kinect.createContext();
		
		log.info("Setting logging Level");
		cxt.setLogLevel(LogLevel.FREENECT_LOG_DEBUG);
		
		log.info("Selecting Motor & Camera Subdevices");
		cxt.selectMotorAndCamreaSubDevices();
		
		log.info("Finding the number of connected devices");
		int num = cxt.connectedDevices();
		
		log.info("Found {} Kinects Connected", num);
		if(num == 0) {
			log.fatal("No Kinects found");
			cxt.shutdown();
			System.exit(1);
			
		}
		Device dev = cxt.openDevice(0);
		
		log.info("Device Handle {}", cxt.handle);
		
		if(dev == null) {
			log.fatal("Device is NULL!");
			cxt.shutdown();
			System.exit(1);
		}
		
		ContextThread cxtThread = new ContextThread(dev);
		Runtime.getRuntime().addShutdownHook(new TiltTest.ShutDownHook(cxtThread));
		cxtThread.start();
		try {
			cxtThread.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		cxt.shutdown();
	}
}
