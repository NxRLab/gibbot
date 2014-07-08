/**
 * @(#)SerialProject.java
 *
 *
 * @author 
 * @version 1.00 2014/7/8
 */


public class SerialProject {
    
    public static void main(String[] args) {
    	
    	SerialTester test = new SerialTester();
    	test.searchForPorts();
    	test.connect();
    	test.initIOStream();
    	test.initListener();
    	//test.doStuff();
    	test.disconnect();
    }
}





































