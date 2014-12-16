package org.nowireless.kinect;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.nowireless.kinect.Kinect.Context;
import org.nowireless.kinect.Kinect.Device;
import org.nowireless.kinect.Kinect.LogLevel;

public class TiltTest {
	
	public static class MainThread extends Thread {
		
		private final Device dev;
		
		public MainThread(Device dev) {
			this.dev = dev;
		}
		
		@Override
		public void run() {
			boolean state = false;
			double angle = 0;
			TiltTest.log.info("Starting Thread");
			while (true) {
				if (state) {
					angle = 27;
				} else {
					angle = -27;
				}
				TiltTest.log.info("Tilting Kinect to {} degs", angle);
				dev.setTiltAngle(angle);
				
				state = !state;
				
				try {
					Thread.sleep(3000);
				} catch (InterruptedException e) {
					TiltTest.log.info("Ending Main Thread");
					break;
				}
			}
		}
	}
	
	public static class ShutDownHook extends Thread {
		final Thread thread;
		
		public ShutDownHook(Thread thread) {
			this.thread = thread;
		}
		
		@Override
		public void run() {
			thread.interrupt();
		}
	}
	
	public static Logger log = LogManager.getLogger("TiltTest");
	
	public static void main(String[] args) {
		log.info("Loading Native Library");
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
		
		Thread main = new MainThread(dev);
		Runtime.getRuntime().addShutdownHook(new ShutDownHook(main));
		main.start();
		
		try {
			main.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		cxt.shutdown();
		
	}
	
}
