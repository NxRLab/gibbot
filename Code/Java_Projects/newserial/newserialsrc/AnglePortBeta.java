import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.nio.*;
import jssc.*;


//works with motor encoders to measure rotation//
class AnglePortBeta extends SerialPort implements SerialPortEventListener {
	
	private ByteBuffer bb;
	
	private int[] codes;
	private double[] angles;
	
	private final int CONVERT = 1; //Will get real value later
	
	public AnglePortBeta(String name){
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
     			
     			for(int i = 0; i < 3; i++){
     				bb = ByteBuffer.wrap(readBytes(4));
     				bb.order(ByteOrder.LITTLE_ENDIAN);
     				codes[i] = bb.getInt();
     				angles[i] = codes[i]*CONVERT;
     				
     			}
     			
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
	
	public void sendSignal(){
		try{
			writeString("2");
		}
		
		catch(SerialPortException e){
     		System.out.println(e);
     	}
		
		}
		
	public double getAngle(int i){
		//some check to make sure 0<=i<3
		
		return angles[i];
	}
}

