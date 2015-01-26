
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**Displays battery level in "sleep" mode. Based on max battery level 
 *from 8 3.6V batteries in series.
 */
public class ChargingBox extends JPanel implements ActionListener {
	
	private Image batteryBar = ImageHandler.getImage("batteryBar");
	
	/**How many seconds the panel waits between checks for change in battery level*/
	private final int SEC_PER_UPDATE = 10;
	/**Color of bar that indicates battery level*/
	private final Color GREEN = new Color(0, 204, 0, 200);
	/**Used to update {@link #batt} at even intervals*/
	private int timerCount;
	/**Used to update {@link #batt} at even intervals; set by call to {@link GUITimer#getMillisPerFrame} in constructor*/
	private int millisPerFrame;
	
	/**Value of battery level that's displayed in the graph*/
	private int batt;

	/**Constructor initializes {@link #batt} and {@link #timerCount} to zero, gets {@link #millisPerFrame}.*/
    public ChargingBox() {

    	batt = 0;
    	millisPerFrame = GUITimer.getMillisPerFrame();	
    	timerCount = 0;
    	GUITimer.addActionListener(this);
    	   
    }
    
    /**Override of {@link javax.swing.JComponent#paintComponent}. super.paintComponent() call fills background color.
    This is what is executed whenever repaint() is called in the program. 
    Draws empty battery bar image, then draws a green rectangle to represent charge level.
    @param g Graphics context for drawing. Kind of a black box; gets handled in the background somehow
    */ 
    public void paintComponent(Graphics g){
    	
    	super.paintComponent(g);
    	
    	g.drawImage(batteryBar, 0, 0, batteryBar.getWidth(this), batteryBar.getHeight(this) + 23, this); //+23 to make space for the max
    																									 //height of the charge bar to be
    																									 //exactly 2*((int)4*max) voltage.
    																									 //See update() method of GUISerialPort. 
    	g.setColor(GREEN);
    	g.fillRect(81, 299 - batt, 113, batt);
    }
    
    /**Specifies how to respond to timer events from {@link GUITimer}. This panel uses events as a signal to 
    update {@link batt} by getting battery value from {@link GUISerialPort#data} at frequency determined by SEC_PER_UPDATE
    @param evt The timer event (not important to code but required by {@link java.awt.event#ActionListener} interface)
    */
    public void actionPerformed(ActionEvent evt){
    	
    	if(timerCount == SEC_PER_UPDATE*1000/millisPerFrame){ 
    		batt = GUISerialPort.getData()[3]*2; //*2 to scale
    		timerCount = 0;
    		repaint();
    	}
    	else
    		timerCount++;
    }
    
}