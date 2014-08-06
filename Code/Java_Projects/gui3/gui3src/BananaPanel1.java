/**
 * @(#)BananaPanel1.java
 *
 *
 * @author 
 * @version 1.00 2014/6/30
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*Handles user placement of bananas, animation of robot, and draws metal board background.
 *Note: once process is implemented to get camera data, ActionListener implementation, 
 *actionPerformed() method, timerCount variable will no longer be needed in this class.
 */
 

public class BananaPanel1 extends JPanel implements MouseListener, MouseMotionListener, ActionListener {
	
	Image bananaBubble = ImageHandler.getImage("bananaBubble");
	Image board = ImageHandler.getImage("board");
	Image bunch = ImageHandler.getImage("bunch");
	Image gibbotBubble = ImageHandler.getImage("gibbotBubble");
	
	private int height;
	private int width;
	
	private boolean interacting = false;
	private boolean dragging = false;
	
	private Banana banana = new Banana();
	private Gibbot bob = new Gibbot();
	private double timerCount=0; //only for gibbot animation simulation
	
	private Color bg = new Color(204, 204, 255);
	
    public BananaPanel1(int widthOfContainer, int heightOfContainer) {
    	
    	width = widthOfContainer-30;
    	height = heightOfContainer*2/3;
    	setPreferredSize(new Dimension(width, height));
    	setBackground(bg);
    	addMouseListener(this);
    	addMouseMotionListener(this);
		
    }
    
    public void paintComponent(Graphics g) {
    	
    	super.paintComponent(g);
    	
    	g.drawImage(board, 1, 1, getWidth()-1, getHeight()-1, this);
    	g.drawImage(bunch, (int)(getWidth() - (getHeight()/1.8)), -30, (int)(getHeight()/1.7), (int)(getHeight()/1.7), this);
    	g.setColor(Color.BLACK);

    	if(!interacting){		//Either nothing has happened or the user is moving the banana
    		if(dragging)
    			g.drawImage(banana.getImage(), banana.getX(), banana.getY(), 80, 60, this);	
    		
    		else{
    			g.drawImage(gibbotBubble, (int)bob.getArmX(), (int)bob.getPivotY()+20, 165, 110, this);
    			g.drawImage(bananaBubble, (int)(getWidth()-(getHeight()/1.2)), (int)(getHeight()/10), 165, 91, this);
    		}
    		bob.draw(g);
    	}
    	
    	else{		//If the user dropped the banana, this is where we draw call for animation images
        	g.drawImage(banana.getImage(), banana.getX(), banana.getY(), 80, 60, this);
        	bob.draw(g);    
    	}        
    	
    }
    
    public void mousePressed(MouseEvent evt) {
    	
    	if(interacting)	//If the user clicks while the animation is going on, nothing happens.
    		return;
    	
    	int x = evt.getX();
    	int y = evt.getY();
    	
    	if((x - (getWidth() - getHeight()/1.8) > 70) && (y < getHeight()/1.7 - 70)){ //clicked in the right place to start dragging banana
    	
    		if(!dragging){		//If the panel has been waiting to be clicked on and nothing is happening, 
    							//this draws a banana to be moved around. 										
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
   		
   		if(dragging){		//NOTE: also need some restriction on target coors to keep real robot from falling off board
	   		dragging = false;
   			interacting = true;
   			GUITimer.addActionListener(this);
   			//GUISerialPort.sendGoalCoors(evt.getX(), evt.getY());
   		}	
   }
   
   public void actionPerformed(ActionEvent evt){   //Handles events from the timer. Only needed for gibbot animation simulation
											
   		if((int)bob.getPivotX()<= banana.getX()){  //If the robot is not to the bananas yet	
   			bob.arcMotionUpdate(timerCount);
   			//SERIAL: above method will be replaced by getting coordinates of the three "clusters" from python code, sending it to updateRealCoors method
   			
   			//SERIAL: above method will be replaced getting info on each swipe tab, sending it to updateForDrawing method
   			repaint();
   			timerCount++;
   		}
   		
   		else{ 	//When the robot reaches the bananas, the panel resets itself.            
   			GUITimer.removeActionListener(this);
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