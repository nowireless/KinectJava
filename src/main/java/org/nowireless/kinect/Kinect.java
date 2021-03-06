package org.nowireless.kinect;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.nowireless.kinect.internal.Native;
import org.opencv.core.Mat;
import org.opencv.highgui.Highgui;

public class Kinect {
	private static final int DUMMY = 2147483647;
	public static final String NATIVE_LIBRARY = "KinectBridge";
	public static final long CONTEXT_THREAD_SLEEP = 5;
	
	public enum DeviceFlags {
		FREENECT_DEVICE_MOTOR(0x01),
		FREENECT_DEVICE_CAMERA(0x02),
		FREENECT_DEVICE_AUDIO(0x04);
		
		public final int val;
		private DeviceFlags(int val) {
			this.val = val;
		}
	}
	
	public enum Resolution {
		FREENECT_RESOLUTION_LOW(0),
		FREENECT_RESOLUTION_MEDIUM(1),
		FREENECT_RESOLUTION_HIGH(2),
		FREENECT_RESOLUTION_DUMMY(DUMMY);
		
		public final int val;
		private Resolution(int val) {
			this.val = val;
		}
	}
	
	public enum VideoFormat {
		FREENECT_VIDEO_RGB(0),
		FREENECT_VIDEO_BAYER(1),
		FREENECT_VIDEO_IR_8BIT(2),
		FREENECT_VIDEO_IR_10BIT(3),
		FREENECT_VIDEO_IR_10BIT_PACKED(4),
		FREENECT_VIDEO_YUV_RGB(5),
		FREENECT_VIDEO_YUV_RAW(6),
		FREENECT_VIDEO_DUMMY(DUMMY);
		
		public final int val;
		private VideoFormat(int val) {
			this.val = val;
		}
	}
	
	public enum DepthFormat {
		FREENECT_DEPTH_11BIT(0),
		FREENECT_DEPTH_10BIT(1),
		FREENECT_DEPTH_11BIT_PACKED(2),
		FREENECT_DEPTH_10BIT_PACKED(3),
		FREENECT_DEPTH_REGISTERED(4),
		FREENECT_DEPTH_MM(6),
		FREENECT_DEPTH_DUMMY(DUMMY);
		
		public final int val;
		private DepthFormat(int val) {
			this.val = val;
		}
	}
	
	public enum Flag {
		FREENECT_AUTO_EXPOSURE(1 << 14),
		FREENECT_AUTO_WHITE_BALANCE(1 << 1),
		FREENECT_RAW_COLOR(1 << 4),
		FREENECT_MIRROR_DEPTH(1 << 16),
		FREENECT_MIRROR_VIDEO(1 << 17);
		
		public final int val;
		private Flag(int val) {
			this.val = val;
		}
	}
	
	public enum FlagValue {
		FREENECT_OFF(0),
		FREENECT_ON(1);
		
		public final int val;
		private FlagValue(int val) {
			this.val = val;
		}
	}
	
	public class FrameMode {
		
	}
	
	public enum LedOptions {
		LED_OFF(0),
		LED_GREEN(1),
		LED_RED(2),
		LED_YELLOW(3),
		LED_BLINK_GREEN(4),
		LED_BLINK_RED_YELLOW(6);
		
		public final int val;
		private LedOptions(int val) {
			this.val = val;
		}
	}
	
	public enum TiltStatus {
		TILT_STATUS_STOPPED(0x00),
		TILT_STATUS_LIMIT(0x01),
		TILT_STATUS_MOVING(0x04);
		
		public final int val;
		private TiltStatus(int val) {
			this.val = val;
		}
	}
	
	public enum LogLevel {
		FREENECT_LOG_FATAL(0),
		FREENECT_LOG_ERROR(1),
		FREENECT_LOG_WARNING(2),
		FREENECT_LOG_NOTICE(3),
		FREENECT_LOG_INFO(4),
		FREENECT_LOG_DEBUG(5),
		FREENECT_LOG_SPEW(6), 
		FREENECT_LOG_FLOOD(7);
		
		public final int val;
		private LogLevel(int val) {
			this.val = val;
		}
	}
	
	public static class Context {
		public final long handle;
		public Context(long handle) {
			this.handle = handle;
		}
		
		public void setLogLevel(LogLevel level) {
			Native.freenectSetLogLevel(handle, level.val);
		}
		
		public void selectMotorAndCamreaSubDevices() {
			Native.freenectSelectMotorAndCamera(handle);
		}
		
		public boolean processEvents() {
			int status = Native.freenectProcessEvents(handle);
			return status == 0;
		}
		
		public int connectedDevices() {
			return Native.freenectNumDevices(handle);
		}
		
		public Device openDevice(int index) {
			long device = Native.freenectOpenDevice(handle, index);
			if(device != 0) return new Device(this,device);
			return null;
		}
		
		public void shutdown() {
			Native.freenectShutDown(handle);
		}
		
		//public boolean closedevice() {
		//	return Native.freenectCloseDevice() == 0;
		//}
	}
	
	public static class Device {
		public final Context context;
		public final long handle;
		public Device(Context context, long handle) {
			this.handle = handle;
			this.context = context;
		}
		
		public boolean startDepth() {
			return Native.freenectStartDepth(handle) == 0;
		}
		
		public boolean startVideo() {
			return Native.freenectStartVideo(handle) == 0;
		}
		
		public boolean stopDepth() {
			return Native.freenectStopDepth(handle) == 0;
		}
		
		public boolean stoptVideo() {
			return Native.freenectStopVideo(handle) == 0;
		}
		
		public boolean setTiltAngle(double angle) {
			return Native.freenectSetTiltDegs(handle, angle) == 0;
		}
	}
	
	public static class ContextThread extends Thread {
		private final Logger log = LogManager.getLogger();
		private volatile boolean run = false;
		public final Context cxt;
		public final Device dev;
		private final long sleep;
		
		public ContextThread(Device dev, long sleep) {
			this.dev = dev;
			this.cxt = dev.context; 
			this.sleep = sleep;
		}
		
		public ContextThread(Device dev) {
			this(dev, CONTEXT_THREAD_SLEEP);
		}
		
		@Override
		public void run() {
			run = true;
			log.trace("Entering Context Thread loop");
			
			log.trace("Starting Video");
			if(!dev.startVideo()) {
				log.fatal("Could not start video");
			}
			
			Mat buf = new Mat(Native.opencvGetVideoBuffer());
			log.trace("VideoBuff {}",  buf);
			
			while(run) {
				log.trace("Procssing Events");
				if(cxt.processEvents()) {
					if(Native.opencvIsImageUnread() == 1) {
						log.trace("New Frame!");
						log.trace("VideoBuff {}",  buf);
						
						Highgui.imwrite("Kinect.jpg", buf);
						
						Native.opencvImageHasBeenRead();
					}
					log.trace("Processed Events");
				} else {
					log.warn("Could not Process Events");
				}
				
				try {
					Thread.sleep(sleep);
				} catch (InterruptedException e) {
					log.trace("Breaking Context Thread loop");
					break;
				}
			}
			
			log.trace("Exiting Context thread");
		}
		
	}
	
	public static void loadLibrary() {
		System.loadLibrary(NATIVE_LIBRARY);
	}
	
	public static Context createContext() {
		long context = Native.freenectInit();
		if(context != 0) return new Context(context);
		return null;
	}
	
	//public static ? supportedSubDevices() {}
}
