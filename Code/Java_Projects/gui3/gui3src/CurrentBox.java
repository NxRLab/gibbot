
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**CurrentBox displays current and torque as an animated line graph with a double y-axis.
 *Stores points in two different arrays and updates/draws them alternatively 
 *depending on the value of the par (parity) variable - which is either zero or
 *one. This was done to cut back on lengthy array updating functions.
 */
public class CurrentBox extends JPanel implements ActionListener{

    private Image chart = ImageHandler.getImage("currentChart");
    
    /**Specified by LayoutContainerPanel parent. Used to set preferred dimensons in constructor*/
	private int height;
	/**Specified by LayoutContainerPanel parent. Used to set preferred dimensons in constructor*/
	private int width;
	
    /**Width for drawing chart image*/
    private int w;
    /**Height for drawing chart image*/
	private int h;
		
	/**Horizontal scale for drawing chart image (not really needed unless {@link GUILayeredPane#DRAWING_WIDTH} is altered)*/
	private double xscale;
	/**Vertical scale for drawing chart image (not really needed unless {@link GUILayeredPane#DRAWING_HEIGHT} is altered)*/
	private double yscale;
	
	/**Proportion of horizontal space this box will take up in {@link LayoutContainerPanel}. Stronly recommended not to alter.*/
	private final double CURRENT_WIDTH_ALLOCATION = .25;
	/**Proportion of vertical space this box will take up in {@link LayoutContainerPanel}. Stronly recommended not to alter.*/
	private final double CURRENT_HEIGHT_ALLOCATION = 1/3.25;
	
	/**Horizontal margin around chart area when placed in panel. Strongly recommended not to alter.*/
	private final int XMARGIN = 35;
	/**Vertical margin around chart area when placed in panel. Strongly recommended not to alter.*/
	private final int YMARGIN = 30;
	/**X-coor of upper left corner of {@link #chart}. Strongly recommended not to alter.*/
	private final int CHARTX = 25;
	/**Y-coor of upper left corner of {@link #chart}. Strongly recommended not to alter.*/
	private final int CHARTY = 20;
	/**X-coor of the left origin of the gray graph plane area on current graphic.*/
	private final int PLANE_XORIGIN = ImageHandler.CURRENT_PLANE_XORIGIN;
	/**Y-coor of the left origin of the gray graph plane area on current graphic.*/
	private final int PLANE_YORIGIN = ImageHandler.CURRENT_PLANE_YORIGIN;
	
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
	
	/**Color of current axis label and line graph*/
	private final Color CURRENT_COLOR = new Color(207, 46, 46); //reddish
	/**Color of torque axis label and line graph*/
	private final Color TORQUE_COLOR = new Color(36, 149, 176); //bluish
	
	/**Y-coor values for current chart on even {@link #par} (see class notes)*/
	private int[] milliampsE;
	/**Y-coor values for current chart on odd {@link #par} (see class notes)*/
	private int[] milliampsO;
	/**Y-coor values for torque chart on even {@link #par} (see class notes)*/	
	private int[] millinewtmetsE;
	/**Y-coor values for torque chart on odd {@link #par} (see class notes)*/
	private int[] millinewtmetsO;
	/**X-coor values for all charts*/
	private int[] t; 
	/**Number of points drawn (determined by width available for chart image)*/ 
	private int n;
	/**Tracks which arrays to draw/update (even or odd)*/ 
	private int par;  
	
	/**Constructor sets preferred size to tell layout manager of {@link LayoutContainerPanel} how to draw this panel;
    Initializes chart size variables as well as {@link #milliampsE}, {@link #milliampsO}, {@link #millinewtmetsE}, 
    and {@link #millinewtmetsO} (all to 0).
    @param widthOfContainer used to set {@link #width}
    @param heightOfContainer used to set {@link #height}*/
	public CurrentBox(int widthOfContainer, int heightOfContainer){
		
		width = (int)(widthOfContainer*CURRENT_WIDTH_ALLOCATION);
		height = (int)(heightOfContainer*CURRENT_HEIGHT_ALLOCATION);
		
		setPreferredSize(new Dimension(width, height));
    	setBackground(GibbotGUI3.GLOBAL_BG);
		
		w = width - 2*XMARGIN;
		h = height - 2*YMARGIN;
		xscale = w/(double)(ImageHandler.CURRENT_WIDTH);
		yscale = h/(double)(ImageHandler.HEIGHT);
		n = (int)((ImageHandler.CURRENT_PLANE_WIDTH + 10)*xscale/10); //points drawn 10 pixles apart. + 10 to put last point on right axis 
		
		milliampsE = new int[n];
		milliampsO = new int[n];
		millinewtmetsE = new int[n];
		millinewtmetsO = new int[n];
		t = new int[n];
		par = 0;
		
		for(int i = 0; i < n; i++){
			milliampsE[i] = CHARTY + (int)(PLANE_YORIGIN*yscale); 
			milliampsO[i] = CHARTY + (int)(PLANE_YORIGIN*yscale);
			millinewtmetsE[i] = CHARTY + (int)(PLANE_YORIGIN*yscale);
			millinewtmetsO[i] = CHARTY + (int)(PLANE_YORIGIN*yscale);
			t[i] = 10*i + CHARTX + (int)(PLANE_XORIGIN*xscale);  
		}
		
		GUITimer.addActionListener(this);
	}
	
	/**Override of {@link javax.swing.JComponent#paintComponent}. super.paintComponent() call fills background color.
    This is what is executed whenever repaint() is called in the program. 
    Calls {@link #drawTab} to draw containing rectangle and shadow, draws chart image, then draws line graphs for current and torque. 
    @param g Graphics context for drawing. Kind of a black box; gets handled in the background somehow
     */ 
	public void paintComponent(Graphics g){
		
		super.paintComponent(g);
		drawTab(width, height - CHARTY, g);	
		g.drawImage(chart, CHARTX, CHARTY, w, h, this);
			
		if(par == 0){
			g.setColor(CURRENT_COLOR);
    		g.drawPolyline(t, milliampsE, n);
	   		g.setColor(TORQUE_COLOR);
    		g.drawPolyline(t, millinewtmetsE, n);
		}    	
    	else{
    		g.setColor(CURRENT_COLOR);
    		g.drawPolyline(t, milliampsO, n);
    		g.setColor(TORQUE_COLOR);
    		g.drawPolyline(t, millinewtmetsO, n);	
    	}
	}
	
	/**Gets current and torque values from {@link GUISerialPort#data} and updates {@link #milliampsE}, {@link #milliampsO},
	 *{@link #millinewtmetsE}, and {@link #millinewtmetsO}. Called by {@link #actionPerformed}.
	*/
	public void updateForDrawing(){
		
		int[] data = GUISerialPort.getData();
			
		int newCurr = CHARTY + (int)(PLANE_YORIGIN*yscale) - data[0];
		int newTor = CHARTY + (int)(PLANE_YORIGIN*yscale) -  data[1];
		
		if(par == 0){
			par = 1;
			milliampsE[0] = newCurr;
			millinewtmetsE[0] = newTor;
    	
    		for(int i = 0; i<n-2; i++){
    			milliampsE[i+1] = milliampsO[i];
	   			millinewtmetsE[i+1] = millinewtmetsO[i];
    		}
		}
	   	else{
    		par = 0;
    		milliampsO[0] = newCurr;
			millinewtmetsO[0] = newTor;
    
    		for(int i = 0; i<n-2; i++){
   				milliampsO[i+1] = milliampsE[i];
    			millinewtmetsO[i+1] = millinewtmetsE[i];
   			}
		}

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