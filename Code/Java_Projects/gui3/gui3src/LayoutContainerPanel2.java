/**
 * @(#)LayoutContainerPanel2.java
 *
 *
 * @author 
 * @version 1.00 2014/8/1
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*This is the "asleep" view of the GUI. The gibbotTab images contain "public-friendly" 
 *descriptions of how the robot works. The ChargingBox instance shows a battery icon
 *to show charging status.
 */

public class LayoutContainerPanel2 extends JPanel implements MouseListener, MouseMotionListener {

	private Image batteryArrow = ImageHandler.getImage("batteryArrow");
	private Image gibbotTab1 = ImageHandler.getImage("gibbotTab1");
	private Image gibbotTab2 = ImageHandler.getImage("gibbotTab2");
	private Image gibbotTab3 = ImageHandler.getImage("gibbotTab3");
	private Image sleepBubble = ImageHandler.getImage("sleepBubble");
	
	private int height;
	private int width;
	
	private boolean pulled1;
	private boolean pulled2;
	private boolean pulling1;
	private boolean pulling2;
	private boolean allowDragging;
	
	private int mouseAt;
	private int offset;
	
	private ChargingBox charge;
	GridBagConstraints c;

    public LayoutContainerPanel2(int widthOfContainer, int heightOfContainer) {

    	setLayout(null);
    	height=heightOfContainer-1;
    	width=widthOfContainer-1;
  
    	charge = new ChargingBox();
    	charge.setOpaque(false);
    	charge.setBounds(975, 5, 250, 350);
    	add(charge);
    	
    	addMouseListener(this);
    	addMouseMotionListener(this);
    	
    	pulled1 = false;
    	pulled2 = false;
    	pulling1 = false;
    	pulling2 = false;
    	allowDragging = false;
    }
    
    public void paintComponent(Graphics g){

    	g.setColor(new Color(125, 125, 125, 180));
    	g.fillRect(0, 0, getWidth(), getHeight());
    	g.drawImage(sleepBubble, 0, 0, this);
    	g.drawImage(batteryArrow, 750, 10, this);
    	g.setColor(Color.WHITE);
    	g.drawImage(gibbotTab3, (int)(getVisibleRect().getWidth()) - gibbotTab3.getWidth(this), 
    			sleepBubble.getHeight(this), this);
    			
    	if(!pulled2 && !pulling2)
    		g.drawImage(gibbotTab2, (int)(getVisibleRect().getWidth()) - gibbotTab2.getWidth(this) + 10, 
    			sleepBubble.getHeight(this) - 30, this); //10 and -30 to account for invisible margins on the images
    	else {
    		if(pulling2){
    			g.drawImage(gibbotTab2, mouseAt - offset, 
    				sleepBubble.getHeight(this) - 30, this); //160 and -180 to account for invisible margins on the image
    		}
    		else{
    			g.drawImage(gibbotTab2, (int)(getVisibleRect().getWidth()) - 120, 
    				sleepBubble.getHeight(this) - 30, this);
    		}
    	}
    	
    	if(!pulled1 && !pulling1)
    		g.drawImage(gibbotTab1, (int)(getVisibleRect().getWidth()) - gibbotTab1.getWidth(this) + 160, 
    			sleepBubble.getHeight(this) - 180, this); //160 and -180 to account for invisible margins on the images
    	else {
    		if(pulling1){
    			g.drawImage(gibbotTab1, mouseAt - offset, 
    				sleepBubble.getHeight(this) - 180, this); //160 and -180 to account for invisible margins on the image
    		}
    		else{
    			g.drawImage(gibbotTab1, (int)(getVisibleRect().getWidth()) - 80, 
    				sleepBubble.getHeight(this) - 180, this);
    		}
    	}
    }
    
    public void resetTabs(){
    	pulled1 = false;
    	pulled2 = false;
    	pulling1 = false;
    	pulling2 = false;
    }
    
    public void mousePressed(MouseEvent evt){
    	
    	int x = evt.getX();
    	int y = evt.getY();
    	
    	if((!pulled1 && !pulled2) || (!pulled1 && pulled2)){ //if top tab is not pulled, the user may only pull open the top tab
    		if (x > 190 && y > 355 && y < 675){
    			pulling1 = true;
    			mouseAt = x;
    			offset = mouseAt - ((int)(getVisibleRect().getWidth()) - gibbotTab1.getWidth(this) + 160);
    		}
    	}
    	
    	if(pulled1 && !pulled2){ //either the user can pull the top tab closed again or pull the second tab open
    		if(x > 150 && x < 1320 && y > 355 && y < 675){
    			pulling2 = true;
    			mouseAt = x;
    			offset = mouseAt - ((int)(getVisibleRect().getWidth()) - gibbotTab2.getWidth(this) + 10);
    		}
    		else{
    			if (x > 1330 && y > 355 && y < 675){
    				pulled1 = false;
    				pulling1 = true;
    				mouseAt = x;
    				offset = mouseAt - ((int)(getVisibleRect().getWidth()) - 80);
    				allowDragging = true;
    			}
    		}
    	}
    	
    	if(pulled1 && pulled2){ //the user may pull either tab closed
    		if(x > 1290 && x < 1330 && y > 355 && y < 675){
    			pulled2 = false;
    			pulling2 = true;
    			mouseAt = x;
    			offset = mouseAt - ((int)(getVisibleRect().getWidth()) - 120);
    		}
    		else{
    			if (x > 1330 && y > 355 && y < 675){
    				System.out.println("pulling1");
    				pulled1 = false;
    				pulling1 = true;
    				mouseAt = x;
    				offset = mouseAt - ((int)(getVisibleRect().getWidth()) - 80);
    				allowDragging = true;
    			}	
    		}
    	}
    }
    
    public void mouseDragged(MouseEvent evt){
    	
    	int x = evt.getX();
    	int y = evt.getY();
    	
    	if(pulling1){
    		if(x < 180){
    			pulling1 = false;
    			pulled1 = false;
    		}
    		else{
    			if(x > 1330){
    				if(allowDragging)
    					mouseAt = x;
    				else{
    					pulling1 = false;
    					pulled1 = true;
    				}
    			}
    			else{
    				if(mouseAt < 1330)
    					allowDragging = false;
    				mouseAt = x;
    			}
    		}	
    	}
    	else{
    		if(pulling2){
    			if(x < 140){
	    			pulling2 = false;
    				pulled2 = false;
    			}
    			else{
	    			if(x > 1320){
    					pulling2 = false;
    					pulled2 = true;
    				}
    				else{
    					mouseAt = x;
    				}
    			}	
    		}
    	}
    	
    	repaint();
    }
    
    public void mouseReleased(MouseEvent evt){
    	
    	int x = evt.getX();
    	int y = evt.getY();
    	
    	if(pulling1){
    		pulling1 = false;
    		repaint();
    	}
    	else{
    		if(pulling2){
    			pulling2 = false;
    			repaint();
    		}
    	}
    			
    }
    	
    public void mouseClicked(MouseEvent evt){}
    public void mouseEntered(MouseEvent evt){}
    public void mouseExited(MouseEvent evt){}
    public void mouseMoved(MouseEvent evt){}
    
    
}