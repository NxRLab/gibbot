
import javax.swing.*;
import java.awt.Color;

/**GibbotGUI3 is a JFrame (window) object that runs the GUI. 
 *Note that {@link GUISerialPort}, {@link GUITimer}, and {@link ImageHandler} are activated here.
 *All visuals are contained in an instance of {@link GUILayeredPane}. 
 */
public class GibbotGUI3 extends JFrame{
	
	/**Background color for all elements in the awake view.*/
	public static final Color GLOBAL_BG = Color.WHITE;
	/**Background color for chart animations*/
	public static final Color SECONDARY_GLOBAL_BG = new Color(240, 240, 240);
	
	/**Panel that contains all graphics.*/
	private static GUILayeredPane content;
    
   /** Main method that runs.
    *@param args String array of arguments when program is run on command line (handled in the background)*/
    public static void main(String[] args) {
    	
    	SwingUtilities.invokeLater(new Runnable() {
      		public void run() {
        		GibbotGUI3 gui = new GibbotGUI3();
        		gui.setVisible(true);
        		gui.setExtendedState(MAXIMIZED_BOTH);
      }
    });
  }
	 /**Constructor for the GibbotGUI3 object. Parameters of setSize() call should remain the same to preserve 
	 graphics quality; if screen size needs to be adjusted, parameters of setBounds() calls for awake and asleep panels 
	 should be altered in constructor code of {@link GUILayeredPane}.*/
  	 	
 	 private GibbotGUI3() {
    	GUITimer.start();
      	GUISerialPort.openPort(); 
      	ImageHandler.loadImages();
      	ImageHandler.drawImages();

    	super.setUndecorated(true);
      	super.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      	
    	content = new GUILayeredPane();
    	setContentPane(content);
    	
 	 }
    
}