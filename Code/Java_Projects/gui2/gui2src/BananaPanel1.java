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
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;

/*Handles user placement of bananas, animation of robot, and draws metal board background*/

public class BananaPanel1 extends JPanel implements MouseListener, MouseMotionListener, ActionListener {
	
	Banana banana;
	Gibbot bob = new Gibbot();
	boolean interacting = false;
	boolean dragging = false;
	Font f = new Font("Serif", Font.BOLD, 30);
	double slope;
	int dx = 5;
	private Color bg = new Color(255, 204, 255);
	Image boardImg;
	Image bucketImg;
	Image prompt1;
	Image prompt2;
	private int height;
	private int width;
	
	private double timerCount=0; //only for gibbot animation simulation
	
    public BananaPanel1(int widthOfContainer, int heightOfContainer) {
    	width=widthOfContainer-30;
    	height=(int)(heightOfContainer*2/3);
    	setPreferredSize(new Dimension(width, height));
    	setBackground(bg);
    	addMouseListener(this);
    	addMouseMotionListener(this);
    	try {
		boardImg = ImageIO.read(new File("C:\\Users\\K\\Downloads\\sheet_metal.png"));
		bucketImg = ImageIO.read(new File("C:\\Users\\K\\Downloads\\bucket.png"));
		prompt1 = ImageIO.read(new File("C:\\Users\\K\\Downloads\\gibbot_prompt.png"));
		prompt2 = ImageIO.read(new File("C:\\Users\\K\\Downloads\\banana_prompt.png"));
		}
	catch(IOException e){
		System.out.println("not found");
		}
		
    }
    
    public void paintComponent(Graphics g) {
    	
    	super.paintComponent(g);
    	
    	Graphics2D g2d = (Graphics2D)g;
    	
    	/*for non proportional board in GUI*/
    	g2d.drawImage(boardImg, 1, 1, getWidth()-1, getHeight()-1, this);
    	g2d.drawImage(bucketImg, (int)(getWidth()-1.6*(getHeight()/3)), 2*(int)(getHeight()/3), 
    		(int)(getHeight()/2.7), (int)(getHeight()/2.7), this);
    	
    	g2d.setColor(Color.BLACK);

    	if(!interacting){												//Either nothing has happened or the user is moving the banana
    		if(dragging)
    			g2d.drawImage(banana.getImage(), banana.getX(), banana.getY(), 80, 60, this);												//AKA if the user hasn't clicked on the board yet
    		
    		else{
    			g2d.drawImage(prompt1, (int)bob.getPivotX(), (int)bob.getPivotY()+20, 150, 100, this);
    			g2d.drawImage(prompt2, (int)(getWidth()-1.6*(getHeight()/3))-20, 2*(int)(getHeight()/3)-100, 150, 100, this);
    		}
    		bob.draw(g);
    	}
    	
    	else{															//If the user dropped the banana, this is where we draw call for animation images
        	g2d.drawImage(banana.getImage(), banana.getX(), banana.getY(), 80, 60, this);
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
   		GUITimer.addActionListener(this);
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