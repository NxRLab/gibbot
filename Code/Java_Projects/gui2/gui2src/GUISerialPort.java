/**
 * @(#)GUISerialPort.java
 *
 *
 * @author 
 * @version 1.00 2014/7/11
 */
import java.awt.event.*;
import javax.swing.*;
import jssc.*;

public class GUISerialPort {
	
	private static SerialPort port = new SerialPort("COM5");
	 
	private static String str = "";
	private static String[] temp = new String[19];
	private static int[] tempInt = new int[19];
	private static int[] data = new int[19];
	private static boolean sending = false;
	
	public static void open(){
		try{
    		port.openPort();
    		port.setParams(115200, 8, 1, 0);
            port.setFlowControlMode(SerialPort.MASK_CTS);
		}
    	
    	catch(SerialPortException e){
    		System.out.println("Failed to open " + port.getPortName() + " due to: "); 
    		System.out.println(e.getExceptionType());
    	}
    	
    	for(int i = 0; i < 19; i++){
			data[i] = 20;
    	}
	}
	
	public static double getCoors(){return 7;} //probably will use multiple methods here (for x and y of all three pivots)
	
	public static int[] getData(){
		return data;
	}	 
	
	public static void update(){  //called by GibbotGUI2 in response to timer-generated events
		
		if(!port.isOpened()){
			
			for(int i = 0; i < 19; i++){
				data[i] = 0;
			}
		}
		
		if(sending)
			return;
			
		else{
			
			try {
				String next;
				port.writeString("q");
				/*while(true){
					next = port.readString(1);
					if(next == "\n")
						break;				
					else{
						if(next != null)
							str += next;
					}
				}*/
				str = port.readString();
				
				System.out.println(str);
				if(str == null)
					return;
				temp = str.split(" ");
				if(temp.length != 19)
					return;
				
				tempInt[0] = Integer.parseInt(temp[0]);
				tempInt[1] = Integer.parseInt(temp[1]);
				tempInt[2] = Integer.parseInt(temp[2]);
				tempInt[3] = (int)(Float.parseFloat(temp[3])*7.5);
				tempInt[4] = (int)Float.parseFloat(temp[4]);
				tempInt[5] = (int)(Float.parseFloat(temp[5])); //add *2 scalar when we have real vals
				tempInt[6] = (int)((Float.parseFloat(temp[6]))*4); //?
				tempInt[7] = (int)(Float.parseFloat(temp[7])*35);
				tempInt[8] = (int)(Float.parseFloat(temp[8])*35);
				tempInt[9] = (int)(Float.parseFloat(temp[9])*35);
				tempInt[10] = (int)Float.parseFloat(temp[10]);
				tempInt[11] = (int)Float.parseFloat(temp[11]);
				tempInt[12] = (int)Float.parseFloat(temp[12]);
				tempInt[13] = (int)(Float.parseFloat(temp[13])*35);
				tempInt[14] = (int)(Float.parseFloat(temp[14])*35);
				tempInt[15] = (int)(Float.parseFloat(temp[15])*35);
				tempInt[16] = (int)Float.parseFloat(temp[16]);
				tempInt[17] = (int)Float.parseFloat(temp[17]);
				tempInt[18] = (int)Float.parseFloat(temp[18]);
				
				data = tempInt;
					
				}
				
				
    
     		catch(SerialPortException e){
     			for(int i = 0; i < 19; i++){
					data[i] = 100;
				}
     		}
			
		}

	}
	
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

