/**
 * @(#)LayoutContainerPanel.java
 *
 *
 * @author 
 * @version 1.00 2014/7/1
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class LayoutContainerPanel extends JPanel implements ActionListener {
	
	private int height;
	private int width;
	private Color bg = new Color(204, 204, 255);
	
	private int timerCount = 0;
	private int factor = GUITimer.getSerialFactor();

    public LayoutContainerPanel(int widthOfContainer, int heightOfContainer) {
    	setBackground(bg);
    	setOpaque(true);
    	setLayout(new GridBagLayout());
    	height=heightOfContainer-1;
    	width=widthOfContainer-1;
    	setPreferredSize(new Dimension(width, height));
    	GUITimer.addActionListener(this);
    }
    
    public void paintComponent(Graphics g) {
    	
    	super.paintComponent(g);
    	
    	BananaPanel1 bananapan = new BananaPanel1(width, height);
    	GridBagConstraints c = new GridBagConstraints();
    	c.gridx=0;
    	c.gridy=1;
    	c.gridwidth=4;
    	c.gridheight=1;
    	c.weighty = .55;
    	c.fill=GridBagConstraints.BOTH;
    	add(bananapan,c);
    	

    	AngleSwipeTab angle = new AngleSwipeTab(width, height, "serial input: rotations");
    	c.gridx=0;
    	c.gridy=0;
    	c.gridwidth=1;
    	c.gridheight=1;
    	c.weightx=.33;
    	c.weighty=.3;
    	add(angle, c);
    	
    	CurrentSwipeTab current = new CurrentSwipeTab(width, height, "motor data");
    	c.gridx=1;
    	c.gridy=0;
    	c.weightx = .25;
    	add(current, c);
    	
    	HardwareSwipeTab hardware = new HardwareSwipeTab(width, height, "hardware stats");
    	c.gridx=2;
    	c.gridy=0;
    	c.weightx = .16;
    	add(hardware, c);
    	
    	AccelSwipeTab accel = new AccelSwipeTab(width, height, "accelerometer");
    	c.gridx=3;
    	c.gridy=0;
    	c.weightx = .25;
    	add(accel, c);
    	
    }
    
      public void actionPerformed(ActionEvent evt){
      	
      	if(timerCount % factor == (factor - 1)){
    		GUISerialPort.update();
    		timerCount = 0;
      	}
      	
      	else
      		timerCount++;
    }
    
    
}