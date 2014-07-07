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

public class BananaPanel1 extends JPanel implements MouseListener, ActionListener {
	
	Banana banana;
	Gibbot bob = new Gibbot();
	boolean interacting = false;
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
    }
    
    public void paintComponent(Graphics g) {
    	super.paintComponent(g);
    	
    	g.setColor(Color.LIGHT_GRAY);									//This section draws the metal board
    	g.fillRect(30, 30, getWidth()-60, getHeight()-60);
    	g.setColor(Color.DARK_GRAY);
		g.drawRect(40, 40, getWidth()-80, getHeight()-80);
    	g.drawRect(50, 50, getWidth()-100, getHeight()-100);    	
    	Graphics2D g2d = (Graphics2D)g;
    	g2d.drawImage(board.getImage(), 60, 60, getWidth()-120, getHeight()-120, this);
    	
    	g2d.setColor(Color.BLACK);

    	if(!interacting){												//AKA if the user hasn't clicked on the board yet
    		g2d.setFont(f);
    		g2d.drawString("Click to place the bait!", 0, 25);
    		bob.draw(g);
    		//swipe tab draw methods
    	}
    	else{															//If the user has clicked, this is where we draw call for animation images
        g2d.drawImage(banana.getImage(), banana.getX(), banana.getY(), 60, 60, this);
        bob.draw(g);
        //swipe tab draw methods        
    	}        
    	
    }
    
    public void mouseClicked(MouseEvent evt) {
    	
    	if(!interacting){					//If the panel has been waiting to be clicked on and nothing is happening, this starts the animation in motion.
    										//NOTE: also need some restriction on target coors to keep real robot from falling off board
    		interacting = true;
    		slope = (double)(evt.getY()-bob.getPivotY())/(double)(evt.getX()-bob.getPivotX());    	
    		banana = new Banana();
    		
    		banana.setX(evt.getX());
    		banana.setY(evt.getY());
    		
    		//SERIAL: send goal coordinates to robot
    	
    		repaint();
    		timer.start();
    	}
    	else								//If the user clicks while the animation is going on, nothing happens.
    		return;
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
   public void mousePressed(MouseEvent evt){}
   public void mouseReleased(MouseEvent evt){}
   public void mouseEntered(MouseEvent evt){}
   public void mouseExited(MouseEvent evt){}
    
}