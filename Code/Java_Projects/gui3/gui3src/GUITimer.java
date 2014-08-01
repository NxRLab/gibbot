/**
 * @(#)GUITimer.java
 *
 *
 * @author 
 * @version 1.00 2014/7/17
 */

import java.awt.event.*;
import javax.swing.*;

public class GUITimer {
	
	private static Timer timer;
	private static int delay;
	private static int serialFactor = 10;
	private static int millisPerFrame = 33;
	
    
    public static void start(int millisDelay){
    	delay = millisDelay;
    	timer = new Timer(delay, null);
    	timer.start();
    }
    
    public static void addActionListener(ActionListener listener){
    	timer.addActionListener(listener);
    }
    
    public static void removeActionListener(ActionListener listener){
    	timer.removeActionListener(listener);
    }
    
    public static int getDelay(){
    	return delay;
    }
    
    public static int getSerialFactor(){
    	return serialFactor;
    }
    
    public static int getMillisPerFrame(){
    	return millisPerFrame;
    }
    
    
}