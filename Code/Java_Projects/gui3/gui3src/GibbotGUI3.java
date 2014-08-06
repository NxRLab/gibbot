/**
 * @(#)GibbotGUI3.java
 *
 *
 * @author 
 * @version 1.00 2014/7/30
 */

import javax.swing.*;

/*Runs GUI. Note that GUISerialPort, GUITimer, and ImageHandler are activated here.
 *All visuals are contained in GUILayeredPane. setSize() parameters should
 *remain the same to preserve graphics quality; if screen size needs to be 
 *adjusted, setBounds() method for LayoutContainerPanels should be altered 
 *in GUILayeredPane.
 */
  
public class GibbotGUI3 extends JFrame{
    
    public static void main(String[] args) {
    	
    	SwingUtilities.invokeLater(new Runnable() {
      		public void run() {
        		GibbotGUI3 gui = new GibbotGUI3();
        		gui.setVisible(true);
        		gui.setExtendedState(MAXIMIZED_BOTH);
      }
    });
  }

 	 private GibbotGUI3() {
    	GUITimer.start(GUITimer.getMillisPerFrame());
      	GUISerialPort.open(); 
      	ImageHandler.loadImages();
      	ImageHandler.drawImages();
    		 	
    	super.setSize(1300, 800);
    	super.setUndecorated(true);
      	super.setLocation(50,50);
      	super.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      	
    	GUILayeredPane content = new GUILayeredPane(getWidth(), getHeight());
    	setContentPane(content);
    	
 	 }
    
}