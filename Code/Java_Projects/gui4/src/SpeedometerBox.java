import java.awt.*;
import java.awt.event.*;
import java.util.HashMap;

import javax.swing.*;

/**SpeedometerBox is what it sounds like; shows the linear velocity of the two links with two different colored "needles"
 */
public class SpeedometerBox extends JPanel implements ActionListener{
	
	private Image batteryBar = ImageHandler.getImage("batteryBar.png");
	private final Font ANDALE_BIG = ImageHandler.getAndaleFont().deriveFont(Font.BOLD, 30);
	private final Font ANDALE_MED = ImageHandler.getAndaleFont().deriveFont(Font.BOLD, 27); //for 100% to be centered when displayed
	private final Font DIGITAL = ImageHandler.getDigitalFont().deriveFont(Font.BOLD, 65);
	
	private int batterySpent;
	private final int MAX_BATT = 136; //CHANGE THIS WHEN YOU KNOW
	
    /**Specified by LayoutContainerPanel parent. Used to set preferred dimensions in constructor*/
	private int height;
	/**Specified by LayoutContainerPanel parent. Used to set preferred dimensions in constructor*/
	private int width;
	
	/**Proportion of horizontal space this box will take up in {@link LayoutContainerPanel}. Strongly recommended not to alter.*/
	private final double SPEEDOMETER_WIDTH_ALLOCATION = 1/3.0; //was 1/3.0
	/**Proportion of vertical space this box will take up in {@link LayoutContainerPanel}. Strongly recommended not to alter.*/
	private final double SPEEDOMETER_HEIGHT_ALLOCATION = 1/3.25;
    
	/**Color of needle on the speedometer corresponding to first link. If altered, also alter 
	 *{@link Gibbot#ARM1COLOR} with same first three values (RGB) but no fourth parameter (alpha).*/
	public final Color ARM1COLOR = new Color(150, 150, 150); //100 was last
	/**Color of needle on the speedometer corresponding to second link. If altered, also alter 
	 *{@link Gibbot#ARM2COLOR} with same first three values (RGB) but no fourth parameter (alpha).*/
	public final Color ARM2COLOR = new Color(36, 149, 176); //125 was last
	
	/**Value of velocity for first link (primary board) that's displayed on the speedometer*/	
	private double arm1vel;
	/**Value of velocity for second link (secondary board) that's displayed on the speedometer*/ 
	private double arm2vel;
 
	
	/**Constructor sets preferred size to tell layout manager of {@link LayoutContainerPanel} how to draw this panel;
    Initializes chart size variables.
    @param widthOfContainer used to set {@link #width}
    @param heightOfContainer used to set {@link #height}*/
	public SpeedometerBox(int widthOfContainer, int heightOfContainer){
		
		width = (int)(widthOfContainer*SPEEDOMETER_WIDTH_ALLOCATION); //417px
		height = (int)(heightOfContainer*SPEEDOMETER_HEIGHT_ALLOCATION); //238px
		
		setPreferredSize(new Dimension(width, height));
		setBackground(GibbotGUI3.GLOBAL_BG);
		setFont(ANDALE_BIG);
		
		GUITimer.addActionListener(this);
		
		batterySpent = 0;
		arm1vel = 50; //test case
		arm2vel = 40; //test case
	}
	
	/**Override of {@link javax.swing.JComponent#paintComponent}. super.paintComponent() call fills background color.
    This is what is executed whenever repaint() is called in the program. 
    Calls {@link #drawTab} to draw containing rectangle and shadow, draws chart image, then draws needles in the appropriate place. 
    @param g Graphics context for drawing. Kind of a black box; gets handled in the background somehow
     */ 
	public void paintComponent(Graphics g){
		
		int MAX_BATT_HEIGHT = (int)(height*0.57); //135px
		super.paintComponent(g);
		
		/**Drawing arm1vel and arm2vel*/
		int arm1VelUpperX = (int)(width*0.05); //25px
		int arm1VelUpperY = (int)(height*0.252); //60px
		
		g.setFont(DIGITAL);
		g.setColor(ARM1COLOR);
		g.drawString(arm1vel + "mph", arm1VelUpperX, arm1VelUpperY);
		g.setColor(ARM2COLOR);
		g.drawString(arm2vel + "mph", arm1VelUpperX, (int)(arm1VelUpperY*2.667));
		
		
		/**Drawing battery bar*/
		
		int battBarUpperX = (int)(width*0.720); //300px
		int battBarUpperY = (int)(height*0.063); //15px
		g.drawImage(batteryBar, battBarUpperX, battBarUpperY, (int)(battBarUpperX*0.27), (int)(battBarUpperY*10.71), this); //80, 150
				
		g.setFont(ANDALE_BIG);
		if(batterySpent <= MAX_BATT){
			g.setColor(Color.GREEN);
			g.fillRect((int)(battBarUpperX*1.025), (int)(battBarUpperY*1.75)+batterySpent, (int)(width*0.161), MAX_BATT_HEIGHT-batterySpent);//307, 25+batterySpent, 67, MAX_BATT_HEIGHT-batterySpent
		}
		g.setColor(Color.BLACK);
		int batt_height = (int)(100*batterySpent/MAX_BATT_HEIGHT);
		if(batt_height == 0) { g.setFont(ANDALE_MED); }
		g.drawString(100-batt_height + "%", (int)(battBarUpperX*1.05), (int)(battBarUpperY*14));//100-batt_height + "%", 315, 195
		
		
	}
	
	/**Gets velocity values from {@link GUISerialPort#data}. Called by {@link #actionPerformed}.
	*/
	public void updateForDrawing(){
		
		HashMap<String, Integer> data = GUISerialPort.getData();
		if(BananaPanel1.getAnimating()){
			arm1vel++;
			arm2vel++;
			if(batterySpent < MAX_BATT){
				batterySpent++;
			}
		}
		
		
		//arm1vel = data.get("Gyroscope_Z_Primary")*Math.PI/180; //convert to radians
		//arm2vel = data.get("Gyroscope_Z_Secondary")*Math.PI/180; //convert to radians
			
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