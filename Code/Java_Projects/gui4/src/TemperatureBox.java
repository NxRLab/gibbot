
import java.awt.*;
import java.awt.event.*;
import java.util.HashMap;

import javax.swing.*;
import javax.swing.JFrame;

/**HardwareBox displays motor temperature and battery life in a bar chart graphic
 */
public class TemperatureBox extends JPanel implements ActionListener{
	
	private Image thermometer = ImageHandler.getImage("thermometer.png");
	private final Font ANDALE_BIG = ImageHandler.getAndaleFont().deriveFont(Font.BOLD, 30);
	//private final Font ANDALE_SMALL = ImageHandler.getAndaleFont().deriveFont(Font.BOLD, 20);
	private final Color TEMPERATURE_COLOR = Color.RED;
	private final int TEMP_MAX = 100; //CHANGE WHEN YOU KNOW
	private int timer = 0;
	
    /**Specified by LayoutContainerPanel parent. Used to set preferred dimensions in constructor*/
	private int height;
	/**Specified by LayoutContainerPanel parent. Used to set preferred dimensions in constructor*/
	private int width;
	
	/**Proportion of horizontal space this box will take up in {@link LayoutContainerPanel}. Stronly recommended not to alter.*/
	private final double HARDWARE_WIDTH_ALLOCATION = 1/6.0;
	/**Proportion of vertical space this box will take up in {@link LayoutContainerPanel}. Stronly recommended not to alter.*/
	private final double HARDWARE_HEIGHT_ALLOCATION = 1/3.25;
	
	/**Value of motor temperature that's displayed in the graph*/ 
	private int temp;
	
	/**Constructor sets preferred size to tell layout manager of {@link LayoutContainerPanel} how to draw this panel;
    Initializes chart size variables.
    @param widthOfContainer used to set {@link #width}
    @param heightOfContainer used to set {@link #height}*/
	public TemperatureBox(int widthOfContainer, int heightOfContainer){
		
		
		width = (int)(widthOfContainer*HARDWARE_WIDTH_ALLOCATION);
		height = (int)(heightOfContainer*HARDWARE_HEIGHT_ALLOCATION);
		
		
		setPreferredSize(new Dimension(width, height));
		setBackground(GibbotGUI3.GLOBAL_BG);
		
		temp = 0; //fahrenheit for now
		
		
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
		
		//thermometer
		int upperX = (int)(width*0.337);//70px
		int upperY = (int)(height*0.043);//10px
		int sizeX = (int)(upperX*1.22);//85px
		int sizeY = (int)(upperY*16);//160px
		
		
		g.drawImage(thermometer, upperX, upperY, sizeX, sizeY, this); //image, x coor, y coor, x size, y size, this
		g.setColor(TEMPERATURE_COLOR);
		
		//base circle for thermometer
		//int x, int y, int width, int length
		g.fillOval((int)(upperX*1.15), (int)(upperY*12), (int)(sizeX*0.518), (int)(sizeY*0.27));//80, 120, 44, 43
		
		//int x, int y,int width,int height
		if(temp < TEMP_MAX){
			g.fillRect((int)(upperX*1.3), (int)(upperY*12)-temp, (int)(sizeX*0.26), (int)(sizeY*0.032)+temp);//91, 120-temp, 22, 5+temp
			g.setColor(Color.BLACK);
			setFont(ANDALE_BIG);
			final String DEGREE  = "\u00b0";
			g.drawString(temp+DEGREE+"F", upperX, (int)(upperY*19.5));//70, 195
		}
		else{
			g.fillRect((int)(upperX*1.3), (int)(upperY*12)-TEMP_MAX, (int)(sizeX*0.26), (int)(sizeY*0.032)+TEMP_MAX);//91, 120-temp, 22, 5+temp
			g.fillOval((int)(upperX*1.29), (int)(upperY*1.8), (int)(sizeX*0.271), (int)(sizeY*0.132));//90, 18, 23, 21
			timer++;
		}
		
	}
	
	/**Gets battery and temperature values from {@link GUISerialPort#data}. Called by {@link #actionPerformed}.
	*/
	public void updateForDrawing(){
	
		HashMap<String, Integer> data = GUISerialPort.getData();	
		
		//temp = data.get("motorTemperature"); 
		
		if(BananaPanel1.getAnimating()){
			temp++;
		}
		
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