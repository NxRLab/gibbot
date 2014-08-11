
import java.awt.*;
import java.io.*;
import java.nio.*;
import javax.swing.*;
import jssc.*;

/**Wrapper class for jssc's SerialPort; gets all data from wireless
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
	
	/**SerialPort object that is wrapped by this class*/
	private static SerialPort port = new SerialPort("COM5");
	
	/**Used to read byte stream*/
	private static ByteBuffer bb;
	 
	/**Used to convert angular velocity to linear velocity for the speedometer. This is 
	 *an approximation since the distance from the center of rotation will change
	 *for a double pendulum, but it will do for display purposes.*/
	private final static double RADIUS = .15; //distance in meters from gyroscope to center of rotation

	/**Holds initial floats from byte conversion*/
	private static float[] floatHolder = new float[7];
	/**Holds float values converted to ints and scaled while all processing occurs (see class comments).*/
	private static int[] tempData = new int[7];
	/**Holds final values to send for drawing; returned by {@link #update}.*/
	private static int[] data = new int[7];

	/**True if {@link #port} is trying to send data rather than recieve it (only used for sending
	 *goal coordinates from user (banana image coordinates). Value set by {@link #sendGoalCoors} and checked
	 *by {@link #update}.*/
	private static boolean sending = false;
	
	/**Override for SerialPort's openPort() method. Configures port and initiallizes values
	 *in data to non-null.*/
	public static void openPort(){
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
	
	/**Currently an empty class, but eventually would be called by {@link Gibbot#updateRealCoors} to animate the robot image.
	 *Type for coordinates could be changed to ints.
	 *@return double array of size 6 (x and y coors for each joint)*/
	public static double[] getRealCoors(){return new double[] {};} //for updating robot animation; called from Gibbot class
	
	/**Returns {@link #data}. Called by all graph animations.
	 *@return data The array with values for velocity, motor temp, battery, current, and torque.*/
	public static int[] getData(){
		return data;
	}	 
	
	/**Updates {@link #data}. Called by {@link GUILayeredPane} in response to {@link GUITimer fires}.
	 * As per communication protocol, sends a "q" to the other XBee and reads a stream of bytes that
	 *is returned. Turns the bytes into floats, scales as necessary, converts to ints and writes new 
	 *values over old ones in {@link #data}. If port is not open or if an error occurs while sending/
	 *receiving, fills data with dummy values. Note that this does not return the array; {@link #getData}
	 *must be called for that.*/
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
				port.writeString("q");
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
	
	/**Used to send user-determined goal coordinates to the robot. Called by {@link BananaPanel1#mouseReleased}.
	 *Right now has {@link #port} simply send coordinates as a string, but this is not final or necessary.
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

