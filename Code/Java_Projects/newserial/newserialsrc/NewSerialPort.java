
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.nio.*;
import jssc.*;


//works with f-w program on XBee//
public class NewSerialPort extends SerialPort implements SerialPortEventListener {
	
	public NewSerialPort(String name){
		super(name);
	}
	
	public void addEventListener(){
		try{
			addEventListener(this);
		}
		catch(SerialPortException e){
			System.out.println(e);
		}
	
	}
	
	public void serialEvent(SerialPortEvent evt){
     	
     	if(evt.isRXCHAR()){
     			try {
     			
     			String read = readString();
     			System.out.println(read);
     			BufferedReader br = new BufferedReader( new InputStreamReader(System.in));
				String s = br.readLine();
				
				writeString(s);
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
