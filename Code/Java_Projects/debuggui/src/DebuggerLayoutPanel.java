/**
 * @(#)DebuggerLayoutPanel.java
 *
 *
 * @author 
 * @version 1.00 2014/8/18
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class DebuggerLayoutPanel extends JPanel{

    public DebuggerLayoutPanel() {
    	
    	super();
    	
    	setLayout(new GridBagLayout());
    	GridBagConstraints c;
    	
    	c = new GridBagConstraints();
    	c.fill=GridBagConstraints.BOTH;
    	c.insets = new Insets(5, 5, 5, 5);
    	
    	c.gridwidth = 1;
    	c.gridheight = 1;
    	c.gridx = 0; 
    	c.gridy = 0;
    	c.weightx = .45;
    	c.weighty = .5;
    	add(new DebuggerGraphPanel("Graph 1", 1), c);
    	
    	c.gridx = 1;
    	add(new DebuggerGraphPanel("Graph 2", 2), c);

    	c.gridy = 1;
    	add(new DebuggerGraphPanel("Graph 3", 3), c);
    	
    	c.gridx = 0;
    	add(new DebuggerGraphPanel("Graph 4", 4), c);

    	c.gridx = 2;
    	c.gridy = 0;
    	c.gridheight = 2;
    	c.weightx = .1;
    	c.weighty = 1;
    	add(new ButtonPanel(), c);

    }
    
    
}