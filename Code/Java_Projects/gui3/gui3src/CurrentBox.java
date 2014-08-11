
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
    
    /**Width for drawing chart image (not really needed unless parameters of setBounds() call in {@link GUILayeredPane#GUILayeredPane} are altered)*/
    private int w;
    /**Height for drawing chart image (not really needed unless parameters of setBounds() call in {@link GUILayeredPane#GUILayeredPane} are altered)*/
	private int h;
	/**Horizontal scale for drawing chart image (not really needed unless parameters of setBounds() call in {@link GUILayeredPane#GUILayeredPane} are altered)*/
	private double xscale;
	/**Vertical for drawing chart image (not really needed unless parameters of setBounds() call in {@link GUILayeredPane#GUILayeredPane} are altered)*/
	private double yscale;
	
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
		
		width = widthOfContainer/4;
		height = (int)(heightOfContainer/3.25);
		
		setPreferredSize(new Dimension(width, height));
    	setBackground(GibbotGUI3.globalBg);
		
		w = (int)width -70;
		h = height-60;
		xscale = w/254.0;
		yscale = h/185.0;
		n = (int)(200*xscale/10); //points drawn 10 pixles apart
		
		milliampsE = new int[n];
		milliampsO = new int[n];
		millinewtmetsE = new int[n];
		millinewtmetsO = new int[n];
		t = new int[n];
		par = 0;
		
		for(int i = 0; i < n; i++){
			milliampsE[i] = 20 + (int)(93*yscale); //replace 20 w/ y coor where chart image is drawn
			milliampsO[i] = 20 + (int)(93*yscale);
			millinewtmetsE[i] = 20 + (int)(93*yscale);
			millinewtmetsO[i] = 20 + (int)(93*yscale);
			t[i] = 10*i + 25 + (int)(26*xscale);  //replace 25 w/ x coor where chart image is drawn
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
		drawTab(width, height - 20, g);	
		g.drawImage(chart, 25, 20, w, h, this);
			
		if(par == 0){
			g.setColor(new Color(207, 46, 46));
    		g.drawPolyline(t, milliampsE, n);
	   		g.setColor(new Color(36, 149, 176));
    		g.drawPolyline(t, millinewtmetsE, n);
		}    	
    	else{
    		g.setColor(new Color(207, 46, 46));
    		g.drawPolyline(t, milliampsO, n);
    		g.setColor(new Color(36, 149, 176));
    		g.drawPolyline(t, millinewtmetsO, n);	
    	}
	}
	
	/**Gets current and torque values from {@link GUISerialPort#data} and updates {@link #milliampsE}, {@link #milliampsO},
	 *{@link #millinewtmetsE}, and {@link #millinewtmetsO}. Called by {@link #actionPerformed}.
	*/
	public void updateForDrawing(){
		
		int[] data = GUISerialPort.getData();
			
		int newCurr = 20 + (int)(93*yscale) - data[0];
		int newTor = 20 + (int)(93*yscale) -  data[1];
		
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