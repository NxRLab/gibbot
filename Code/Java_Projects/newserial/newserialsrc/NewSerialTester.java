/**
 * @(#)NewSerialTester.java
 *
 *
 * @author 
 * @version 1.00 2014/7/9
 */

import java.awt.*;
import java.awt.event.*;
import java.awt.Color;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.TooManyListenersException;
import javax.swing.*;
import jssc.*;

public class NewSerialTester {
	
	SerialPort selectedPortIdentifier;
	boolean connected;
    
     public void searchAndConnect(){
    	
    	String[] options = SerialPortList.getPortNames();
    	
    	if(options.length == 0);{
    		
    		options = new String[1];
    		options[0] = "No ports found";
    	}
    	
    	PortPane content = new PortPane(options);
    	
    	JFrame container = new JFrame("Connection options");
    	container.setSize(500, 500);
    	container.setLocation(300, 300);
    	container.setContentPane(content);
    	container.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	container.setVisible(true);
    	
    	int i = 0;
    	
    	while(content.buttonClicked == false){
    		System.out.println("in loop");
    	}
    	
    	System.out.println("out of loop");
    	
    	String selectedPort = content.getDesiredMessage();
    	
    	selectedPortIdentifier = new SerialPort(selectedPort);
    	
    	try{
    		connected = selectedPortIdentifier.openPort();
    	}
    	
    	catch(SerialPortException e){
    		System.out.println("Failed to open"); 
    		System.out.println(selectedPort + " due to: " + e.getExceptionType());
    	}
        
    }
    
    public void simpleIOTest(){
    	if(!connected)
    		return;
    	
    	try{
    		System.out.println("Params setted: " + selectedPortIdentifier.setParams(9600, 8, 1, 0)); //Baud, data, stop, parity
            System.out.println("\"Hello World!!!\" successfully writen to port: " + selectedPortIdentifier.writeBytes("Hello World!!!".getBytes()));
            System.out.println("Port closed: " + selectedPortIdentifier.closePort());
    	}
    	
    	catch(SerialPortException e){
    		System.out.println(e);
    	}
    }
    
    
    
}