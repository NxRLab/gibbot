/**
 * @(#)GUISerialPort.java
 *
 *
 * @author 
 * @version 1.00 2014/7/11
 */

import java.awt.*;
import java.io.*;
import java.nio.*;
import javax.swing.*;
import jssc.*;

/*Wrapper class for jssc SerialPort; gets all data from wireless
 *serial connection. GUILayeredPane calls update() method at a set interval,
 *which updates the data[] array, then GUI components are free to call
 *getData() when they need to without causing confliction serial commands.
 *Conversion to ints/ scaling is done in update().
 *
 *tempData[] is used to store information as it is being converted for use
 *in GUI so that a call to getData() won't return a partially updated array.
 *
 *sendGoalCoors() currently unimplemented in GUI, but available for when camera is set up.
 */

public class GUISerialPort {
	
	private static SerialPort port = new SerialPort("COM5");
	
	private static ByteBuffer bb;
	 
	private final static double RADIUS = .15; //distance in meters from gyroscope to center of rotation

	private static float[] floatHolder = new float[7];
	private static int[] tempData = new int[7];
	private static int[] data = new int[7];

	private static boolean sending = false;
	
	public static void open(){
		try{
    		port.openPort();
    		port.setParams(115200, 8, 1, 0);
            port.setFlowControlMode(SerialPort.MASK_CTS);
		}
    	
    	catch(SerialPortException e){
    		System.out.println("Failed to open " + port.getPortName() + " due to: "); 
    		System.out.println(e.getExceptionType());
    	}
    	
    	for(int i = 0; i < 7; i++){
			data[i] = 20;
    	}
	}
	
	public static double[] getCoors(){return new double[] {};} //for updating robot animation; called from Gibbot class
	
	public static int[] getData(){
		return data;
	}	 
	
	public static void update(){  //called by GUILayeredPane in response to timer-generated events
		
		if(!port.isOpened()){
			
			for(int i = 0; i < 7; i++)
				data[i] = 8;
			
			data[5] = 80;
		}
		
		else if(sending)
			return;
			
		else{
			
			try {
				for(int i = 0; i < 7; i++){
     				bb = ByteBuffer.wrap(port.readBytes(4));
     				bb.order(ByteOrder.LITTLE_ENDIAN);
     				floatHolder[i] = bb.getFloat();		
     			}
				tempData[0] = (int)(floatHolder[0]*7.5);
				tempData[1] = (int)floatHolder[1];
				tempData[2] = (int)floatHolder[2];				
				tempData[3] = (int)(floatHolder[3]*4);
				tempData[4] = Math.abs((int)(floatHolder[4]*4*RADIUS));
				tempData[5] = Math.abs((int)(floatHolder[5]*4*RADIUS));
				tempData[6] = (int)floatHolder[6]; //for battery signal?
				
				for(int i = 0; i < 7; i++)
					data[i] = tempData[i];
					
			}

     		catch(SerialPortException e){
     			for(int i = 0; i < 7; i++)
					data[i] = 100;
     		}			
		}
	}
	
	public static void sendGoalCoors(int x, int y){ //called by BananaPanel1 class when user places banana image on the screen
		sending = true;	
		try{
			port.writeString(String.format("%s %s", x, y));
			sending = false;
		}
		catch(SerialPortException e){
			System.out.println("Could not send coordinates");
			sending = false;
		}
	}
}

