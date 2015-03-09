import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**This is the "asleep" view of the GUI. The gibbotTab images contain "public-friendly" 
 *descriptions of how the robot works. Only subpanel is a {@link ChargingBox} instance.
 *Strongly recommended not to alter any fields declared final.
 */
public class LayoutContainerPanel2 extends JPanel implements MouseListener, MouseMotionListener, ActionListener {

	private Image batteryArrow = ImageHandler.getImage("batteryArrow.png");
	private Image gibbotTab1 = ImageHandler.getImage("gibbotTab1.png");
	private Image gibbotTab2 = ImageHandler.getImage("gibbotTab2.png");
	private Image gibbotTab3 = ImageHandler.getImage("gibbotTab3.png");
	private Image sleepBubble = ImageHandler.getImage("sleepBubble.png");
	
	/**Specified by GUILayeredPane parent. Used to determine anchor locations for pull tabs.*/
	private int sizingWidth;
	/**Difference between sizingWidth and 1366 (the original width used to design the GUI)*/
	private int widthCorrection;
	
	/**Furthest left user is allowed to get or pull top tab when closed*/
	private final int LEFT_BOUND_1 = 180;
	/**Furthest left user is allowed to get or pull middle tab when closed*/
	private final int LEFT_BOUND_2 = 140;
	/**Furthest right user is allowed to get or pull top tab when open*/
	private final int RIGHT_BOUND_1 = 1330;
	/**Furthest right user is allowed to get or pull middle tab when open*/
	private final int RIGHT_BOUND_2 = 1290;
	/**Furthest up user is allowed to get or pull either tab*/
	private final int TOP_BOUND = 355;
	/**Furthest down user is allowed to get or pull either tab*/
	private final int BOTTOM_BOUND = 675;
	
	/**X-coor of top tab when closed; set in constructor method*/
	private final int CLOSED_X1;
	/**X-coor of top tab when open; set in constructor method*/
	private final int OPEN_X1;
	/**Y-coor of top tab; set in constructor method*/
	private final int Y1;
	/**X-coor of middle tab when closed; set in constructor method*/
	private final int CLOSED_X2;
	/**X-coor of middle tab when open; set in constructor method*/
	private final int OPEN_X2;
	/**Y-coor of middle tab; set in constructor method*/
	private final int Y2;
	
	/**True if top pull tab is pulled open (not visible)*/
	private boolean pulled1;
	/**True if middle pull tab is pulled open (not visible)*/
	private boolean pulled2;
	/**True if top pull tab is being pulled by user*/
	private boolean pulling1;
	/**True if middle pull tab is being pulled by user*/	
	private boolean pulling2;
	/**True if the user was swiping the top pull tab and let go*/
	private boolean floating1;
	/**True if the user was swiping the middle pull tab and let go*/
	private boolean floating2;
	/**True if top tab is pulled open (not visible).
	 *Allows user to pull top tab closed, since mouse-handling methods don't allow 
	 *dragging past a certain point - to keep the end of the tab visible.*/
	private boolean allowDragging;
	
	/**X-coordinate of where the user grabs a tab to move it*/
	private int mouseAt;
	/**Difference between left-most edge of the tab image and mouseAt*/
	private int offset;
	
	/**Used to track velocity as user is pulling a tab*/
	private long t = System.currentTimeMillis();
	/**Velocity at which user is pulling tab (pixels/sec)*/
	private double v;
	/**Time between timer fires (sec), used to update velocity of a "floating" tab*/
	private double dt = (double)GUITimer.getMillisPerFrame()/1000;
	/**Acceleration of a "floating" tab*/
	private double a = -6000;
	
	/**Transparent dark gray, for the background*/
	private final Color TRANSPARENT_BG = new Color(125, 125, 125, 180); 
	
	/**charge is declared public for access by {@link GUILayeredPane} for enabling/disabling*/
	public ChargingBox charge;

	/**Constructor adds an instance of {@link ChargingBox} and initializes all boolean state variables to false
	 *@param sizeW Used to set {@link #sizingWidth}*/
    public LayoutContainerPanel2(int sizeW) {
    	
    	sizingWidth = sizeW;
    	
    	widthCorrection = sizingWidth - 1366;
    	CLOSED_X1 = sizingWidth - (gibbotTab1.getWidth(this) - 160); //-160 to account for image margins
    	OPEN_X1 = sizingWidth - 80; //-80 to keep small portion visible on screen
    	Y1 = sleepBubble.getHeight(this) - 180; //-180 to account for image margins
    	CLOSED_X2 = sizingWidth - (gibbotTab2.getWidth(this) - 10); //-10 to account for image margins
    	OPEN_X2 = sizingWidth - 120; //-120 to keep small portion visible on screen
    	Y2 = sleepBubble.getHeight(this) - 30; //-30 to account for image margins

    	setLayout(null);
  
    	charge = new ChargingBox();
    	charge.setOpaque(false);
    	charge.setBounds(975, 5, 250, 350); //location and dimensions of battery charging icon
    	add(charge);
    	
    	addMouseListener(this);
    	addMouseMotionListener(this);
    	
    	pulled1 = false;
    	pulled2 = false;
    	pulling1 = false;
    	pulling2 = false;
    	floating1 = false;
    	floating2 = false;
    	allowDragging = false;
    }
    
    /**Override of {@link javax.swing.JComponent#paintComponent}. super.paintComponent() call fills background color.
     *Draws everything. This is what is executed whenever repaint() is called in the program. 
     *First fills entire space with a transparent gray background, then draws images.
     *Uses boolean state variables to determine how to draw the gibbotTab images. 
     *@param g Graphics context for drawing. Kind of a black box; gets handled in the background somehow
     * */  	
    public void paintComponent(Graphics g){

    	g.setColor(TRANSPARENT_BG);
    	g.fillRect(0, 0, getWidth(), getHeight());
    	g.drawImage(sleepBubble, 0, 0, this);
    	g.drawImage(batteryArrow, 750, 10, this);
    	g.drawImage(gibbotTab3, sizingWidth - gibbotTab3.getWidth(this), //third tab doesn't move, so it's always drawn															 
				sleepBubble.getHeight(this), this);						 //in the same place.
    			
    	if(!pulled2 && !pulling2 && !floating2) //closed
    		g.drawImage(gibbotTab2, CLOSED_X2, Y2, this); 
    	else {
    		if(pulling2 || floating2) //in the middle
    			g.drawImage(gibbotTab2, mouseAt - offset, Y2, this);
    		else{ //open
    			g.drawImage(gibbotTab2, OPEN_X2, Y2, this);														
    		}
    	}
    	
    	if(!pulled1 && !pulling1 && !floating1) //closed
    		g.drawImage(gibbotTab1, CLOSED_X1, Y1, this);
    	else {
    		if(pulling1 || floating1) //in the middle
    			g.drawImage(gibbotTab1, mouseAt - offset, Y1, this); 
    		else{ //open
    			g.drawImage(gibbotTab1, OPEN_X1, Y1, this);
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
    	
    	if((!pulled1 && !pulled2) || (!pulled1 && pulled2)){ //if top tab is not pulled, the user may only pull open the top tab
    		if (x > LEFT_BOUND_1 + widthCorrection && y > TOP_BOUND && y < BOTTOM_BOUND){
    			pulling1 = true;
    			mouseAt = x;
    			offset = mouseAt - CLOSED_X1;
    		}
    	}
    	
    	if(pulled1 && !pulled2){ //either the user can pull the top tab closed again or pull the second tab open
    		if(x > LEFT_BOUND_2 + widthCorrection && x < 1320 + widthCorrection && y > TOP_BOUND && y < BOTTOM_BOUND){
    			pulling2 = true;
    			mouseAt = x;
    			offset = mouseAt - CLOSED_X2;
    		}
    		else{
    			if (x > RIGHT_BOUND_1 + widthCorrection && y > TOP_BOUND && y < BOTTOM_BOUND){
    				pulled1 = false;
    				pulling1 = true;
    				mouseAt = x;
    				offset = mouseAt - (OPEN_X1);
    				allowDragging = true;
    			}
    		}
    	}
    	
    	if(pulled1 && pulled2){ //the user may pull either tab closed
    		if(x > RIGHT_BOUND_2 + widthCorrection && x < RIGHT_BOUND_1 + widthCorrection && y > TOP_BOUND && y < BOTTOM_BOUND){
    			pulled2 = false;
    			pulling2 = true;
    			mouseAt = x;
    			offset = mouseAt - (OPEN_X2);
    		}
    		else{
    			if (x > RIGHT_BOUND_1 + widthCorrection && y > TOP_BOUND && y < BOTTOM_BOUND){
    				pulled1 = false;
    				pulling1 = true;
    				mouseAt = x;
    				offset = mouseAt - (OPEN_X1);
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
    		v = (double)(x - mouseAt)/(System.currentTimeMillis() - t)*1000;
    		t = System.currentTimeMillis();
    		if(x - offset < CLOSED_X1 + widthCorrection){ //pulled too far to the left
    			pulling1 = false;
    			pulled1 = false;
    		}
    		else{
    			if(x > RIGHT_BOUND_1 + widthCorrection){ //pulled too far to the right
    				if(allowDragging)
    					mouseAt = x;
    				else{
    					pulling1 = false;
    					pulled1 = true;
    				}
    			}
    			else{ //just pulling around in the middle (checks to see if it needs to update allowDragging, as well).
    				if(mouseAt < RIGHT_BOUND_1 + widthCorrection)
    					allowDragging = false;
    				mouseAt = x;
    			}
    		}	
    	}
    	else{
    		if(pulling2){
    			v = (double)(x - mouseAt)/(System.currentTimeMillis() - t)*1000;
    			t = System.currentTimeMillis();
    			if(x  - offset < CLOSED_X2 + widthCorrection){ //pulled too far to the left
	    			pulling2 = false;
    				pulled2 = false;
    			}
    			else{
	    			if(x > RIGHT_BOUND_2 + 30 + widthCorrection){ //pulled too far to the right; +30 to allow it to pull from start point
    					pulling2 = false;
    					pulled2 = true;
    				}
    				else{ //just pulling around in the middle
    					mouseAt = x;
    				}
    			}	
    		}
    	}
    	
    	repaint();
    }
    
    /**Called when mouse is released. Only does something if user lets go of a tab before they have
    fully pulled it open, in which case the tab is set to "floating" state and is handled by {@link #actionPerformed}.
    @param evt Used to get x coordinate of mouse press event
    */
    public void mouseReleased(MouseEvent evt){
    	
    	int x = evt.getX();
    	
    	if(pulling1){
    		pulling1 = false;
    		floating1 = true;
    		GUITimer.addActionListener(this);
    		//repaint();
    	}
    	else{
    		if(pulling2){
    			pulling2 = false;
    			floating2 = true;
    			GUITimer.addActionListener(this);
    			//repaint();
    		}
    	}   			
    }
    
    /**Specifies how to respond to timer events from {@link GUITimer}. This panel uses events as a signal to 
   update status of a "floating" tab (user let go while swiping; tab continues to move, but decelerates.)
   @param evt The timer event (not important to code but required by {@link java.awt.event#ActionListener} interface)*/
    public void actionPerformed(ActionEvent evt){
    	
    	if(floating1){
	    	if(v <= 0){ //stopped before getting anywhere
    			floating1 = false;
    			pulled1 = false;
    			GUITimer.removeActionListener(this);
    			repaint();
    			return;
    		}	
    		else{ //update floating motion
    			mouseAt = (int)(v*dt + mouseAt);
    			v = a*dt + v;
    		}
    		
    		if(mouseAt < LEFT_BOUND_1 + widthCorrection){ //floated too far to the left
    			floating1 = false;
    			pulled1 = false;
    		}
    		else{
    			if(mouseAt > RIGHT_BOUND_1 + widthCorrection){ //floated too far to the right
    				floating1 = false;
    				pulled1 = true;
    			}	
    		}
    	}
    		
    	if(floating2){
    		if(v <= 0){ //stopped before getting anywhere
    			floating2 = false;
    			pulled2 = false;
    			GUITimer.removeActionListener(this);
    			repaint();
    			return;
    		}	
    		else{ //update floating motion
    			mouseAt = (int)(v*dt + mouseAt);
    			v = a*dt + v;
    		}
    		
    		if(mouseAt < LEFT_BOUND_2 + widthCorrection){ //floated too far to the left
	    			floating2 = false;
    				pulled2 = false;
    		}
    			else{
	    			if(mouseAt > RIGHT_BOUND_2 + widthCorrection){ //floated too far to the right
    					floating2 = false;
    					pulled2 = true;
    			}
    		}	
    	}
    	repaint();
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