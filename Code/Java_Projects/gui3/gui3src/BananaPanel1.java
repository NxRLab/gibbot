
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**BananaPanel1 handles user directions for the robot's goal coordinates (in the form of dragging and dropping
a banana on the screen), and controls animation of the robot in its movement towards those coordinates. Contained
by an instance of {@link LayoutContainerPanel}.*/
public class BananaPanel1 extends JPanel implements MouseListener, MouseMotionListener, ActionListener {
	
	private Image bananaImg = ImageHandler.getImage("banana");
	private Image bananaBubble = ImageHandler.getImage("bananaBubble");
	private Image board = ImageHandler.getImage("board");
	private Image bunch = ImageHandler.getImage("bunch");
	private Image gibbotBubble = ImageHandler.getImage("gibbotBubble");
	private Font andaleBig = ImageHandler.getFont().deriveFont(Font.BOLD, 64);
	
	/**Specified by LayoutContainerPanel parent. Used to set preferred dimensons in constructor*/
	private int height;
	/**Specified by LayoutContainerPanel parent. Used to set preferred dimensons in constructor*/
	private int width;
	
	/**Margin around the board that can't be passed in the x direction when the user is placing banana image.
	Note that the board image has upper left corner at (20, 10) with width 1285 and height 450.*/
	private final int XBOUND = 30;
	/**Margin around the board that can't be passed in the y direction when the user is placing banana image.
	Note that the board image has upper left corner at (20, 10) with width 1285 and height 450.*/ 
	private final int YBOUND = 30;
	
	/**True if the banana has been placed and gibbot movement is being animated.*/
	private boolean animating;
	/**True if the user is dragging a banana object around the screen but hasn't placed it yet.*/
	private boolean dragging;
	/**True if the user is dragging a banana object around the screen and has breached margins set by {@link #XBOUND} or {@link #YBOUND}.*/
	private boolean outOfBounds;
	
	private Banana banana = new Banana();
	private Gibbot bob = new Gibbot();
	private double timerCount; //only for gibbot animation simulation
	
	/**Color of the pulsing outline around the prompt to drag and drop a banana.*/
	private Color promptHighlight;
	/**Alpha (transparency) value of promptHighlight; this is what changes.*/
	private int a;
	
    /**Constructor sets preferred size to tell layout manager of {@link LayoutContainerPanel} how to draw this panel;
    sets all boolean state variables to false, initializes some graphics elements.
    @param widthOfContainer used to set {@link #width}
    @param heightOfContainer used to set {@link #height}*/
    public BananaPanel1(int widthOfContainer, int heightOfContainer) {
    	
    	width = widthOfContainer-30;
    	height = heightOfContainer*2/3;
    	setPreferredSize(new Dimension(width, height));
    	
    	animating = false;
    	dragging = false;
    	outOfBounds = false;
    	
    	setBackground(GibbotGUI3.globalBg);
    	setFont(andaleBig);
    	
    	a = 0;
    	promptHighlight = new Color(207, 46, 46, a);
    	
    	timerCount = 0;
    	addMouseListener(this);
    	addMouseMotionListener(this);
    	GUITimer.addActionListener(this);
		
    }
    
    /**Override of {@link javax.swing.JComponent#paintComponent}. super.paintComponent() call fills background color.
    Draws everything. This is what is executed whenever repaint() is called in the program.
    There are basically four states: (1)Nothing is happening (prompt for dragging a banana pulses);
    (2)User is dragging a banana around on screen; (3)User is dragging a banana around on screen and is
    "out of bounds" (red rectangle with warning shows up); (4)User has placed banana and the
    gibbot is being animated.
    *@param g Graphics context for drawing. Kind of a black box; gets handled in the background somehow */  	   
    public void paintComponent(Graphics g) {
    	
    	super.paintComponent(g);
    	
    	g.drawImage(board, 1, 1, getWidth()-1, getHeight()-1, this);
    	g.setColor(Color.BLACK);

    	if(!animating){	//Either nothing has happened or the user is moving the banana
    		if(dragging){ 	//user is moving the banana
    			g.drawImage(bananaImg, banana.getX(), banana.getY(), 80, 60, this);
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
        	g.drawImage(bananaImg, banana.getX(), banana.getY(), 80, 60, this);
        	bob.draw(g);    
    	}
    	
    	g.drawImage(bunch, (int)(getWidth() - (getHeight()/1.8)), -30, (int)(getHeight()/1.7), (int)(getHeight()/1.7), this);        
    	
    }
    
    /**Called when mouse is pressed (not clicked). Uses location of mouse at press event to set boolean state variables.
    As long as nothing is currently happening (gibbot is not moving), a click on the bunch of bananas image in the top
   	right corner initializes a {@link Banana} object and draws it in this class's {@link #paintComponent} method.
   	@param evt Used to get x, y coordinates of mouse press event*/
    public void mousePressed(MouseEvent evt) {
    	
    	if(animating)	//If the user clicks while the animation is going on, nothing happens.
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
   
   /**Called continuously as the mouse is dragged. Only registers if there is a banana object that's being dragged.
   "Listens" for the user dragging to an "out of bounds" region determined by {@link #XBOUND} and {@link #YBOUND}.
   @param evt Used to get x, y coordinates of mouse press event*/
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
   
   /**Called if the user drags out of the panel entirely; current {@link Banana} object is set to null.
    @param evt Used to get x, y coordinates of mouse press event*/
   public void mouseExited(MouseEvent evt){
   	
   		if(dragging){
   			dragging = false;
   			repaint();
   		}
   	}
   
   /**Called when mouse is released after a press event. Only does something if the user has been dragging a banana.
   If the coordinates of the release event are "in bounds" as specified by {@link #XBOUND} and {@link #YBOUND}, gibbot animation is
   activated.
   @param evt Used to get x, y coordinates of mouse press event*/
   public void mouseReleased(MouseEvent evt){
   		
   		if(dragging){		//NOTE: also need some restriction on target coors to keep real robot from falling off board
	   		if(outOfBounds){
	   			dragging = false;
	   			repaint();
	   		}
	   		else{
	   			dragging = false;
   				animating = true;
   				//GUISerialPort.sendGoalCoors(evt.getX(), evt.getY());
	   		}
   		}	
   }
   
   /**Specifies how to respond to timer events from {@link GUITimer}. This panel uses events as a signal to 
   change {@link #promptHighlight} color, and to run gibbot animation (which is canned right now; see: 
   {@link Gibbot#arcMotionUpdate}). Checks for when gibbot reaches banana and resets panel when it does.
   @param evt The timer event (not important to code but required by {@link java.awt.event#ActionListener} interface)*/
   public void actionPerformed(ActionEvent evt){
											
   		if(animating && (int)bob.getPivotX() <= banana.getX()){  //If the robot is not to the bananas yet	
   			bob.arcMotionUpdate(timerCount);
   			//With camera data, above call will be replaced by bob.updateRealCoors(); 
   			timerCount++;
   		}
   		
   		else{
   			if(animating){ 	//When the robot reaches the bananas, the panel resets itself.            
	   			animating = false;
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
   /**Required for MouseListener interface*/
   public void mouseClicked(MouseEvent evt){}
   /**Required for MouseListener interface*/
   public void mouseEntered(MouseEvent evt){}
   /**Required for MouseMotionListener interface*/
   public void mouseMoved(MouseEvent evt){}
    
}