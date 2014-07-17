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
    	height=heightOfContainer-1;
    	width=widthOfContainer-1;
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
    	c.weighty = .66;
    	c.fill=GridBagConstraints.BOTH;
    	add(bananapan,c);
    	
    	//SampleSwipeTab swipe0 = new SampleSwipeTab(width, height, "Torque");
    	
    	SampleSwipeTab swipe1 = new SampleSwipeTab(width, height, "Torque");
   		//GridBagConstraints c = new GridBagConstraints();
    	c.gridx=0;
    	c.gridy=0;
    	c.gridwidth=1;
    	c.gridheight=1;
    	c.weightx=.25;
    	c.weighty=.33;
    	//c.anchor=GridBagConstraints.LINE_START;
    	add(swipe1, c);
    	
    	SampleSwipeTab swipe2 = new SampleSwipeTab(width, height, "Battery");
    	//GridBagConstraints c = new GridBagConstraints();
    	c.gridx=1;
    	c.gridy=0;
    	add(swipe2, c);
    	
    	AngleSwipeTab angle = new AngleSwipeTab(width, height, "Angle");
    	c.gridx=2;
    	c.gridy=0;
    	add(angle, c);
    	
    	CurrentSwipeTab current = new CurrentSwipeTab(width, height, "Current");
    	c.gridx=3;
    	c.gridy=0;
    	add(current, c);
    	
    }
    
    
}