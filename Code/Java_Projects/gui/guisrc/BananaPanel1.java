/**
 * @(#)BananaPanel1.java
 *
 *
 * @author 
 * @version 1.00 2014/6/30
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;

/*Handles user placement of bananas, animation of robot, and draws metal board background*/

public class BananaPanel1 extends JPanel implements MouseListener, MouseMotionListener, ActionListener {
	
	Banana banana;
	Gibbot bob = new Gibbot();
	boolean interacting = false;
	boolean dragging = false;
	Font f = new Font("Serif", Font.BOLD, 30);
	Timer timer = new Timer(40, this);
	double slope;
	int dx = 5;
	MetalTexture board = new MetalTexture();
	private int height;
	private int width;
	private double timerCount=0;
	
    public BananaPanel1(int widthOfContainer, int heightOfContainer) {
    	width=widthOfContainer-30;
    	height=(int)(heightOfContainer*2/3)-70;
    	setPreferredSize(new Dimension(width, height));
    	this.setBackground(Color.WHITE);
    	this.addMouseListener(this);
    	this.addMouseMotionListener(this);
    }
    
    public void paintComponent(Graphics g) {
    	super.paintComponent(g);
    	
    	g.setColor(Color.LIGHT_GRAY);									//This section draws the metal board
    	g.fillRect(30, 30, getWidth()-60, getHeight()-60);
    	g.setColor(Color.DARK_GRAY);
		g.drawRect(40, 40, getWidth()-80, getHeight()-80);
    	g.drawRect(50, 50, getWidth()-100, getHeight()-100);    	
    	Graphics2D g2d = (Graphics2D)g;
    	g2d.setFont(f);
    	g2d.drawImage(board.getImage(), 60, 60, getWidth()-120, getHeight()-120, this);
    	
    	g2d.setColor(Color.RED);
    	g2d.fillRect((int)(.91*getWidth())-105, (int)(.75*getHeight())-15, (int)(.09*getWidth()), (int)(.25*getHeight()));
    	g2d.setColor(Color.BLACK);
    	g2d.drawString("Bananas", (int)(.91*getWidth())-95, (int)(.75*getHeight())+20);
    	
    	g2d.setColor(Color.BLACK);

    	if(!interacting){												//Either nothing has happened or the user is moving the banana
    		if(dragging)
    			g2d.drawImage(banana.getImage(), banana.getX(), banana.getY(), 60, 60, this);												//AKA if the user hasn't clicked on the board yet
    		
    		g2d.drawString("Click and drag to place the bait!", 0, 25);
    		bob.draw(g);
    	}
    	
    	else{															//If the user dropped the banana, this is where we draw call for animation images
        	g2d.drawImage(banana.getImage(), banana.getX(), banana.getY(), 60, 60, this);
        	bob.draw(g);    
    	}        
    	
    }
    
    public void mousePressed(MouseEvent evt) {
    	
    	if(interacting)						//If the user clicks while the animation is going on, nothing happens.
    		return;
    	
    	int x = evt.getX();
    	int y = evt.getY();
    	
    	if((int)((.91*getWidth())-105)<x && x<(getWidth()-105) && (.75*getHeight()-15)<y && y<(getHeight()-15)){
    	
    		if(!dragging){					//If the panel has been waiting to be clicked on and nothing is happening, this draws a banana to be moved around.
    										
    			dragging = true;   	
				banana = new Banana();
    		
    			banana.setX(x);
    			banana.setY(y);
    	
    			repaint();
    		
    	}
   	}
   	
    	else								
    		return;
  }
   
   public void mouseDragged(MouseEvent evt){
   	
   	int x = evt.getX();
    int y = evt.getY();
   	
   	if(dragging){
   		banana.setX(x);
    	banana.setY(y);
    	
    	repaint();
   		
   	}
   	
   	
   }
   
   public void mouseExited(MouseEvent evt){
   	
   	if(dragging){
   		dragging = false;
   		repaint();
   	}
   	}
   
   public void mouseReleased(MouseEvent evt){
   	if(dragging){								//NOTE: also need some restriction on target coors to keep real robot from falling off board
   		dragging = false;
   		interacting = true;
   		timer.start();
   	}
   		
   }
   
   public void actionPerformed(ActionEvent evt){//Handles events from the timer
											
   		if((int)bob.getPivotX()<= banana.getX()){        //If the robot is not to the bananas yet	
   			bob.arcMotionUpdate(timerCount);
   			//SERIAL: above method will be replaced by getting coordinates of the three "clusters" from python code, sending it to updateRealCoors method
   			
   			//SERIAL: above method will be replaced getting info on each swipe tab, sending it to updateForDrawing method
   			repaint();
   			timerCount++;
   		}
   		
   		else{               						//When the robot reaches the bananas, the panel resets itself.            
   			timer.stop();
   			interacting = false;
   			timerCount=0;
   			bob.reset();
   			repaint();
   		}
   		
   		
   }
   /*Required methods for MouseListener interface*/
   public void mouseClicked(MouseEvent evt){}
   public void mouseEntered(MouseEvent evt){}
   public void mouseMoved(MouseEvent evt){}
    
}