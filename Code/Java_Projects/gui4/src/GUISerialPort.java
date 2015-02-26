
import java.awt.*;
import java.io.*;
import java.nio.*;
import java.util.HashMap;

import javax.swing.*;

import jssc.*;

/**Wrapper class for jssc's SerialPort; gets all data from wireless
 *serial connection. GUILayeredPane calls {@link #update} method at a set interval,
 *which updates the {@link #data} array, then GUI components are free to call
 *{@link #getData} when they need to without causing confliction serial commands.
 *Conversion to ints and scaling is done in update().
 *
 *{@link #tempData} is used to store information as it is being converted for use
 *in GUI so that a call to getData() won't return a partially updated array.
 *
 *{@link #sendGoalCoors} currently unimplemented in GUI, but available for when camera is set up.
 */

public class GUISerialPort {
	
	/**SerialPort name to open */ 
    public static String portName = "COM5";

	/**SerialPort object that is wrapped by this class*/
	private static SerialPort port;
	
	/**Used to read byte stream*/
	private static ByteBuffer bb;
	 
	/**Used to convert angular velocity to linear velocity for the speedometer. This is 
	 *an approximation since the distance from the center of rotation will change
	 *for a double pendulum, but it will do for display purposes.*/
	private final static double RADIUS = .15; //distance in meters from gyroscope to center of rotation

	/**Holds final values to send for drawing; returned by {@link #update}.*/
	private static HashMap<String, Integer> data = new HashMap<String, Integer>();
	/**Data names*/
	private static String[] dataNames = new String[] {"motorCurrent", "motorTorque",
		"motorTemperature", "batteryVoltage", "Gyroscope_Z_Primary",
		"Gyroscope_Z_Secondary", "gibbotAngle", "gibbotXPos", "gibbotYPos"}; //xPos and yPos are middle position
	static int NUM_DATA = dataNames.length; //number of data points (e.g. torque, blah blah)
	
	
	/**Holds initial floats from byte conversion*/
	//private static float[] floatHolder = new float[7];
	private static float[] floatHolder = new float[NUM_DATA];
	/**Holds float values converted to ints and scaled while all processing occurs (see class comments).*/
	//private static int[] tempData = new int[7];
	private static int[] tempData = new int[NUM_DATA];
	/**Holds final values to send for drawing; returned by {@link #update}.*/
	//private static int[] data = new int[7];

	
	
	
	/**True if {@link #port} is trying to send data rather than recieve it (only used for sending
	 *goal coordinates from user (banana image coordinates). Value set by {@link #sendGoalCoors} and checked
	 *by {@link #update}.*/
	private static boolean sending = false;
	
	/**Override for SerialPort's openPort() method. Configures port and initiallizes values
	 *in data to non-null.*/
	public static void openPort(){
		try{
            port = new SerialPort(portName);
    		port.openPort();
    		port.setParams(115200, 8, 1, 0);
            port.setFlowControlMode(SerialPort.MASK_CTS);
		}
    	
    	catch(SerialPortException e){
    		System.out.println("Failed to open " + port.getPortName() + " due to: "); 
    		System.out.println(e.getExceptionType());
    	}
		for(int i = 0;i < NUM_DATA; i++){
			data.put(dataNames[i], 20); //20 is hardcoded for now, will soon get from PIC
		}
	}
	
	/**Currently an empty class, but eventually would be called by {@link Gibbot#updateRealCoors} to animate the robot image.
	 *Type for coordinates could be changed to ints.
	 *@return double array of size 6 (x and y coors for each joint)*/
	public static double[] getRealCoors(){return new double[] {};} //for updating robot animation; called from Gibbot class
	
	/**Returns {@link #data}. Called by all graph animations.
	 *@return data The array with values for velocity, motor temp, battery, current, and torque.*/
	/*public static int[] getData(){
		return data;
	}*/
	public static HashMap<String, Integer> getData(){
		return data;
	}	 
	
	/**Updates {@link #data}. Called by {@link GUILayeredPane} in response to {@link GUITimer fires}.
	 * As per communication protocol, sends an "s" to the other XBee and reads the stream of bytes that
	 *is returned. Turns the bytes into floats, scales as necessary, converts to ints and writes new 
	 *values over old ones in {@link #data}. If port is not open or if an error occurs while sending/
	 *receiving, fills data with dummy values. The problem that seemed to freeze the program was that 
	 *the last byte would be dropped, so this method checks for that and returns without updating if 
	 *that is the case (update speed is fast enough that this does not have a noticeable effect on the GUI. 
	 *Note that this method does not return the data array; {@link #getData} must be called to obtain that.*/
	public static void update(){  //called by GUILayeredPane in response to timer-generated events
		
		if(!port.isOpened()){
			/*
			data[0] = 30;
			data[1] = 13;
			data[2] = 60;
			data[3] = 48;
			data[4] = 10;
			data[5] = 80;
			*/
			data.put("motorCurrent", 30);
			data.put("motorTorque", 13);
			data.put("motorTemperature", 60);
			data.put("batteryVoltage", 48);
			data.put("motorTorque", 13);
			data.put("Gyroscope_Z_Primary", 10);
			data.put("Gyroscope_Z_Secondary", 18);
		}
		
		else if(sending)
			return;
			
		else{
			
			try {
				port.writeString("s");
				
				//System.out.println("sent");
				int bytes = port.getInputBufferBytesCount();
				
				if(bytes == 24){ //makes a byte hasn't been dropped
					for(int i = 0; i < 6; i++){
					 
	     				bb = ByteBuffer.wrap(port.readBytes(4));
     					bb.order(ByteOrder.LITTLE_ENDIAN);
     					floatHolder[i] = bb.getFloat();
     					//System.out.print(floatHolder[i] + " "); //can use to track dropped data
					}
				}
				else{ //if a byte has been dropped, reads those in the port to clear it but doesn't do anything with them.
						port.readBytes();
						return;
					}					
     			
     			//System.out.println(); //Uncomment this if using print command in for loop above
     			
				//scaling for drawing on charts
				tempData[0] = (int)(floatHolder[0]*7.5);
				tempData[1] = (int)(floatHolder[1]*.065);
				tempData[2] = ((int)(27*floatHolder[2]/25 - 10.8));				
				tempData[3] = (int)(floatHolder[3]*4);
				tempData[4] = Math.abs((int)(floatHolder[4]*4*RADIUS));
				tempData[5] = Math.abs((int)(floatHolder[5]*4*RADIUS));
				//tempData[6] = (int)floatHolder[6]; //for battery signal?
				
				
				/*
				for(int i = 0; i < 7; i++)
					data[i] = tempData[i];
				*/
				for(int i = 0; i < NUM_DATA; i++)
					data.put(dataNames[i], tempData[i]);
					
			}

     		catch(SerialPortException e){
     			/*
     			for(int i = 0; i < 7; i++)
					data[i] = 100;
				*/
     			for(int i = 0; i < NUM_DATA; i++)
     				data.put(dataNames[i], 100);
     		}			
		}
	}
	
	/**Used to send user-determined goal coordinates to the robot. Called by {@link BananaPanel1#mouseReleased}.
	 *Currently has {@link #port} simply send coordinates as a string, but this is not final or necessary to any
	 *other part of the program right now.
	 *@param x X coordinate to be reached by the robot
	 *@param y Y coordinate to be reached by the robot
	 **/
	public static void sendGoalCoors(int x, int y){ 
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

