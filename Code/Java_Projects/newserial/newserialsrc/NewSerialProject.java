/**
 * @(#)NewSerialProject.java
 *
 *
 * @author 
 * @version 1.00 2014/7/9
 */

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.TooManyListenersException;
import jssc.*;

public class NewSerialProject {
	
	static SerialPort port = new SerialPort("COM3");
	
	public static void main(String[] args){
		
		boolean connected;
		
		try{
    		connected = port.openPort();
    		port.setParams(230400, 8, 1, 0);
    		int mask = SerialPort.MASK_RXCHAR + SerialPort.MASK_CTS;
            port.setEventsMask(mask);//Set mask
            port.setFlowControlMode(SerialPort.MASK_CTS);
    		port.addEventListener(new SListener());
    	}
    	
    	catch(SerialPortException e){
    		System.out.println("Failed to open " + port.getPortName() + " due to: "); 
    		System.out.println(e.getExceptionType());
    	}
	}
	
	static class SListener implements SerialPortEventListener {

    public void serialEvent(SerialPortEvent evt){
     	
     	if(evt.isRXCHAR()){
     		try {
     			System.out.println(port.readString());
     			BufferedReader br = new BufferedReader( new InputStreamReader(System.in));
				String s = br.readLine();
				port.writeString(s+"\n");
				return;
     		}
     		catch(SerialPortException e){
     			System.out.println(e);
     		}
     		
     		catch(IOException e){
     			System.out.println(e);
     		}
     	}
     	
    }
}   
}