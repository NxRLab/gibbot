/**
 * @(#)SelectorPanel.java
 *
 *
 * @author 
 * @version 1.00 2014/8/18
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class SelectorPanel extends JPanel{
	
	private String[] valNames = new String[] {"Theta1", "Theta2", "Theta3", "Current", "Torque", "Temperature", "Voltage", 
												"AccelX1", "AccelY1", "AccelZ1", "GyroX1", "GyroY1", "GyroZ1", 
													"AccelX2", "AccelY2", "AccelZ2", "GyroX2", "GyroY2", "GyroZ2"};


    public SelectorPanel() {
    	
    	super();
    	
    	setLayout(new GridBagLayout());
    	GridBagConstraints c = new GridBagConstraints();
    	c.anchor = GridBagConstraints.CENTER;
    	ChoiceBox cb;
    	JLabel name;
    	
    	for(int i = 0; i < 19; i++){
    		
    		c.gridy = i;
    		
    		c.gridx = 0;
    		name = new JLabel(valNames[i]);
    		add(name, c);
    		
    		c.gridx = 1;
    		cb = new ChoiceBox(new Integer[] {0, 1, 2, 3, 4}, i);
    		add(cb, c);
    		
    		c.gridx = 2;
    		f = new JTextField
    	}
    	
    }
    
    
}