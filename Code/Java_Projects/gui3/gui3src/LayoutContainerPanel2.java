
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**This is the "asleep" view of the GUI. The gibbotTab images contain "public-friendly" 
 *descriptions of how the robot works. Only subpanel is a {@link ChargingBox} instance.
 */
public class LayoutContainerPanel2 extends JPanel implements MouseListener, MouseMotionListener {

	private Image batteryArrow = ImageHandler.getImage("batteryArrow");
	private Image gibbotTab1 = ImageHandler.getImage("gibbotTab1");
	private Image gibbotTab2 = ImageHandler.getImage("gibbotTab2");
	private Image gibbotTab3 = ImageHandler.getImage("gibbotTab3");
	private Image sleepBubble = ImageHandler.getImage("sleepBubble");
	
	/**Specified by GUILayeredPane parent. Used to determine anchor locations for pull tabs.*/
	private int sizingWidth;
	
	/**True if top pull tab is pulled open (not visible)*/
	private boolean pulled1;
	/**True if middle pull tab is pulled open (not visible)*/
	private boolean pulled2;
	/**True if top pull tab is being pulled by user*/
	private boolean pulling1;
	/**True if top pull tab is being pulled by user*/	
	private boolean pulling2;
	/**True if top tab is pulled open (not visible).
	 *Allows user to pull top tab closed, since mouse-handling methods don't allow 
	 *dragging past a certain point - to keep the end of the tab visible.*/
	private boolean allowDragging;
	
	/**X-coordinate of where the user grabs a tab to move it*/
	private int mouseAt;
	/**Difference between left-most edge of the tab image and mouseAt*/
	private int offset;
	
	/**Shows battery status*/
	private ChargingBox charge;

	/**Constructor adds an instance of {@link ChargingBox} and initializes all boolean state variables to false
	 *@param sizeW Used to set {@link #sizingWidth}*/
    public LayoutContainerPanel2(int sizeW) {
    	
    	sizingWidth = sizeW;

    	setLayout(null);
  
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
    
    /**Override of {@link javax.swing.JComponent#paintComponent}. super.paintComponent() call fills background color.
     *Draws everything. This is what is executed whenever repaint() is called in the program. 
     *First fills entire space with a transparent gray background, then draws images.
     *Uses boolean state variables to determine how to draw the gibbotTab images. 
     *@param g Graphics context for drawing. Kind of a black box; gets handled in the background somehow
     * */  	
    public void paintComponent(Graphics g){

    	g.setColor(new Color(125, 125, 125, 180));
    	g.fillRect(0, 0, getWidth(), getHeight());
    	g.drawImage(sleepBubble, 0, 0, this);
    	g.drawImage(batteryArrow, 750, 10, this);
    	g.drawImage(gibbotTab3, sizingWidth - gibbotTab3.getWidth(this), 
    			sleepBubble.getHeight(this), this);
    			
    	if(!pulled2 && !pulling2)
    		g.drawImage(gibbotTab2, sizingWidth - gibbotTab2.getWidth(this) + 10, 
    			sleepBubble.getHeight(this) - 30, this); //10 and -30 to account for invisible margins on the images
    	else {
    		if(pulling2){
    			g.drawImage(gibbotTab2, mouseAt - offset, 
    				sleepBubble.getHeight(this) - 30, this); //-30 to account for invisible margins on the image
    		}
    		else{
    			g.drawImage(gibbotTab2, sizingWidth - 120, 
    				sleepBubble.getHeight(this) - 30, this);//-30 to account for invisible margins on the image, -120 to keep a small 
    														//portion visible on screen
    		}
    	}
    	
    	if(!pulled1 && !pulling1)
    		g.drawImage(gibbotTab1, sizingWidth - gibbotTab1.getWidth(this) + 160, 
    			sleepBubble.getHeight(this) - 180, this); //160 and -180 to account for invisible margins on the images
    	else {
    		if(pulling1){
    			g.drawImage(gibbotTab1, mouseAt - offset, 
    				sleepBubble.getHeight(this) - 180, this); //-180 to account for invisible margins on the image
    		}
    		else{
    			g.drawImage(gibbotTab1, sizingWidth - 80, 
    				sleepBubble.getHeight(this) - 180, this);//-180 to account for invisible margins on the image, -80 to keep a small 
    														 //portion visible on screen. 
    		}
    	}
    }
    
    /**Called by {@link GUILayeredPane} when switching from asleep to awake mode. Resets all boolean state
    variables so that tabs are redrawn in original position the next time asleep mode is activated
    */
    public void resetTabs(){
    	pulled1 = false;
    	pulled2 = false;
    	pulling1 = false;
    	pulling2 = false;
    	allowDragging = false;
    }
    
    /**Called when the mouse is pressed (not clicked). Uses location of mouse at press event to set boolean state variables.
    User can press anywhere on a tab to start dragging it; however they can't move the middle tab if the top tab is pulled 
    over it.
    @param evt Used to get x, y coordinates of mouse press event
    */
    public void mousePressed(MouseEvent evt){
    	
    	int x = evt.getX();
    	int y = evt.getY();
    	
    	System.out.println(x + " " + y);
    	
    	if((!pulled1 && !pulled2) || (!pulled1 && pulled2)){ //if top tab is not pulled, the user may only pull open the top tab
    		if (x > 170 + sizingWidth - 1366 && y > 355 && y < 675){
    			pulling1 = true;
    			mouseAt = x;
    			offset = mouseAt - (sizingWidth - gibbotTab1.getWidth(this) + 160);
    		}
    	}
    	
    	if(pulled1 && !pulled2){ //either the user can pull the top tab closed again or pull the second tab open
    		if(x > 150 + sizingWidth - 1366 && x < 1320 + sizingWidth - 1366 && y > 355 && y < 675){
    			pulling2 = true;
    			mouseAt = x;
    			offset = mouseAt - (sizingWidth - gibbotTab2.getWidth(this) + 10);
    		}
    		else{
    			if (x > 1330 + sizingWidth - 1366 && y > 355 && y < 675){
    				pulled1 = false;
    				pulling1 = true;
    				mouseAt = x;
    				offset = mouseAt - (sizingWidth - 80);
    				allowDragging = true;
    			}
    		}
    	}
    	
    	if(pulled1 && pulled2){ //the user may pull either tab closed
    		if(x > 1290 + sizingWidth - 1366 && x < 1330 + sizingWidth - 1366 && y > 355 && y < 675){
    			pulled2 = false;
    			pulling2 = true;
    			mouseAt = x;
    			offset = mouseAt - (sizingWidth - 120);
    		}
    		else{
    			if (x > 1330 + sizingWidth - 1366 && y > 355 && y < 675){
    				pulled1 = false;
    				pulling1 = true;
    				mouseAt = x;
    				offset = mouseAt - (sizingWidth - 80);
    				allowDragging = true;
    			}	
    		}
    	}
    }
    
    /**Called continuously as the mouse is dragged. Only registers if one of the tabs is being pulled.
    Sets "pulling" state variables false if user pulls a tab past the right or left boundary, with the
    exception of when allowDragging is true, in which case the user is allowed to pull closed the top tab
    from rest in what would otherwise be "out of bounds" territory.
    @param evt Used to get x, y coordinates of mouse press event
    */
    public void mouseDragged(MouseEvent evt){
    	
    	int x = evt.getX();
    	int y = evt.getY();
    	
    	if(pulling1){
    		if(x < 180 + sizingWidth - 1366){
    			pulling1 = false;
    			pulled1 = false;
    		}
    		else{
    			if(x > 1330 + sizingWidth - 1366){
    				if(allowDragging)
    					mouseAt = x;
    				else{
    					pulling1 = false;
    					pulled1 = true;
    				}
    			}
    			else{
    				if(mouseAt < 1330 + sizingWidth - 1366)
    					allowDragging = false;
    				mouseAt = x;
    			}
    		}	
    	}
    	else{
    		if(pulling2){
    			if(x < 140 + sizingWidth - 1366){
	    			pulling2 = false;
    				pulled2 = false;
    			}
    			else{
	    			if(x > 1320 + sizingWidth - 1366){
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
    
    /**Called when mouse is released. Only does something if user lets go of a tab before they have
    fully pulled it open, in which case the tab is redrawn as closed
    @param evt Used to get x, y coordinates of mouse press event
    */
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
    
    /**Required for MouseListener interface*/	
    public void mouseClicked(MouseEvent evt){}
    /**Required for MouseListener interface*/
    public void mouseEntered(MouseEvent evt){}
    /**Required for MouseListener interface*/
    public void mouseExited(MouseEvent evt){}
    /**Required for MouseMotionListener interface*/
    public void mouseMoved(MouseEvent evt){}
    
    
}