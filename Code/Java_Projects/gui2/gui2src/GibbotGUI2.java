/**
 * @(#)GibbotGUI2.java
 *
 *
 * @author 
 * @version 1.00 2014/7/17
 */


//import java.awt.*;
import javax.swing.*;

/*Sets up external window to display content*/
 
public class GibbotGUI2 extends JFrame{
    
    public static void main(String[] args) {
    	
    	SwingUtilities.invokeLater(new Runnable() {
      		public void run() {
        		GibbotGUI2 gui = new GibbotGUI2();
        		gui.setVisible(true);
        		//gui.setExtendedState(Frame.MAXIMIZED_BOTH);
      }
    });
  }

 	 private GibbotGUI2() {
    	GUITimer.start(500);
      	GUISerialPort.open(); 
      	ImageHandler.loadImages();
      	ImageHandler.drawImages();
    	
    	super.setLayout(null);	 	
    	super.setSize(1300,800);
    	super.setUndecorated(false);
      	super.setLocation(50,50);
      	super.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      	
      	LayoutContainerPanel content = new LayoutContainerPanel(super.getWidth(), super.getHeight());
      	super.setContentPane(content);    	     
    	
 	 }
    
}