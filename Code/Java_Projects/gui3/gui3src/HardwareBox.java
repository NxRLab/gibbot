
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**HardwareBox displays motor temperature and battery life in a bar chart graphic
 */
public class HardwareBox extends JPanel implements ActionListener{
	
	private Image chart = ImageHandler.getImage("hardwareChart");

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
	
	/**Value of battery level that's displayed in the graph*/
	private int batt;
	/**Value of motor temperature that's displayed in the graph*/ 
	private int temp; 
	
	/**Constructor sets preferred size to tell layout manager of {@link LayoutContainerPanel} how to draw this panel;
    Initializes chart size variables.
    @param widthOfContainer used to set {@link #width}
    @param heightOfContainer used to set {@link #height}*/
	public HardwareBox(int widthOfContainer, int heightOfContainer){
		
		width = widthOfContainer/6;
		height = (int)(heightOfContainer/3.25);
		setPreferredSize(new Dimension(width, height));
		setBackground(GibbotGUI3.globalBg);
		w = width - 70;
		h = height - 60;
		xscale = w/146.0;
		yscale = h/185.0;
		GUITimer.addActionListener(this);
	}
	
	/**Override of {@link javax.swing.JComponent#paintComponent}. super.paintComponent() call fills background color.
    This is what is executed whenever repaint() is called in the program. 
    Calls {@link #drawTab} to draw containing rectangle and shadow, draws chart image, 
    then draws bars to represent battery level and motor temperature.
    @param g Graphics context for drawing. Kind of a black box; gets handled in the background somehow
     */ 
	public void paintComponent(Graphics g){
		
		super.paintComponent(g);
		drawTab(width, height - 20, g);
		g.drawImage(chart, 30, 20, w, h, this);
		
		g.setColor(new Color(207, 46, 46, 125));
		g.fillRect((int)(30 + xscale*20) + 1, (int)(20 + yscale*144) - temp, (int)(xscale*21)-1, temp-2);
		g.setColor(new Color(36, 149, 176, 125));
		g.fillRect((int)(30 + xscale*78) + 1, (int)(20 + yscale*144) - batt, (int)(xscale*44)-1, batt-2);

	}
	
	/**Gets battery and temperature values from {@link GUISerialPort#data}. Called by {@link #actionPerformed}.
	*/
	public void updateForDrawing(){
	
		int[] data = GUISerialPort.getData();	
	
		batt = data[3]; 
		temp = data[2]; 
			
	}
			
	/**Draws the containing rectangle and shadow. Called by Called by {@link #paintComponent}.
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