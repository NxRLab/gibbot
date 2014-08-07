/**
 * @(#)LayoutContainerPanel.java
 *
 *
 * @author 
 * @version 1.00 2014/7/1
 */

import javax.swing.*;
import java.awt.*;

/*This is the "awake" view of the GUI. Basically just handles layout for
 *all subpanels in that view: BananaPanel1, TextBox, Speedometer, HardwareBox,
 *and CurrentBox instances.
 */

public class LayoutContainerPanel extends JPanel{
	
	private int height;
	private int width;
	
	private Color bg = new Color(204, 204, 255);
	public BananaPanel1 bananapan; //this is declared public for access by GUILayeredPane for enabling/disabling
	GridBagConstraints c;


    public LayoutContainerPanel(int widthOfContainer, int heightOfContainer) {
    	
    	setBackground(bg);
    	setLayout(new GridBagLayout());
    	height=heightOfContainer-1;
    	width=widthOfContainer-1;
    	
    	bananapan = new BananaPanel1(width, height);
    	c = new GridBagConstraints();
    	c.gridx=0;
    	c.gridy=0;
    	c.gridwidth=4;
    	c.gridheight=1;
    	c.weighty = .55;
    	c.weightx = 1;
    	c.fill=GridBagConstraints.BOTH;
    	add(bananapan,c);
    	
    	c.weighty = .3;
    	c.gridwidth = 1;
    	c.anchor = GridBagConstraints.SOUTH;
    	
    	TextBox text = new TextBox(width, height);
    	c.gridx = 0;
    	c.gridy = 1;
    	c.weightx = .25;
    	add(text, c);
    	
    	Speedometer speed = new Speedometer(width, height);
    	c.gridx = 1;
    	c.gridy = 1;
    	c.weightx = .33;
    	add(speed, c);
    	
    	HardwareBox hardware = new HardwareBox(width, height);
    	c.gridx = 2;
    	c.gridy = 1;
    	c.weightx = .16;
    	add(hardware, c);
    	
    	CurrentBox current = new CurrentBox(width, height);
    	c.gridx = 3;
    	c.gridy = 1;
    	c.weightx = .25;
    	add(current, c);
    }
    
    public void paintComponent(Graphics g) {

    		super.paintComponent(g);
    }
    
}

