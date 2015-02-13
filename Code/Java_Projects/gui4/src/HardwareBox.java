
import java.awt.*;
import java.awt.event.*;
import java.util.HashMap;

import javax.swing.*;

/**HardwareBox displays motor temperature and battery life in a bar chart graphic
 */
public class HardwareBox extends JPanel implements ActionListener{
	
	//private Image chart = ImageHandler.getImage("hardwareChart");

	private Image thermometer = ImageHandler.getImage("thermometer.png");
	
    /**Specified by LayoutContainerPanel parent. Used to set preferred dimensions in constructor*/
	private int height;
	/**Specified by LayoutContainerPanel parent. Used to set preferred dimensions in constructor*/
	private int width;
	    
    /**Width for drawing chart image
    private int w;
    /**Height for drawing chart image
	private int h;
		
	/**Horizontal scale for drawing chart image (not really needed unless {@link GUILayeredPane#DRAWING_WIDTH} is altered)
	private double xscale;
	/**Vertical scale for drawing chart image (not really needed unless {@link GUILayeredPane#DRAWING_HEIGHT} is altered)
	private double yscale;
	*/
	/**Proportion of horizontal space this box will take up in {@link LayoutContainerPanel}. Stronly recommended not to alter.*/
	private final double HARDWARE_WIDTH_ALLOCATION = 1/6.0;
	/**Proportion of vertical space this box will take up in {@link LayoutContainerPanel}. Stronly recommended not to alter.*/
	private final double HARDWARE_HEIGHT_ALLOCATION = 1/3.25;
	
	/**Horizontal margin around chart area when placed in panel. Strongly recommended not to alter.*/
	private final int XMARGIN = 35;
	/**Vertical margin around chart area when placed in panel. Strongly recommended not to alter.*/
	private final int YMARGIN = 30;
	/**X-coor of upper left corner of {@link #chart}. Strongly recommended not to alter.*/
	private final int CHARTX = 30;
	/**Y-coor of upper left corner of {@link #chart}. Strongly recommended not to alter.*/
	private final int CHARTY = 20;
	/**Space, in pixels, between outline of battery and temperature rectangles and the colored bars within.*/
	private final int BAR_MARGIN = 2;
	/**X-coor of left edge of temperature empty rectangle. Strongly recommended not to alter.*/
	//private final int TEMP_LEFT_EDGE = ImageHandler.HARDWARE_TEMP_LEFT_EDGE + BAR_MARGIN;
	/**Width, in pixels, of temperature empty rectangle.*/
	//private final int TEMP_WIDTH = ImageHandler.HARDWARE_TEMP_WIDTH - 2*BAR_MARGIN;
	/**X-coor of left edge of battery empty rectangle.*/
	//private final int BATT_LEFT_EDGE = ImageHandler.HARDWARE_BATT_LEFT_EDGE + BAR_MARGIN;
	/**Width, in pixels, of battery empty rectangle.*/
	//private final int BATT_WIDTH = ImageHandler.HARDWARE_BATT_WIDTH - 2*BAR_MARGIN;
	/**Y-coor of bottom edge of temperature and battery empty rectangles.*/
	//private final int BOTTOM_EDGE = ImageHandler.HARDWARE_BOTTOM_EDGE;
	
	
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
	
	/**Color for temperature bar*/
	//private final Color TEMP_COLOR = new Color(207, 46, 46, 125); //reddish, transparent
	/**Color for battery bar*/
	//private final Color BATT_COLOR = new Color(36, 149, 176, 125); //bluish, transparent
	
	/**Value of motor temperature that's displayed in the graph*/ 
	private int temp;
	/**Value of battery level that's displayed in the graph*/
	private int batt; 
	
	/**Constructor sets preferred size to tell layout manager of {@link LayoutContainerPanel} how to draw this panel;
    Initializes chart size variables.
    @param widthOfContainer used to set {@link #width}
    @param heightOfContainer used to set {@link #height}*/
	public HardwareBox(int widthOfContainer, int heightOfContainer){
		
		
		width = (int)(widthOfContainer*HARDWARE_WIDTH_ALLOCATION);
		height = (int)(heightOfContainer*HARDWARE_HEIGHT_ALLOCATION);
		
		
		setPreferredSize(new Dimension(width, height));
		setBackground(GibbotGUI3.GLOBAL_BG);
		
		//w = width - 2*XMARGIN;
		//h = height - 2*YMARGIN;
		//xscale = w/(double)(ImageHandler.HARDWARE_WIDTH);
		//yscale = h/(double)(ImageHandler.HEIGHT);
		
		
		GUITimer.addActionListener(this);
	}
	
	/**Override of {@link javax.swing.JComponent#paintComponent}. super.paintComponent() call fills background color.
    This is what is executed whenever repaint() is called in the program. 
    Calls {@link #drawTab} to draw containing rectangle and shadow, draws chart image, 
    then draws bars to represent battery level and motor temperature.
    @param g Graphics context for drawing. Kind of a black box; gets handled in the background somehow
     */ 
	public void paintComponent(Graphics g){
		//drawTab(width, height-CHARTY, g);
		
		//thermometer
		g.drawImage(thermometer, 5, 15, 180, 180, this); //image, x coor, y coor, x size, y size, this
		
		/*
		super.paintComponent(g);
		drawTab(width, height - CHARTY, g);
		g.drawImage(chart, CHARTX, CHARTY, w, h, this);
		
		g.setColor(TEMP_COLOR);
		g.fillRect((int)(CHARTX + xscale*TEMP_LEFT_EDGE) + 1, (int)(CHARTY + yscale*BOTTOM_EDGE) - temp, 
			(int)(xscale*TEMP_WIDTH) - 1, temp - BAR_MARGIN); // +/- 1 to adjust placement
		g.setColor(BATT_COLOR);
		g.fillRect((int)(CHARTX + xscale*BATT_LEFT_EDGE) + 1, (int)(CHARTY + yscale*BOTTOM_EDGE) - batt, 
			(int)(xscale*BATT_WIDTH) - 1, batt - BAR_MARGIN); // +/- 1 to adjust placement
		 */
	}
	
	/**Gets battery and temperature values from {@link GUISerialPort#data}. Called by {@link #actionPerformed}.
	*/
	public void updateForDrawing(){
	
		/*
		int[] data = GUISerialPort.getData();	
	
		batt = data[3]; 
		temp = data[2]; 
		*/
		HashMap<String, Integer> data = GUISerialPort.getData();	
		
		batt = data.get("batteryVoltage"); 
		temp = data.get("motorTemperature"); 
			
	}
			
	/**Draws the containing rectangle and shadow. Called by Called by {@link #paintComponent}.
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