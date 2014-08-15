/**
 * @(#)DebuggerGUITimer.java
 *
 *
 * @author 
 * @version 1.00 2014/8/15
 */

import java.awt.event.*;
import javax.swing.*;

public class DebuggerGUITimer {
	
	private static final int MILLISDELAY = 33;
    private static Timer timer = new Timer(MILLISDELAY, null);
    
    public static void start(){
    	timer.start();
    }
    
    public static void addActionListener(ActionListener listener){
    	timer.addActionListener(listener);  
    }
    
    public static void removeActionListener(ActionListener listener){
    	timer.removeActionListener(listener);
    }
    
}