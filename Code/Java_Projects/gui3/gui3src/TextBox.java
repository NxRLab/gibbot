
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
	
	/**Wireless signal: dot only*/
	private final int W0 = 0;
	/**Wireless signal: dot, one arc*/
	private final int W1 = 1;
	/**Wireless signal: dot, two arcs*/
	private final int W2 = 2;
	/**Wireless signal: dot, three arcs*/
	private final int W3 = 3;
	
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
    	
    	width = widthOfContainer/4 - 20;
    	height = (int)(heightOfContainer/3.25) - 30;
    	setPreferredSize(new Dimension(width, height));
    	setBackground(GibbotGUI3.globalBg);
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
    	drawTextBubble(10, 20, width - 30, height - 20, g);
    	
    }
    
    /**Draws all graphics for the TextBox panel.
    @param x X-coor of upper left corner
    @param y Y-coor of upper left corner
    @param width Width of rectangle available to draw text in
    @param height Height of rectangle available to draw text in
    @param g Graphics context to draw with.*/
    public void drawTextBubble(int x, int y, int width, int height, Graphics g){
    	
    	g.setColor(new Color(0, 51, 153));
    	g.drawString("real time", x + 15, 70);
    	g.drawString("wireless", x + 24, 110);
    	g.drawString("data from", x + 15, 150);
    	g.drawString("the gibbot", x + 6, 190);
    	
    	Graphics2D g2 = (Graphics2D)g;
    	g2.setStroke(new BasicStroke(5, BasicStroke.CAP_ROUND, BasicStroke.JOIN_BEVEL));
    	g2.setColor(new Color (0, 51, 153));
    	
    	switch(wireless){
    		case(W0):
    			g2.fillOval(width - 5, height/2 + 15, 15, 15);
    			break;
    		case(W1):;
    			g2.fillOval(width - 5, height/2 + 15, 15, 15);
    			g2.drawArc(width - 35, height/2 - 7, 60, 60, -45, 90);
    			break;
    		case(W2):;
    			g2.fillOval(width - 5, height/2 + 15, 15, 15);
    			g2.drawArc(width - 35, height/2 - 7, 60, 60, -45, 90);
    			g2.drawArc(width - 50, height/2 - 22, 90, 90, -45, 90);
    			break;
    		case(W3):;
    			g2.fillOval(width - 5, height/2 + 15, 15, 15);
    			g2.drawArc(width - 35, height/2 - 7, 60, 60, -45, 90);
    			g2.drawArc(width - 50, height/2 - 22, 90, 90, -45, 90);
    			g2.drawArc(width - 65, height/2 - 37, 120, 120, -45, 90);
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