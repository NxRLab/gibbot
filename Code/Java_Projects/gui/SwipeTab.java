/**
 * @(#)SwipeTab.java
 *
 *
 * @author 
 * @version 1.00 2014/7/10
 */

import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import java.util.*;
import javax.swing.*;
import javax.swing.Timer;

//Panels that can be pulled down by the user to display robot data

public class SwipeTab extends JPanel implements ActionListener, MouseListener, MouseMotionListener {
	
	//vars for drawing
	private String message;
	private int width;
	private int height;
	private final int initialHeight = 20;
	private int totalNumberOfTabs = 1;
	private Color bg = Color.WHITE;
	private Font font = new Font("Serif", Font.BOLD, initialHeight);
	private Timer timer = new Timer(25, this);
	
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
    
    public SwipeTab(int widthOfContainer, int heightOfContainer) {
    	waitingForPull = true;
    	pulling = false;
    	pulled = false;
    	width = (int)(widthOfContainer/totalNumberOfTabs)-20;
    	height = (int)(heightOfContainer/3)-20;
    	message = "Pull down";
    	setPreferredSize(new Dimension(width, height));
    	setBackground(bg);
    	setFont(new Font("Serif", Font.BOLD, initialHeight));
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
    				
    			/*drawDataContent*/
    				 }
    			}
    		}
    	}	
    }
    
    /*MouseListener and MouseMotionListener methods*/
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
    		timer.stop();
    		latchPoint = y;
    		newT = System.currentTimeMillis();
    		floating = false;
    		pulling = true;
    	}
    	
    	if(pulled){ //user clicked to hide
    		pulled = false;
    		floating = true;
    		timer.start();
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
    		timer.start();
    	}
    }
    
    public void actionPerformed(ActionEvent evt){
    	
    	if(newY <= initialHeight){
    		timer.stop();
    		floating = false;
    		waitingForPull = true;
    		repaint();
    		}
    		
    	if(newY >= height){
    		timer.stop();
    		floating = false;
    		pulled = true;
    		repaint();
    		}
    		
    	oldY = newY;
    	acceleration = -15*oldY;  		
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
}