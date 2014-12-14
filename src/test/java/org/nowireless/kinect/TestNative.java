package org.nowireless.kinect;

import org.nowireless.kinect.internal.Native;

public class TestNative {
	public static void main(String[] args) {
		System.out.println(System.getProperty("java.library.path"));
		Kinect.loadLibrary();
		Native.test();
	
	}
}
