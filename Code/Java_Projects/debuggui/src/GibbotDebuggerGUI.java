/**
 * @(#)GibbotDebuggerGUI.java
 *
 * GibbotDebuggerGUI application
 *
 * @author 
 * @version 1.00 2014/8/15
 */
 import java.awt.*;
 import javax.swing.*;
 
public class GibbotDebuggerGUI {
    
    public static void main(String[] args) {
    	
    	SwingUtilities.invokeLater(new Runnable() {
      		public void run() {
        		createAndShowGUI();
      		}
    	});
    }
    
    public static void createAndShowGUI(){
    	
    	JFrame frame = new JFrame();
    	frame.setSize(1000, 600);
    	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	frame.add(new DebuggerLayoutPanel());
    	frame.setVisible(true);
    	DebuggerGUITimer.start();
    	GraphArrayUpdater.start();
    	DebuggerGUISerialPort.openPort();
    	
    }
}
