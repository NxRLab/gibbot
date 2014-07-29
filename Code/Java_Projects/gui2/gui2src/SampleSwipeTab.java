/**
 * @(#)SampleSwipeTab.java
 *
 *
 * @author Katie
 * @version 1.00 2014/7/1
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

//Panels that can be pulled down by the user to display robot data

public class SampleSwipeTab extends JPanel implements MouseListener, MouseMotionListener {
	
	private String message;
	private boolean waitingForPull;
	private boolean pulling;
	private boolean pulled;
	private final int initialHeight=24;
	private Color bg = new Color(204, 204, 255);
	private int width;
	private int height;
	private int totalNumberOfTabs=4;
	private int latchPoint;
	private int mouseAt;
	private Polygon triangle;

    public SampleSwipeTab(int correctedWidth, int heightOfContainer, String s) {
    	waitingForPull=true;
    	pulling=false;
    	pulled=false;
    	width = correctedWidth;
    	height=(int)(heightOfContainer/3.25);
    	message=s;
    	setPreferredSize(new Dimension(width, height));
    	setBackground(bg);
    	setFont(ImageHandler.getFont());
    	triangle = new Polygon(new int[]{(int)(width/2)-5, (int)(width/2)+5, (int)(width/2)},
    						   new int[]{48, 48, 51}, 
    							3);
    	addMouseListener(this);
    	addMouseMotionListener(this);
    }
    
    public void paintComponent(Graphics g){
    	super.paintComponent(g);
    	g.setColor(new Color(0, 51, 153));
    	
    	if(waitingForPull){			//Tab is at the top waiting to be pulled; prompter message specified in constructor or default: "Pull down"
    	
    		g.fillPolygon(triangle);
    		
    		FontMetrics fm = g.getFontMetrics();  
    		int stringWidth = fm.stringWidth(message);
			g.drawString(message, (int)((getWidth()-stringWidth)/2), 70);
    		
    		drawTab(initialHeight, g);
    	}
    	
    	else{
    		if(pulling){			//User is in the act of pulling the tab down
    			drawTab(initialHeight+(mouseAt-latchPoint), g);
    		}
    	
    		else{
    			if(pulled){			//Tab has been pulled down; stays where it is with a propmt to return it to the top.
    				drawTab(height-19, g);
    				g.setColor(new Color(207, 46, 46));
    				g.drawString("tap to hide", 10, height-2);
    			}
    		}
    	}
    }
    	
    public void drawTab(int height, Graphics g){
    	
    	Graphics2D g2 = (Graphics2D)g;
    	
    	g2.setColor(new Color(125, 125, 125, 50)); //lightest gray
    	g2.fillRoundRect(7, 7, width - 7, height + 12, 12, 12);
    	
    	g2.setColor(new Color(125, 125, 125, 100)); //light gray
    	g2.fillRoundRect(7, 7, width - 11, height + 8, 12, 12);
        
        g2.setColor(new Color(125, 125, 125, 150)); //middle gray
    	g2.fillRoundRect(7, 7, width - 15, height + 4, 12, 12);
    	
    	g2.setColor(new Color(130, 130, 130, 200)); //dark gray
    	g2.fillRoundRect(7, 7, width - 19, height, 9, 9);
   		
   		g2.setColor(Color.WHITE); //white
    	g2.fillRoundRect(3, 3, width - 19, height, 9, 9);
    	
    	g2.setStroke(new BasicStroke(4));  //yellow
    	//g2.setColor(new Color(255, 255, 0));
    	g2.setColor(new Color(0, 51, 153)); 
    	g2.drawRoundRect(13, 13, width - 39, height-20, 9, 9);
    	
    	g2.setStroke(new BasicStroke(1));
    	
    }
    		
    /*MouseListener and MouseMotionListener methods*/
    public void mousePressed(MouseEvent evt) {
    	
    	int y=evt.getY();
    	
    	if(y<=initialHeight){
    		latchPoint=y;
    		pulling=true;
    		waitingForPull=false;
    	}
    	if(pulled){
    		pulled=false;
    		waitingForPull=true;
    		repaint();
    	}
    	}
    public void mouseDragged(MouseEvent evt) {
    	if(!pulling)
    		return;
    	
    	int y=evt.getY();
    	
    	if(y>=height-16){
    		pulling=false;
    		pulled=true;
    		repaint();
    	}
    	
    	else{
    		mouseAt=y;
    		repaint();
    	}
    		
    	
    	}
    public void mouseReleased(MouseEvent evt) {
    	int y=evt.getY();
    	
    	if(!pulling){
    		if(y<height)
    			waitingForPull=true;	
    		return;
    	}
    		
    	if(y<height-16){
    		pulling=false;
    		waitingForPull=true;
    		repaint();
    	}
    }
    
    public void mouseClicked(MouseEvent evt) {}
    public void mouseEntered(MouseEvent evt) {}
    public void mouseExited(MouseEvent evt) {}
    public void mouseMoved(MouseEvent evt) {}
    
    public int getWidth(){
    	return width;
    }
    
    public int getHeight(){
    	return height;
    }
    
    public boolean getPulled(){
    	return pulled;
    }
}

/*
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import java.util.*;
import javax.swing.*;
import javax.swing.Timer;

//Panels that can be pulled down by the user to display robot data

public class SampleSwipeTab extends JPanel implements ActionListener, MouseListener, MouseMotionListener {
	
	//vars for drawing
	private String message;
	private int width;
	private int height;
	private final int initialHeight = 20;
	private int totalNumberOfTabs = 4;
	private Color bg = Color.WHITE;
	private Font font = new Font("Serif", Font.BOLD, initialHeight);

	//state vars
	private boolean waitingForPull;
	private boolean pulling;
	private boolean pulled;
	private boolean floating;
	
	//vars to handle swiping
	private int latchPoint;
	private int oldY;
	private int newY;
	private long oldT;
	private long newT;
	private double velocity;
	private double acceleration;
    
    public SampleSwipeTab(int widthOfContainer, int heightOfContainer) {
    	waitingForPull = true;
    	pulling = false;
    	pulled = false;
    	width=(int)(widthOfContainer/totalNumberOfTabs)-20;
    	height=(int)(heightOfContainer/3)-20;
    	message = "Pull down";
    	setPreferredSize(new Dimension(width, height));
    	setBackground(bg);
    	setFont(font);
    	addMouseListener(this);
    	addMouseMotionListener(this);
    }
    
    public SampleSwipeTab(int widthOfContainer, int heightOfContainer, String s) {
    	waitingForPull = true;
    	pulling = false;
    	pulled = false;
    	width=(int)(widthOfContainer/totalNumberOfTabs)-20;
    	height=(int)(heightOfContainer/3)-20;
    	message = s;
    	setPreferredSize(new Dimension(width, height));
    	setBackground(bg);
    	setFont(font);
    	addMouseListener(this);
    	addMouseMotionListener(this);
    }
    
    public void paintComponent(Graphics g){
    	super.paintComponent(g);
    	g.setColor(Color.GREEN);
    	if(waitingForPull){			//Tab is at the top waiting to be pulled; prompter message specified in constructor or default: "Pull down"
    		g.fillRect(1, 1, width-1, initialHeight);
    		g.setColor(Color.BLACK);
    		g.drawString(message, 10, initialHeight-3);
    	}
    	
    	else{
    		if(pulling){			//User is in the act of pulling the tab down
    			g.fillRect(1, 1, width-1, initialHeight+(newY-latchPoint));
    		}
    		
    		else{
    			if(floating)		//User let go before tab was pulled down
    				g.fillRect(1, 1, width-1, newY);
    	
    			else{
    				if(pulled){			//Tab has been pulled down; stays where it is with a propmt to return it to the top.
    					g.fillRect(1, 1, width-1, height-1);
    					g.setColor(Color.BLACK);
    					g.drawString("Click to hide", 10, height-3);
    				
    			/*drawDataContent
    				 }
    			}
    		}
    	}	
    }
    
    /*MouseListener and MouseMotionListener methods
    public void mousePressed(MouseEvent evt) {
    	
    	int y = evt.getY();
    	
    	if(y <= initialHeight){ //user grabbed tab from rest
    		latchPoint = y;
    		newY = y;
    		newT = System.currentTimeMillis();
    		pulling = true;
    		waitingForPull = false;
    	}
    	
    	if(floating){  //user grabbed tab from floating
    		GUITimer.removeActionListener(this);
    		latchPoint = y;
    		newT = System.currentTimeMillis();
    		floating = false;
    		pulling = true;
    	}
    	
    	if(pulled){ //user clicked to hide
    		pulled = false;
    		floating = true;
    		GUITimer.addActionListener();
    		repaint();
    	}
    }
    	
    public void mouseDragged(MouseEvent evt) {
    	if(!pulling)
    		return;
    	
    	int y = evt.getY();
    	
    	if(y >= height){  //user pulled the tab all the way to the bottom
    		pulling = false;
    		pulled = true;
    		repaint();
    	}
    	
    	else{  //still dragging
    		oldY = newY;
    		newY = y;
    		oldT = newT;
    		newT = System.currentTimeMillis();
    		velocity = (double)(newY-oldY)/(newT-oldT);
    		repaint();
    	}
    		
    	
    	}
    public void mouseReleased(MouseEvent evt) {
    	int y = evt.getY();
    	
    	if(!pulling){
    		if(y < height) //user just clicked and released below the waiting tab
    			waitingForPull = true;	
    		return;
    	}
    	
    	
    		
    	if(y < height){   //user let go before pulling the tab all the way down
    		pulling = false;
    		floating = true;
    		newY = initialHeight+(newY-latchPoint);
    		GUITimer.addActionListener();
    	}
    }
    
    public void actionPerformed(ActionEvent evt){
    	
    	if(newY <= initialHeight){
    		GUITimer.removeActionListener(this);
    		floating = false;
    		waitingForPull = true;
    		repaint();
    		}
    		
    	oldY = newY;
    	acceleration = -50*oldY;  		
    	newY = (int)(.5*acceleration*Math.pow(.025,2)+velocity*.025+oldY);
    	velocity = velocity + acceleration*.025;
    	
    	repaint();
    	
    }
    
    public void mouseClicked(MouseEvent evt) {}
    public void mouseEntered(MouseEvent evt) {}
    public void mouseExited(MouseEvent evt) {}
    public void mouseMoved(MouseEvent evt) {}
    
    public int getWidth(){
    	return width;
    }
    
    public int getHeight(){
    	return height;
    }
    
    public boolean getPulled(){
    	return pulled;
    }
    
    public Font getFont(){
    	return font;
    }
}*/
    
    
    
    
