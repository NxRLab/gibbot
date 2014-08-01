/**
 * @(#)LongTab.java
 *
 *
 * @author 
 * @version 1.00 2014/7/31
 */

import java.awt.*;
import javax.swing.*;
import java.io.*;
import java.util.*;
import javax.imageio.*;

public class LongTab extends JPanel {
	
	Image img;

    public LongTab(int widthOfContainer, int heightOfContainer) {
    	setPreferredSize(new Dimension(widthOfContainer, heightOfContainer));
    	try {
    			img = ImageIO.read(new File("paneltest.png"));
			}
			catch(IOException e){
				System.out.println(e);
			}
    }
    
    public void paintComponent(Graphics g){
    	super.paintComponent(g);
    	g.drawImage(img, 0, 0, getWidth(), getHeight(), this);
    	
    }
    
    
}