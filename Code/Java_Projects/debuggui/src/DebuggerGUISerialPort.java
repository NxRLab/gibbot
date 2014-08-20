/**
 * @(#)DebuggerGUISerialPort.java
 *
 *
 * @author 
 * @version 1.00 2014/8/15
 */

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.nio.*;
import java.nio.charset.*;
import java.sql.Timestamp;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Date;
import javax.swing.*;
import jssc.*;

public class DebuggerGUISerialPort {
	
	public static final String OUTPUT_FILE_NAME = "out_bytes.txt";
	
	private static BufferedOutputStream bos;
	
	private static boolean logging;
	
	private static SerialPort port = new SerialPort("COM5");
	
	private static byte[] bytesData;
	private static int[] anglesData = new int[3];
	private static float[] floatsData = new float[16]; 
		
	private static PortListener listener = new PortListener();

    public static void openPort() {
    	try{
    		port.openPort();
    		port.setParams(115200, 8, 1, 0);
            port.setFlowControlMode(SerialPort.MASK_CTS);
		}
    	
    	catch(SerialPortException e){
    		System.out.println("Failed to open " + port.getPortName() + " due to: "); 
    		System.out.println(e.getExceptionType());
    	}
    	
    	for(int i = 0; i < 3; i++){
			anglesData[i] = 20;
    	}
    	
    	for(int i = 0; i < 16; i++){
    		floatsData[i] = 40;
    	}
    	byte b = 43;
    	bytesData = new byte[70];
    	Arrays.fill(bytesData, b);
    	
    	DebuggerGUITimer.addActionListener(listener);
    }
    
    private static class PortListener implements ActionListener{

    	private static ByteBuffer bb;
	
		private static final byte SPACE = ' ';
		private static final byte ASTERIX = '*';
		private static final int CR = 13; //carriage return
		private static final int NL = 10; //new line
		private static Timestamp currentTimestamp;
		private static byte[] time = new byte[23];

	    public void actionPerformed(ActionEvent evt){
    		
	    	if(port.isOpened()){
    		
    			try{
    				
    				port.writeString("r");
    			
    				int totalBytes = port.getInputBufferBytesCount();
    				
	    			if(totalBytes == 70){
    					bytesData = port.readBytes();
    				
    					for(int i = 0; i < 3; i++){
    						bb = ByteBuffer.wrap(bytesData, 2*i, 2);
    						bb.order(ByteOrder.LITTLE_ENDIAN);
    						anglesData[i] = (int)bb.getChar();
    					}
    				
	    				for (int i = 0; i < 16; i++){
    						bb = ByteBuffer.wrap(bytesData, 4*i + 6, 4);
    						bb.order(ByteOrder.LITTLE_ENDIAN);
    						floatsData[i] = bb.getFloat();
    					}
    				
    					if(logging){
    						currentTimestamp = new Timestamp(Calendar.getInstance().getTime().getTime());
							time = currentTimestamp.toString().getBytes();
							bos.write(SPACE);
							bos.write(time.length);
							bos.write(time);
							bos.write(70);
    						bos.write(SPACE);
							bos.write(bytesData);
							bos.flush();
	    				}
    				}
    				else{
    					bytesData = port.readBytes();
    					
    					if(logging){
    						
    						if(totalBytes == 0){
    							currentTimestamp = new Timestamp(Calendar.getInstance().getTime().getTime());
								time = currentTimestamp.toString().getBytes();
								bos.write(SPACE);
								bos.write(time.length);
								bos.write(time);
								bos.write(totalBytes);    						
    							bos.write(ASTERIX);
    							bos.flush();
    						}
    						
    						else{
	    						currentTimestamp = new Timestamp(Calendar.getInstance().getTime().getTime());
								time = currentTimestamp.toString().getBytes();
								bos.write(SPACE);
								bos.write(time.length);
								bos.write(time);
								bos.write(totalBytes);    						
    							bos.write(ASTERIX);
								bos.write(bytesData);
								bos.flush();
	    					}
    					}
    				}
    			}
    		
    			catch(Exception e){
    				e.printStackTrace();
    			}
   	 		}
   	 	
   	 	else{
    		if(logging){
    			try{
	    			currentTimestamp = new Timestamp(Calendar.getInstance().getTime().getTime());
					time = currentTimestamp.toString().getBytes();
					bos.write(SPACE);
					bos.write(time.length);
					bos.write(time);
					bos.write(70);
    				bos.write(SPACE);
					bos.write(bytesData);
					bos.flush();
    			}
 	   			
 		   		catch(Exception e){
    				e.printStackTrace();
	    			}
    			}
    		}
	    }
	}
    
    public static int[] getAngles(){
    	return anglesData;
    }
    
    public static float[] getFloats(){
    	return floatsData;
    }
    
    public static void startLogging(){
    	try{
			bos = new BufferedOutputStream(new FileOutputStream(OUTPUT_FILE_NAME));
			logging = true;
		}
		catch(FileNotFoundException e){
			e.printStackTrace();
		}
    }
    
    public static void stopLogging(){
		try{
			if(port.isOpened()){
				port.purgePort(SerialPort.PURGE_RXCLEAR);
				bos.close();
			}	
			logging = false;
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
}