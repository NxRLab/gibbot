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
    
    public static void start(int millisDelay){
    	timer = new Timer(millisDelay, null);
    	timer.start();
    }
    
    public static void addActionListener(ActionListener listener){
    	timer.addActionListener(listener);
    }
    
    public static void removeActionListener(ActionListener listener){
    	timer.removeActionListener(listener);
    }
    
    
}