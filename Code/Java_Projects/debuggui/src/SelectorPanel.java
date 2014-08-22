/**
 * @(#)Sa
 *
 * @author 
 * @version 1.00 2014/8/18
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class SelectorPanel extends JPanel{
	
	Color[] colors = new Color[]{Color.BLACK, new Color(0, 229, 221), Color.RED, new Color(15, 229, 0), Color.MAGENTA, Color.GRAY, 
									new Color(210, 0, 0), Color.BLUE, Color.ORANGE, Color.PINK, new Color(129,215,145), 
										new Color(244,128,90), new Color(140,63,43), new Color(145, 0, 255), new Color(160,172,188), 
										   new Color(169,82,214), new Color(255, 188, 0), new Color(41,118,137), new Color(86, 127, 53)};
	
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
    	ScaleTextField f;
    	
    	for(int i = 0; i < 19; i++){
    		
    		c.gridy = i;
    		
    		c.gridx = 0;
    		name = new JLabel(valNames[i]);
    		name.setForeground(colors[i]);
    		add(name, c);
    		
    		c.gridx = 1;
    		cb = new ChoiceBox(new Integer[] {0, 1, 2, 3, 4}, i);
    		add(cb, c);
    		
    		c.gridx = 2;
    		f = new ScaleTextField("Scale", i);
    		add(f, c);
    	}
    }
    	
    }
    
    
