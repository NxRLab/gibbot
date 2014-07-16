/**
 * @(#)SampleSwipeTab.java
 *
 *
 * @author Katie
 * @version 1.00 2014/7/1
 */

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

//Panels that can be pulled down by the user to display robot data

public class SampleSwipeTab extends JPanel implements MouseListener, MouseMotionListener {
	
	private String message;
	private boolean waitingForPull;
	private boolean pulling;
	private boolean pulled;
	private final int initialHeight=20;
	private Color bg = Color.WHITE;
	private int width;
	private int height;
	private int totalNumberOfTabs=4;
	private int latchPoint;
	private int mouseAt;
	private Font font = new Font("Serif", Font.BOLD, initialHeight);

    public SampleSwipeTab(int widthOfContainer, int heightOfContainer, String s) {
    	waitingForPull=true;
    	pulling=false;
    	pulled=false;
    	width=(int)(widthOfContainer/totalNumberOfTabs)-20;
    	height=(int)(heightOfContainer/3)-20;
    	message=s;
    	setPreferredSize(new Dimension(width, height));
    	setBackground(bg);
    	setFont(font);
    	addMouseListener(this);
    	addMouseMotionListener(this);
    }
    
    public SampleSwipeTab(int widthOfContainer, int heightOfContainer) {
    	waitingForPull=true;
    	pulling=false;
    	pulled=false;
    	width=(int)(widthOfContainer/totalNumberOfTabs)-20;
    	height=(int)(heightOfContainer/3)-20;
    	message="Pull down";
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
    		g.fillRect(1, 1, width-1, initialHeight+(mouseAt-latchPoint));
    	}
    	
    		else{
    			if(pulled){			//Tab has been pulled down; stays where it is with a propmt to return it to the top.
    			g.fillRect(1, 1, width-1, height-1);
    			g.setColor(Color.BLACK);
    			g.drawString("Click to hide", 10, height-3);
    				
    			/*drawDataContent*/
    			}}
    	}
    		
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
    	
    	if(y>=height){
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
    		
    	if(y<height){
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
    
    public Font getFont(){
    	return font;
    }
}
    
    
    
    
