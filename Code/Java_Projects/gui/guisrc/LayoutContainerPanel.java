/**
 * @(#)LayoutContainerPanel.java
 *
 *
 * @author 
 * @version 1.00 2014/7/1
 */

import javax.swing.*;
import java.awt.*;

public class LayoutContainerPanel extends JPanel {
	
	private int height;
	private int width;

    public LayoutContainerPanel(int widthOfContainer, int heightOfContainer) {
    	setBackground(Color.WHITE);
    	setOpaque(true);
    	setLayout(new GridBagLayout());
    	height=heightOfContainer-80;
    	width=widthOfContainer-45;
    	setPreferredSize(new Dimension(width, height));
    }
    
    public void paintComponent(Graphics g) {
    	super.paintComponent(g);
    	BananaPanel1 bananapan = new BananaPanel1(width, height);
    	GridBagConstraints c = new GridBagConstraints();
    	c.gridx=0;
    	c.gridy=1;
    	c.gridwidth=4;
    	c.gridheight=1;
    	c.weighty = .75;
    	c.fill=GridBagConstraints.BOTH;
    	add(bananapan,c);
    	
    	SampleSwipeTab swipe;
    	
    	AngleSwipeTab angle = new AngleSwipeTab(width, height, "Angle");
    	GridBagConstraints c2 = new GridBagConstraints();
    	c2.gridx=0;
    	c2.gridy=0;
    	c2.weightx=.25;
    	c2.weighty=.33;
    	c2.anchor=GridBagConstraints.PAGE_START;
    	add(angle, c2);
    	
    	swipe = new SampleSwipeTab(width, height, "Torque");
    	c2.gridx=1;
    	c2.gridy=0;
    	c2.weightx=.25;
    	c2.weighty=.33;
    	c2.anchor=GridBagConstraints.PAGE_START;
    	add(swipe, c2);
    	
    	swipe = new SampleSwipeTab(width, height, "Battery");
    	c2.gridx=2;
    	c2.gridy=0;
    	c2.weightx=.25;
    	c2.weighty=.33;
    	c2.anchor=GridBagConstraints.PAGE_START;
    	add(swipe, c2);
    	
    	//swipe = new SampleSwipeTab(width, height, "Calculations");
    	CurrentSwipeTab current = new CurrentSwipeTab(width, height, "Current");
    	c2.gridx=3;
    	c2.gridy=0;
    	c2.weightx=.25;
    	c2.weighty=.33;
    	c2.anchor=GridBagConstraints.PAGE_START;
    	add(current, c2);
    }
    
    
}