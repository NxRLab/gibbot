
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**Speedometer is what it sounds like; shows the linear velocity of the two links with two different colored "needles"
 */
public class Speedometer extends JPanel implements ActionListener{
	
	private Image chart = ImageHandler.getImage("speedometer");

    /**Specified by LayoutContainerPanel parent. Used to set preferred dimensons in constructor*/
	private int height;
	/**Specified by LayoutContainerPanel parent. Used to set preferred dimensons in constructor*/
	private int width;
    
    /**Width for drawing chart image (not really needed unless parameters of setBounds() call in {@link GUILayeredPane#GUILayeredPane} are altered)*/
    private int w;
    /**Height for drawing chart image (not really needed unless parameters of setBounds() call in {@link GUILayeredPane#GUILayeredPane} are altered)*/
	private int h;
	/**Horizontal scale for drawing chart image (not really needed unless parameters of setBounds() call in {@link GUILayeredPane#GUILayeredPane} are altered)*/
	private double xscale;
	/**Vertical for drawing chart image (not really needed unless parameters of setBounds() call in {@link GUILayeredPane#GUILayeredPane} are altered)*/
	private double yscale;
	
	/**Value of velocity for first link (primary board) that's displayed on the speedometer*/	
	private int arm1vel;
	/**Value of velocity for second link (secondary board) that's displayed on the speedometer*/ 
	private int arm2vel; 
	
	/**Constructor sets preferred size to tell layout manager of {@link LayoutContainerPanel} how to draw this panel;
    Initializes chart size variables.
    @param widthOfContainer used to set {@link #width}
    @param heightOfContainer used to set {@link #height}*/
	public Speedometer(int widthOfContainer, int heightOfContainer){
		
		width = widthOfContainer/3;
		height = (int)(heightOfContainer/3.25);
		setPreferredSize(new Dimension(width, height));
		setBackground(GibbotGUI3.globalBg);
		w = width - 70;
		h = height - 60;
		xscale = w/363.0;
		yscale = h/185.0;
		GUITimer.addActionListener(this);
	}
	
	/**Override of {@link javax.swing.JComponent#paintComponent}. super.paintComponent() call fills background color.
    This is what is executed whenever repaint() is called in the program. 
    Calls {@link #drawTab} to draw containing rectangle and shadow, draws chart image, then draws needles in the appropriate place. 
    @param g Graphics context for drawing. Kind of a black box; gets handled in the background somehow
     */ 
	public void paintComponent(Graphics g){
		
		super.paintComponent(g);
		drawTab(width, height - 20, g);
		g.drawImage(chart, 30, 20, w, h, this);
		
		Graphics2D g2 = (Graphics2D)g;
		g2.setColor(new Color(150, 150, 150, 100));
		g2.setStroke(new BasicStroke(4, BasicStroke.CAP_ROUND, BasicStroke.JOIN_BEVEL));
		g2.drawLine((int)(xscale*182) + 30, (int)(yscale*163 + 20), 
			(int)(xscale*(182 - 117*Math.cos(arm1vel*Math.PI/180))), (int)(yscale*(170 - 117*Math.sin(arm1vel*Math.PI/180))));
		g2.setColor(new Color(36, 149, 176, 125));
		g2.drawLine((int)(xscale*182) + 30, (int)(yscale*163 + 20), 
			(int)(xscale*(182 - 117*Math.cos(arm2vel*Math.PI/180))), (int)(yscale*(170 - 117*Math.sin(arm2vel*Math.PI/180))));

	}
	
	/**Gets velocity values from {@link GUISerialPort#data}. Called by {@link #actionPerformed}.
	*/
	public void updateForDrawing(){
	
		int[] data = GUISerialPort.getData();	
	
		arm1vel = data[4]; 
		arm2vel = data[5]; 
			
	}
				
	/**Draws the containing rectangle and shadow. Called by {@link #paintComponent}.
	@param width Width of rectangle available to draw in
    @param height Height of rectangle available to draw in
    @param g Graphics context to draw with.
     */
	public void drawTab(int width, int height, Graphics g){
    	
    	g.setColor(new Color(125, 125, 125, 50)); //lightest gray
    	g.fillRoundRect(7, 7, width - 7, height + 12, 12, 12);
    	
    	g.setColor(new Color(125, 125, 125, 100)); //light gray
    	g.fillRoundRect(7, 7, width - 11, height + 8, 12, 12);
        
        g.setColor(new Color(125, 125, 125, 150)); //middle gray
    	g.fillRoundRect(7, 7, width - 15, height + 4, 12, 12);
    	
    	g.setColor(new Color(130, 130, 130, 200)); //dark gray
    	g.fillRoundRect(7, 7, width - 19, height, 9, 9);
   		
   		g.setColor(new Color(240, 240, 240));
    	g.fillRoundRect(3, 3, width - 19, height, 12, 12);

	}
	
	/**Specifies how to respond to timer events from {@link GUITimer}. This panel uses events as a signal to 
    call {@link #updateForDrawing} and repaint.
    @param evt The timer event (not important to code but required by {@link java.awt.event#ActionListener} interface)
    */
	public void actionPerformed(ActionEvent evt){
		
		updateForDrawing();
		repaint();
	}
	
}