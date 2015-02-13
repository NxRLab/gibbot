import java.awt.*;
import java.awt.event.*;
import java.util.HashMap;

import javax.swing.*;

/**SpeedometerBox is what it sounds like; shows the linear velocity of the two links with two different colored "needles"
 */
public class SpeedometerBox extends JPanel implements ActionListener{
	
	//private Image chart = ImageHandler.getImage("speedometerChart");
	
	private Image speedometer = ImageHandler.getImage("speedometer.png");
	private Image batteryBar = ImageHandler.getImage("batteryBar.png");
	
    /**Specified by LayoutContainerPanel parent. Used to set preferred dimensions in constructor*/
	private int height;
	/**Specified by LayoutContainerPanel parent. Used to set preferred dimensions in constructor*/
	private int width;
	

    /**Width of chart image*/
    private int w;
    /**Height of chart image*/
	private int h;
		
	/**Horizontal scale for drawing chart image (not really needed unless {@link GUILayeredPane#DRAWING_WIDTH} is altered)*/
	private double xscale;
	/**Vertical scale for drawing chart image (not really needed unless {@link GUILayeredPane#DRAWING_HEIGHT} is altered)*/
	private double yscale;
	
	/**Proportion of horizontal space this box will take up in {@link LayoutContainerPanel}. Strongly recommended not to alter.*/
	private final double SPEEDOMETER_WIDTH_ALLOCATION = 1/3.0;
	/**Proportion of vertical space this box will take up in {@link LayoutContainerPanel}. Strongly recommended not to alter.*/
	private final double SPEEDOMETER_HEIGHT_ALLOCATION = 1/3.25;
    
	/**Horizontal margin around chart area when placed in panel. Strongly recommended not to alter.*/
	private final int XMARGIN = 35;
	/**Vertical margin around chart area when placed in panel. Strongly recommended not to alter.*/
	private final int YMARGIN = 30;
	/**X-coor of upper left corner of {@link #chart}. Strongly recommended not to alter.*/
	private final int CHARTX = 30;
	/**Y-coor of upper left corner of {@link #chart}. Strongly recommended not to alter.*/
	private final int CHARTY = 20;
	
	/**Radius of both needles on speedometer graphic. Alterations okay if needed.*/
	private final int NEEDLE_RADIUS = 117;
	/**X-coor of where needles on speedometer graphic are anchored.*/
	//private final int NEEDLE_XORIGIN = ImageHandler.SPEEDOMETER_NEEDLE_XORIGIN;
	/**Y-coor of where needles on speedometer graphic are anchored.*/
	//private final int NEEDLE_YORIGIN = ImageHandler.SPEEDOMETER_NEEDLE_YORIGIN;
	
	/**Light shadow color*/
	private final Color SHADOW1 = new Color(125, 125, 125, 50);
	/**Medium -light shadow color*/
	private final Color SHADOW2 = new Color(125, 125, 125, 100);
	/**Medium-dark shadow color*/
	private final Color SHADOW3 = new Color(125, 125, 125, 150);
	/**Dark shadow color*/
	private final Color SHADOW4 = new Color(130, 130, 130, 200);
	/**Color of the rectangle the chart is in*/
	private final Color CHART_BG = GibbotGUI3.SECONDARY_GLOBAL_BG;
	
	/**Color of needle on the speedometer corresponding to first link. If altered, also alter 
	 *{@link Gibbot#ARM1COLOR} with same first three values (RGB) but no fourth parameter (alpha).*/
	public final Color ARM1COLOR = new Color(150, 150, 150, 100);
	/**Color of needle on the speedometer corresponding to second link. If altered, also alter 
	 *{@link Gibbot#ARM2COLOR} with same first three values (RGB) but no fourth parameter (alpha).*/
	public final Color ARM2COLOR = new Color(36, 149, 176, 125);
	
	/**Value of velocity for first link (primary board) that's displayed on the speedometer*/	
	private double arm1vel;
	/**Value of velocity for second link (secondary board) that's displayed on the speedometer*/ 
	private double arm2vel;
 
	
	/**Constructor sets preferred size to tell layout manager of {@link LayoutContainerPanel} how to draw this panel;
    Initializes chart size variables.
    @param widthOfContainer used to set {@link #width}
    @param heightOfContainer used to set {@link #height}*/
	public SpeedometerBox(int widthOfContainer, int heightOfContainer){
		
		width = (int)(widthOfContainer*SPEEDOMETER_WIDTH_ALLOCATION);
		height = (int)(heightOfContainer*SPEEDOMETER_HEIGHT_ALLOCATION);
		
		setPreferredSize(new Dimension(width, height));
		setBackground(GibbotGUI3.GLOBAL_BG);
		
		w = width - 2*XMARGIN;
		h = height - 2*YMARGIN;
		//xscale = w/(double)(ImageHandler.SPEEDOMETER_WIDTH);
		//yscale = h/(double)(ImageHandler.HEIGHT);

		GUITimer.addActionListener(this);
	}
	
	/**Override of {@link javax.swing.JComponent#paintComponent}. super.paintComponent() call fills background color.
    This is what is executed whenever repaint() is called in the program. 
    Calls {@link #drawTab} to draw containing rectangle and shadow, draws chart image, then draws needles in the appropriate place. 
    @param g Graphics context for drawing. Kind of a black box; gets handled in the background somehow
     */ 
	public void paintComponent(Graphics g){
		
		//drawTab(width, height - CHARTY, g);
		
		//battery bar
		g.drawImage(batteryBar, 15, 10, 150, 200, this);
		g.drawImage(speedometer, 170, 15, 200, 200, this); //image, x coor, y coor, x size, y size, this
		
		Graphics2D g2 = (Graphics2D)g;
		g2.setColor(Color.RED);
		g2.setStroke(new BasicStroke(3)); //thickness of needle
		g2.drawLine(270, 115, 213, 175); //puts speedometer red needle at speedometer 0
		/*
		super.paintComponent(g);
		drawTab(width, height - CHARTY, g);
		g.drawImage(chart, CHARTX, CHARTY, w, h, this);
		
		Graphics2D g2 = (Graphics2D)g;
		g2.setColor(ARM1COLOR);
		g2.setStroke(new BasicStroke(4, BasicStroke.CAP_ROUND, BasicStroke.JOIN_BEVEL));
		g2.drawLine((int)(xscale*NEEDLE_XORIGIN) + CHARTX, (int)(yscale*NEEDLE_YORIGIN + CHARTY), 
			(int)(xscale*(NEEDLE_XORIGIN - NEEDLE_RADIUS*Math.cos(arm1vel))) + CHARTX, 
				(int)(yscale*(NEEDLE_YORIGIN - NEEDLE_RADIUS*Math.sin(arm1vel))) + CHARTY);
		g2.setColor(ARM2COLOR);
		g2.drawLine((int)(xscale*NEEDLE_XORIGIN) + CHARTX, (int)(yscale*NEEDLE_YORIGIN + CHARTY), 
			(int)(xscale*(NEEDLE_XORIGIN - NEEDLE_RADIUS*Math.cos(arm2vel)) + CHARTX), 
				(int)(yscale*(NEEDLE_YORIGIN - NEEDLE_RADIUS*Math.sin(arm2vel))) + CHARTY);
		 */
	}
	
	/**Gets velocity values from {@link GUISerialPort#data}. Called by {@link #actionPerformed}.
	*/
	public void updateForDrawing(){
		/*
	
		int[] data = GUISerialPort.getData();	
	
		arm1vel = data[4]*Math.PI/180; //convert to radians
		arm2vel = data[5]*Math.PI/180; //convert to radians
		*/
		HashMap<String, Integer> data = GUISerialPort.getData();	
		
		arm1vel = data.get("Gyroscope_Z_Primary")*Math.PI/180; //convert to radians
		arm2vel = data.get("Gyroscope_Z_Secondary")*Math.PI/180; //convert to radians
			
	}
				
	/**Draws the containing rectangle and shadow. Called by {@link #paintComponent}.
	@param width Width of rectangle available to draw in
    @param height Height of rectangle available to draw in
    @param g Graphics context to draw with.
     */
	public void drawTab(int width, int height, Graphics g){
    	
    	g.setColor(SHADOW1);
    	g.fillRoundRect(7, 7, width - 7, height + 12, 12, 12);
    	
    	g.setColor(SHADOW2); 
    	g.fillRoundRect(7, 7, width - 11, height + 8, 12, 12);
        
        g.setColor(SHADOW3); 
    	g.fillRoundRect(7, 7, width - 15, height + 4, 12, 12);
    	
    	g.setColor(SHADOW4); 
    	g.fillRoundRect(7, 7, width - 19, height, 9, 9);
   		
   		g.setColor(CHART_BG);
    	g.fillRoundRect(3, 3, width - 19, height, 12, 12);
    	
	}
	
	/**Specifies how to respond to timer events from {@link GUITimer}. This panel uses events as a signal to 
    call {@link #updateForDrawing} and repaint. Only updates for drawing if awake panel is active.
    @param evt The timer event (not important to code but required by {@link java.awt.event#ActionListener} interface)
    */
	public void actionPerformed(ActionEvent evt){

			updateForDrawing();
			repaint();
	}	
}