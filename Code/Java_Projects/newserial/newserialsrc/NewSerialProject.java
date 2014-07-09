/**
 * @(#)NewSerialProject.java
 *
 *
 * @author 
 * @version 1.00 2014/7/9
 */

public class NewSerialProject {
	
	public static void main(String[] args){
		
		NewSerialTester tester = new NewSerialTester();
		tester.searchAndConnect();
		tester.simpleIOTest();
	}   
}