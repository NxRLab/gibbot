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
	
	private Image bananaBubble = ImageHandler.getImage("bananaBubble");
	private Image board = ImageHandler.getImage("board");
	private Image bunch = ImageHandler.getImage("bunch");
	private Image gibbotBubble = ImageHandler.getImage("gibbotBubble");
	private Font andaleBig = ImageHandler.getFont().deriveFont(Font.BOLD, 64);
	
	private int height;
	private int width;
	
	private final int XBOUND = 30; //board image has upper left corner at (20, 10) with width 1285 and height 450
	private final int YBOUND = 30;
	
	private boolean interacting;
	private boolean dragging;
	private boolean outOfBounds;
	
	private Banana banana = new Banana();
	private Gibbot bob = new Gibbot();
	private double timerCount; //only for gibbot animation simulation
	
	private Color promptHighlight;
	private int a; //alpha (opacity) val of promptHightlight
	
    public BananaPanel1(int widthOfContainer, int heightOfContainer) {
    	
    	width = widthOfContainer-30;
    	height = heightOfContainer*2/3;
    	setPreferredSize(new Dimension(width, height));
    	interacting = false;
    	dragging = false;
    	outOfBounds = false;
    	timerCount = 0;
    	setBackground(GibbotGUI3.globalBg);
    	setFont(andaleBig);
    	a = 0;
    	promptHighlight = new Color(207, 46, 46, a);
    	addMouseListener(this);
    	addMouseMotionListener(this);
    	GUITimer.addActionListener(this);
		
    }
    
    public void paintComponent(Graphics g) {
    	
    	super.paintComponent(g);
    	
    	g.drawImage(board, 1, 1, getWidth()-1, getHeight()-1, this);
    	g.setColor(Color.BLACK);

    	if(!interacting){	//Either nothing has happened or the user is moving the banana
    		if(dragging){ 	//user is moving the banana
    			g.drawImage(banana.getImage(), banana.getX(), banana.getY(), 80, 60, this);
    			if(outOfBounds){
    				g.setColor(new Color(255, 0, 0, 150));
    				g.fillRect(56, 37, 1222, 400);
    				g.setColor(Color.BLACK);
    				g.drawString("Out of Bounds!", 400, 240);
    			}
    		}	
    		
    		else{ //nothing has happened
    			g.drawImage(gibbotBubble, (int)bob.getPivotX() - 30, (int)bob.getPivotY()+20, this);
    			g.setColor(promptHighlight);
    			g.fillRoundRect(getWidth() - getHeight() + 3, getHeight()/10 + 3, 
    				bananaBubble.getWidth(this) - 42, bananaBubble.getHeight(this) - 16, 15, 15);
    			g.fillPolygon(new int[]{getWidth() - getHeight() + bananaBubble.getWidth(this) - 39, //x-coors
    									getWidth() - getHeight() + bananaBubble.getWidth(this) - 39,
    									getWidth() - getHeight() + bananaBubble.getWidth(this) - 13}, 
    						  new int[]{getHeight()/10 + 13, //y-coors
    						  			getHeight()/10 + 89,
    						  			getHeight()/10 + 49}, 
    						  3); //# of pts
    			g.drawImage(bananaBubble, getWidth()-getHeight(), getHeight()/10, this);
    		}
    		g.setColor(Color.BLACK);
    		bob.draw(g);
    	}
    	
    	else{		//If the user dropped the banana, this is where we call draw for animation images
        	g.drawImage(banana.getImage(), banana.getX(), banana.getY(), 80, 60, this);
        	bob.draw(g);    
    	}
    	
    	g.drawImage(bunch, (int)(getWidth() - (getHeight()/1.8)), -30, (int)(getHeight()/1.7), (int)(getHeight()/1.7), this);        
    	
    }
    
    public void mousePressed(MouseEvent evt) {
    	
    	if(interacting)	//If the user clicks while the animation is going on, nothing happens.
    		return;
    	
    	int x = evt.getX();
    	int y = evt.getY();
    	
    	System.out.println(x + " " + y);

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
    		if(x < 20 + XBOUND || x > 1305 - XBOUND || y < 10 + YBOUND || y > 460 - YBOUND)
    			outOfBounds = true;
    		else
    			outOfBounds = false;
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
	   		if(outOfBounds){
	   			dragging = false;
	   			repaint();
	   		}
	   		else{
	   			dragging = false;
   				interacting = true;
   				//GUISerialPort.sendGoalCoors(evt.getX(), evt.getY());
	   		}
   		}	
   }
   
   public void actionPerformed(ActionEvent evt){   //Handles events from the timer. Only needed for gibbot animation simulation
											
   		if(interacting && (int)bob.getPivotX() <= banana.getX()){  //If the robot is not to the bananas yet	
   			bob.arcMotionUpdate(timerCount);
   				//SERIAL: above call will be replaced by getting coordinates of the three "clusters" from python code, 
   				//sending it to updateRealCoors method
   			timerCount++;
   		}
   		
   		else{
   			if(interacting){ 	//When the robot reaches the bananas, the panel resets itself.            
	   			interacting = false;
   				timerCount=0;
   				bob.reset();
   			}
	
   			if(a > -255){ //for pulsing outline around bananaBubble image 
   				promptHighlight = new Color(255, 0, 0, Math.abs(a));
   				a -= 7;
   			}
   			else{
   				a = 255;
   				promptHighlight = new Color(255, 0, 0, a);
   			}
   		}		
   			
   		repaint();
   }
   /*Required methods for MouseListener interface*/
   public void mouseClicked(MouseEvent evt){}
   public void mouseEntered(MouseEvent evt){}
   public void mouseMoved(MouseEvent evt){}
    
}