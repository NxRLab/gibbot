/**
 * @(#)SerialTester.java
 *
 *
 * @author 
 * @version 1.00 2014/7/3
 */

import gnu.io.*;
import java.awt.Color;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.TooManyListenersException;
import javax.swing.JFrame;

public class SerialTester implements SerialPortEventListener {
    
    //for containing the ports that will be found
    private Enumeration ports = null;
    //map the port names to CommPortIdentifiers
    private HashMap portMap = new HashMap();

    //this is the object that contains the opened port
    private CommPortIdentifier selectedPortIdentifier = null;
    private SerialPort serialPort = null;

    //input and output streams for sending and receiving data
    private InputStream input = null;
    private OutputStream output = null;

    //just a boolean flag that i use for enabling
    //and disabling buttons depending on whether the program
    //is connected to a serial port or not
    //NOT USING GUI NOW// private boolean bConnected = false;
    
    private String[] options = new String[20]; //Possibility of overflow here but will serve the current purpose

    //the timeout value for connecting with the port
    final static int TIMEOUT = 2000;

    //some ascii values for for certain things
    final static int SPACE_ASCII = 32;
    final static int DASH_ASCII = 45;
    final static int NEW_LINE_ASCII = 10;

    //a string for recording what goes on in the program
    //this string is written to the GUI
    //NOT USING GUI NOW//String logText = "";
    
    public void serialEvent(){}
    
    
    /*finds all ports and adds serial ones to portMap*/
    public void searchForPorts()
    {
        ports = CommPortIdentifier.getPortIdentifiers(); //static method! :D
        
        int i = 0;

        while (ports.hasMoreElements())
        {
            CommPortIdentifier curPort = (CommPortIdentifier)ports.nextElement();

            //get only serial ports
            if (curPort.getPortType() == CommPortIdentifier.PORT_SERIAL)
            {
                //NOT USING GUI NOW//window.cboxPorts.addItem(curPort.getName());
                portMap.put(curPort.getName(), curPort);
                options[i] = curPort.getName();
                
            }
        }
    }
    
    public void connect()
    {
        //NOT USING GUI NOW//String selectedPort = (String)window.cboxPorts.getSelectedItem();
        
    	PortPane content = new PortPane(options);
    	
    	JFrame container = new JFrame("Connection options");
    	container.setSize(500, 500);
    	container.setLocation(300, 300);
    	container.setContentPane(content);
    	container.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	container.setVisible(true);
    	
    	while(content.buttonClicked == false) {}
    	
    	String selectedPort = content.getDesiredMessage();
        
        selectedPortIdentifier = (CommPortIdentifier)portMap.get(selectedPort);

        CommPort commPort = null;

        try
        {
            //the method below returns an object of type CommPort KT NOTE: opens communication port; first param is the name of the
            //owner of this port now
            commPort = selectedPortIdentifier.open("Gibbot", TIMEOUT);
            //the CommPort object can be casted to a SerialPort object
            serialPort = (SerialPort)commPort;

            //for controlling GUI elements
            //NOT USING GUI NOW//setConnected(true);

            //logging
            //NOT USING GUI NOW//logText = selectedPort + " opened successfully.";
            //NOT USING GUI NOW//window.txtLog.setForeground(Color.black);
            //NOT USING GUI NOW//window.txtLog.append(logText + "\n");

            //CODE ON SETTING BAUD RATE ETC OMITTED
            //XBEE PAIR ASSUMED TO HAVE SAME SETTINGS ALREADY

            //enables the controls on the GUI if a successful connection is made
            //NOT USING GUI NOW//window.keybindingController.toggleControls();
        }
        catch (PortInUseException e)
        {
            //NOT USING GUI NOW//logText = selectedPort + " is in use. (" + e.toString() + ")";

            //NOT USING GUI NOW//window.txtLog.setForeground(Color.RED);
            //NOT USING GUI NOW//window.txtLog.append(logText + "\n");
        }
        catch (Exception e)
        {
            //NOT USING GUI NOW//logText = "Failed to open " + selectedPort + "(" + e.toString() + ")";
            //NOT USING GUI NOW//window.txtLog.append(logText + "\n");
            //NOT USING GUI NOW//window.txtLog.setForeground(Color.RED);
        }
    }
    
    public boolean initIOStream()
    {
        //return value for whether opening the streams is successful or not
        boolean successful = false;

        try {
            //
            input = serialPort.getInputStream();
            output = serialPort.getOutputStream();
            writeData(0, 0); //This method below

            successful = true;
            return successful;
        }
        catch (IOException e) {
            //NOT USING GUI NOW//logText = "I/O Streams failed to open. (" + e.toString() + ")";
            //NOT USING GUI NOW//window.txtLog.setForeground(Color.red);
            //NOT USING GUI NOW//window.txtLog.append(logText + "\n");
            return successful;
        }
    }
    
    public void initListener()
    {
        try
        {
            serialPort.addEventListener(this);
            serialPort.notifyOnDataAvailable(true); //KT NOTE: tells it when to listen (I think?)
        }
        catch (TooManyListenersException e)
        {
            //NOT USING GUI NOW//logText = "Too many listeners. (" + e.toString() + ")";
            //NOT USING GUI NOW//window.txtLog.setForeground(Color.red);
            //NOT USING GUI NOW// window.txtLog.append(logText + "\n");
        }
    }
    
    public void disconnect()
    {
        //close the serial port
        try
        {
            writeData(0, 0);

            serialPort.removeEventListener();
            serialPort.close();
            input.close();
            output.close();
            //NOT USING GUI NOW//setConnected(false);
            //NOT USING GUI NOW//window.keybindingController.toggleControls();

            //NOT USING GUI NOW//logText = "Disconnected.";
            //NOT USING GUI NOW//window.txtLog.setForeground(Color.red);
            //NOT USING GUI NOW//window.txtLog.append(logText + "\n");
        }
        catch (Exception e)
        {
            //NOT USING GUI NOW//logText = "Failed to close " + serialPort.getName() + "(" + e.toString() + ")";
            //NOT USING GUI NOW//window.txtLog.setForeground(Color.red);
            //NOT USING GUI NOW//window.txtLog.append(logText + "\n");
        }
    }
    
    public void serialEvent(SerialPortEvent evt) { 			//Required for SerialPortEventListener, serves as readData method
        if (evt.getEventType() == SerialPortEvent.DATA_AVAILABLE)
        {
            try
            {
                byte singleData = (byte)input.read();

                if (singleData != NEW_LINE_ASCII)
                {
                    //NOT USING GUI NOW//logText = new String(new byte[] {singleData});
                    //NOT USING GUI NOW//window.txtLog.append(logText);
                }
                else
                {
                    //NOT USING GUI NOW//window.txtLog.append("\n");
                }
            }
            catch (Exception e)
            {
                //NOT USING GUI NOW//logText = "Failed to read data. (" + e.toString() + ")";
                //NOT USING GUI NOW//window.txtLog.setForeground(Color.red);
                //NOT USING GUI NOW//window.txtLog.append(logText + "\n");
            }
        }
    }
    
    public void writeData(int leftThrottle, int rightThrottle)
    {
        try
        {
            output.write(leftThrottle);
            output.flush();
            //this is a delimiter for the data
            output.write(DASH_ASCII);
            output.flush();

            output.write(rightThrottle);
            output.flush();
            //will be read as a byte so it is a space key
            output.write(SPACE_ASCII);
            output.flush();
        }
        catch (Exception e)
        {
            //NOT USING GUI NOW//logText = "Failed to write data. (" + e.toString() + ")";
            //NOT USING GUI NOW//window.txtLog.setForeground(Color.red);
            //NOT USING GUI NOW//window.txtLog.append(logText + "\n");
        }
    }
    
    
    
    
    
    
}