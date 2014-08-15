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
    	frame.setSize(500, 500);
    	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	frame.add(new ButtonPanel(), BorderLayout.CENTER);
    	frame.setVisible(true);
    	DebuggerGUITimer.start();
    }
}
