/**
 * @(#)NewSerialProject.java
 *
 *
 * @author 
 * @version 1.00 2014/7/9
 */
import java.util.concurrent.TimeUnit;
import jssc.*;

public class NewSerialProject {
	
	static AnglePortBeta port = new AnglePortBeta("COM5");
	
	public static void main(String[] args){
		
		boolean connected=false;
		
		try{
    		connected = port.openPort();
    		port.setParams(115200, 8, 1, 0);
            port.setFlowControlMode(SerialPort.MASK_CTS);
            port.addEventListener();
    		System.out.println("1 written: " + port.writeString("1")); //or for NewSerialPort: System.out.println("f written: " + port.writeString("f"));
		}
    	
    	catch(SerialPortException e){
    		System.out.println("Failed to open " + port.getPortName() + " due to: "); 
    		System.out.println(e.getExceptionType());
    	}
    		
    }
}
    		
    	
	
	
