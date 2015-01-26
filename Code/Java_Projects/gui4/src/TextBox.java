
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**TextBox displays the message: "real time wireless data from the gibbot" with an animated
 *wireless signal.
 */

public class TextBox extends JPanel implements ActionListener{
	
	/**Font used to write. Set to bold, size 36.*/
	private final Font ANDALE_BIG = ImageHandler.getFont().deriveFont(Font.BOLD, 36);
	
	/**Specified by LayoutContainerPanel parent. Used to set preferred dimensons in constructor*/
	private int height;
	/**Specified by LayoutContainerPanel parent. Used to set preferred dimensons in constructor*/
	private int width;
	
	/**Horizontal margin around chart area when placed in panel. Strongly recommended not to alter.*/
	private final int XMARGIN = 15;
	/**Vertical margin around chart area when placed in panel. Strongly recommended not to alter.*/
	private final int YMARGIN = 10;
	/**X-coor of upper left corner of box. Strongly recommended not to alter.*/
	private final int BOXX = 10;
	/**Y-coor of upper left corner of box. Strongly recommended not to alter.*/
	private final int BOXY = 20;
	
	/**Proportion of horizontal space this box will take up in {@link LayoutContainerPanel}. Stronly recommended not to alter.*/
	private final double TEXT_WIDTH_ALLOCATION = .23;
	/**Proportion of vertical space this box will take up in {@link LayoutContainerPanel}. Stronly recommended not to alter.*/
	private final double TEXT_HEIGHT_ALLOCATION = 1/3.45;
	
	/**Wireless signal: dot only*/
	private final int W0 = 0;
	/**Wireless signal: dot, one arc*/
	private final int W1 = 1;
	/**Wireless signal: dot, two arcs*/
	private final int W2 = 2;
	/**Wireless signal: dot, three arcs*/
	private final int W3 = 3;
	
	/**Length, in pixels, of wireless signal dot*/
	private final int DOT_RAD = 15;
	/**Length, in pixels, of wireless signal first arc*/
	private final int ARC1_RAD = 60;
	/**Length, in pixels, of wireless signal second arc*/
	private final int ARC2_RAD = 90;
	/**Length, in pixels, of wireless signal third arc*/
	private final int ARC3_RAD = 120;
	/**Degrees relative to pos. x-axis where arcs begin*/
	private final int START_ANGLE = -45;
	/**Degree measure of arcs*/
	private final int ARC_ANGLE = 90;
	
	private final Color INDIGO = new Color(0, 51, 153);
	
	/**Set to W[int] to determine which wireless signal frame to draw.*/
	private int wireless;
	/**Used to update {@link #wireless} at even intervals.*/
	private int timerCount;
	/**How many timer events heard before wireless is updated (currently set so that signal updates every .75 seconds*/
	private final int UPDATE_COUNT = (int)(750/GUITimer.getMillisPerFrame()); //symbol updates every .75 seconds

    /**Constructor sets preferred size to tell layout manager of {@link LayoutContainerPanel} how to draw this panel;
    Initializes some graphics elements including wireless signal.
    @param widthOfContainer used to set {@link #width}
    @param heightOfContainer used to set {@link #height}*/
    public TextBox(int widthOfContainer, int heightOfContainer) {
    	
    	width = (int)(widthOfContainer*TEXT_WIDTH_ALLOCATION);
    	height = (int)(heightOfContainer*TEXT_HEIGHT_ALLOCATION);
    	
    	setPreferredSize(new Dimension(width, height));
    	setBackground(GibbotGUI3.GLOBAL_BG);
    	setFont(ANDALE_BIG);
    	
    	timerCount = 0;
    	wireless = -1;
    	
    	GUITimer.addActionListener(this);
    }
    
    /**Override of {@link javax.swing.JComponent#paintComponent}. super.paintComponent() call fills background color.
     *This is what is executed whenever repaint() is called in the program. 
     *Calls {@link #drawTextBubble} to draw everything. If images need to be relocated/resized, change parameters of this call.
     *@param g Graphics context for drawing. Kind of a black box; gets handled in the background somehow */  	
    public void paintComponent(Graphics g){
    	
    	super.paintComponent(g);
    	drawTextBubble(BOXX, BOXY, width - 2*XMARGIN, height - 2*YMARGIN, g);
    	
    }
    
    /**Draws all graphics for the TextBox panel.
    @param x X-coor of upper left corner
    @param y Y-coor of upper left corner
    @param w Width of rectangle available to draw text in
    @param h Height of rectangle available to draw text in
    @param g Graphics context to draw with.*/
    public void drawTextBubble(int x, int y, int w, int h, Graphics g){
    	
    	g.setColor(INDIGO);
    	g.drawString("real time", x + 15, 70); //last two parameters give (x, y) coors of bottom left corner.
    	g.drawString("wireless", x + 24, 110);
    	g.drawString("data from", x + 15, 150);
    	g.drawString("the gibbot", x + 6, 190);
    	
    	Graphics2D g2 = (Graphics2D)g;
    	g2.setStroke(new BasicStroke(5, BasicStroke.CAP_ROUND, BasicStroke.JOIN_BEVEL));
    	g2.setColor(INDIGO);
    	
    	switch(wireless){
    		case(W0):
    			g2.fillOval(w - 5, h/2 + DOT_RAD, DOT_RAD, DOT_RAD); //first two parameters are (x, y) of upper left 
    																 //corner of binding rectangle; do not alter.
    			break;
    		case(W1):;
    			g2.fillOval(w - 5, h/2 + DOT_RAD, DOT_RAD, DOT_RAD);
    			g2.drawArc(w - 35, h/2 - 7, ARC1_RAD, ARC1_RAD, START_ANGLE, ARC_ANGLE);
    			break;
    		case(W2):;
    			g2.fillOval(w - 5, h/2 + DOT_RAD, DOT_RAD, DOT_RAD);
    			g2.drawArc(w - 35, h/2 - 7, ARC1_RAD, ARC1_RAD, START_ANGLE, ARC_ANGLE);
    			g2.drawArc(w - 50, h/2 - 22, ARC2_RAD, ARC2_RAD, START_ANGLE, ARC_ANGLE);
    			break;
    		case(W3):;
    			g2.fillOval(w - 5, h/2 + DOT_RAD, DOT_RAD, DOT_RAD);
    			g2.drawArc(w - 35, h/2 - 7, ARC1_RAD, ARC1_RAD, START_ANGLE, ARC_ANGLE);
    			g2.drawArc(w - 50, h/2 - 22, ARC2_RAD, ARC2_RAD, START_ANGLE, ARC_ANGLE);
    			g2.drawArc(w - 65, h/2 - 37, ARC3_RAD, ARC3_RAD, START_ANGLE, ARC_ANGLE);
    			break;
    	}
    }
    
    /**Specifies how to respond to timer events from {@link GUITimer}. This panel uses events as a signal to 
    update {@link #wireless} at frequency determined by {@link #UPDATE_COUNT}. Only updates  for drawing if awake
    panel is active.
    @param evt The timer event (not important to code but required by {@link java.awt.event#ActionListener} interface)*/
    public void actionPerformed(ActionEvent evt){ 

	    	if(timerCount % UPDATE_COUNT == 0){
    			wireless++;
    			repaint();
	    	}
    		
	    	if(timerCount == UPDATE_COUNT*4){
    			timerCount = 1;
    			wireless = W0;
	    	}
    		else
    			timerCount++;
		}   	  
}