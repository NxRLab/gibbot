/**
 * @(#)GUISerialPort.java
 *
 *
 * @author 
 * @version 1.00 2014/7/11
 */
import java.util.concurrent.TimeUnit;
import java.util.Random;
import jssc.*;

public class GUISerialPort extends SerialPort {
	
	Random generator = new Random();

    public GUISerialPort(String portName) {
    	
    	super(portName);
    }
    
    public boolean openPort(){
    	
    	boolean retVal = false;
    	
		try {
			retVal = super.openPort();
    		setParams(230400, 8, 1, 0);
        	setFlowControlMode(SerialPort.MASK_CTS);
		}
        
        catch(SerialPortException e){
        	System.out.println(e);
        }

        	return retVal;   	

    	
    }
    
    public int getGraphVal() {
    	
    	int write = generator.nextInt(5)+1;
    	String read = "-1";
    	String retVal="";
    	
    	try {
    		super.writeString(write+"\n");
    		try{
				TimeUnit.MILLISECONDS.sleep(20);
    		}
    		catch(InterruptedException e){
    			System.out.println(e);
    		}
    		read = super.readString();
    		for(int i = 0; i < read.length(); i++){          
    			if(read.substring(i, i + 1).matches("[0-9]"))
    				retVal += read.substring(i, i + 1);
    		}
    		return Integer.parseInt(retVal, 10);
    	}
    	catch(SerialPortException e) {
    		System.out.println(e);
    		return 0;
    	}
    	
    	catch(NumberFormatException e){
    		System.out.println(e);
    		return 0;
    	}
    }
}
    
    
