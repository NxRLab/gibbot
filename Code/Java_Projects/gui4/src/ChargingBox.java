
import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

/**Displays battery level in "sleep" mode. Based on max battery level 
 *from 8 3.6V batteries in series.
 */
public class ChargingBox extends JPanel implements ActionListener {
	
	private Image batteryBar = ImageHandler.getImage("batteryBar.png");
	
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
	
	private int MAX_BATT = 230; //230 is hardcoded for beta test, will be replaced with actual max battery value

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
    	
    	int width = batteryBar.getWidth(this);
    	int height = batteryBar.getHeight(this);
    	g.drawImage(batteryBar, (int)(width*0.414), (int)(height*0.142), width, height, this); //+23 to make space for the max
    																									 //exactly 2*((int)4*max) voltage.
    																									 //See update() method of GUISerialPort. 
    	g.setColor(GREEN);
    	if(batt < MAX_BATT){
    		g.fillRect((int)(width*0.51), (int)(height*1.104) - batt, (int)(width*0.841), batt);
    	}
    	else{
    		g.fillRect((int)(width*0.51), (int)(height*1.104) - MAX_BATT, (int)(width*0.841), MAX_BATT);
    	}
    }
    
    /**Specifies how to respond to timer events from {@link GUITimer}. This panel uses events as a signal to 
    update {@link batt} by getting battery value from {@link GUISerialPort#data} at frequency determined by SEC_PER_UPDATE
    @param evt The timer event (not important to code but required by {@link java.awt.event#ActionListener} interface)
    */
    public void actionPerformed(ActionEvent evt){

    	if(timerCount == SEC_PER_UPDATE*1000/millisPerFrame){ 
    		//batt = GUISerialPort.getData().get("batteryVoltage"); Will be used when live-updating is incorporated
    		batt+=10; //hardcoded for beta test
    		timerCount = 0;
    		repaint();
    	}
    	else
    		timerCount++;
    	
    }
    
}