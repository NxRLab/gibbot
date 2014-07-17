/**
 * @(#)GUISerialPort.java
 *
 *
 * @author 
 * @version 1.00 2014/7/11
 */
import java.nio.*;
import jssc.*;

public class GUISerialPort {
	
	private static SerialPort port = new SerialPort("COM5");
	private static ByteBuffer bb;
	
	private static int[] codes = new int[3];
	private static int[] angles = new int[3] ;
	
	private static final int CONVERT = 1; //will get real value later		
	private static int[] KEYS = {1600, 1700, 1800};
	
	public static void open(){
		try{
    		port.openPort();
    		port.setParams(115200, 8, 1, 0);
            port.setFlowControlMode(SerialPort.MASK_CTS);
    		System.out.println("1 written: " + port.writeString("1")); //initializes for angles; may need to alter
		}
    	
    	catch(SerialPortException e){
    		System.out.println("Failed to open " + port.getPortName() + " due to: "); 
    		System.out.println(e.getExceptionType());
    	}
	}
	
	public static double getCoors(){return 7;} //probably will use multiple methods here (for x and y of all three pivots)
	
	public static double getCurrent(){return 7;}
	
	public static int[] getAngles(){ //returns degree value b/t -360 and 360
	
		int[] retArray = new int[3];
		
		if(!port.isOpened()){
			for(int i = 0; i<3; i++)
				retArray[i] = 360;
		}
			
		else{
			
			try {
				port.writeString("2");
     			
     			for(int i = 0; i < 3; i++){
     				/*if(port.getInputBufferBytesCount() != 4*(3-i)){
     					port.purgePort(SerialPort.PURGE_RXCLEAR);
     					codes[i] = KEYS[i];
     				}*/
 
     					bb = ByteBuffer.wrap(port.readBytes(4));
     					bb.order(ByteOrder.LITTLE_ENDIAN);
     					codes[i] = bb.getInt();
     				
     				if(codes[i]!= KEYS[i])
     					System.out.println(codes[i]);
     					
     				angles[i] = (codes[i]*CONVERT-KEYS[i]) % 360;
     				if((codes[i]*CONVERT-KEYS[i]) < 0 && angles[i] > 0)
     					angles[i] -= 360;    				
     			}
     			retArray = angles;
     		}
    
     		catch(SerialPortException e){
     			System.out.println(e);
     			for(int i = 0; i<3; i++)
					retArray[i] = 7;
     		}
			
		}
		
		return retArray;
	}
}
