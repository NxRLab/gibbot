/**
 * @(#)ChargingBox.java
 *
 *
 * @author 
 * @version 1.00 2014/8/6
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*Displays battery level in "sleep" mode. Based on max battery level 
 *from 8 3.6V batteries in series.
 */

public class ChargingBox extends JPanel implements ActionListener {
	
	private Image batteryBar = ImageHandler.getImage("batteryBar");
	
	private int timerCount;
	private int millisPerFrame;
	
	private int batt;

    public ChargingBox() {

    	batt = 0;
    
    	millisPerFrame = GUITimer.getMillisPerFrame();	
    	timerCount = 0;
    	GUITimer.addActionListener(this);   
    }
    
    public void paintComponent(Graphics g){
    	
    	super.paintComponent(g);
    	
    	g.drawImage(batteryBar, 0, 0, batteryBar.getWidth(this), batteryBar.getHeight(this) + 23, this); //+23 to make space for the max
    																									 //height of the charge bar to be
    																									 //exactly 2*((int)4*max) voltage.
    																									 //See update() method of GUISerialPort. 
    	g.setColor(new Color(0, 204, 0, 200));
    	g.fillRect(81, 299 - batt, 113, batt);
    }
    
    public void actionPerformed(ActionEvent evt){
    	
    	if(timerCount == 10000/millisPerFrame){ //updates battery icon every 10 seconds
    		batt = GUISerialPort.getData()[3]*2;
    		timerCount = 0;
    		repaint();
    	}
    	else
    		timerCount++;
    }
    
}