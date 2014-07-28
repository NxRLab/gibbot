/**
 * @(#)GUISerialPort.java
 *
 *
 * @author 
 * @version 1.00 2014/7/11
 */
import java.awt.event.*;
import java.nio.*;
import javax.swing.*;
import jssc.*;

public class GUISerialPort {
	
	private static SerialPort port = new SerialPort("COM5");
	private static ByteBuffer bb;
	
	private static String[] dataS = new String[3];
	private static float[] dataF = new float[16]; 
	private static String str = "";
	private static String[] temp = new String[19];
	
	public static void open(){
		try{
    		port.openPort();
    		port.setParams(115200, 8, 1, 0);
            port.setFlowControlMode(SerialPort.MASK_CTS);
    		//System.out.println("1 written: " + port.writeString("1")); //initializes for angles; may need to alter
		}
    	
    	catch(SerialPortException e){
    		System.out.println("Failed to open " + port.getPortName() + " due to: "); 
    		System.out.println(e.getExceptionType());
    	}
    	
    	for(int i = 0; i < 19; i++){
			if(i < 3)
				dataS[i] = "360";
			else
				dataF[i-3] = 7;
    	}
	}
	
	public static double getCoors(){return 7;} //probably will use multiple methods here (for x and y of all three pivots)
	
	public static String[] getDataS(){
		return dataS;
	}
	
	public static float[] getDataF(){
		return dataF;
	}	 
	
	public static void update(){  //called by GibbotGUI2 in response to timer-generated events
		
		if(!port.isOpened()){
			
						for(int i = 0; i < 19; i++){
							if(i < 3)
								dataS[i] = "180";
							else
								dataF[i-3] = 20;
						}
					}
			
		else{
			
			try {
				
				if(port.getInputBufferBytesCount() != 0)
					return;

				port.writeString("q");
				try{
					Thread.sleep(200);
				}
				catch(InterruptedException e){
					System.out.println("interrupted");
				}
				str = port.readString();
				if(str == null)
					return;
				System.out.println(str);
				temp = str.split(" ");
				
				for(int i = 0; i < 19; i++){
					if(i < 3)
						dataS[i] = temp[i];
					else
						dataF[i-3] = Float.parseFloat(temp[i]);
				}

			}
    
     		catch(SerialPortException e){
     			for(int i = 0; i < 19; i++){
					if(i < 3)
						dataS[i] = "7";
					else
						dataF[i-3] = 7;
     			}
     		}
			
		}

	}
}

