
import javax.swing.*;
import java.awt.*;

/**LayoutContainerPanel is the "awake" view of the GUI. Basically just handles layout for
 *all subpanels in that view: {@link BananaPanel1}, {@link TextBox}, {@link SpeedometerBox}, {@link HardwareBox},
 *and {@link CurrentBox} instances. Values for c.weightx and c.weighty for the most part reflect ALLOCATION constants
 *in all "Box" classes and should not be altered.
 */
public class LayoutContainerPanel extends JPanel{
	
	/**Specified by GUILayeredPane parent. Used to communicate available space to child components*/
	private int drawingHeight;
	/**Specified by GUILayeredPane parent. Used to communicate available space to child components*/
	private int drawingWidth;

	/**bananapan is declared public for access by {@link GUILayeredPane} for enabling/disabling*/
	public BananaPanel1 bananapan;
	/**current is declared public for access by {@link GUILayeredPane} for enabling/disabling*/
	public TorqueBox torque;
	/**hardware is declared public for access by {@link GUILayeredPane} for enabling/disabling*/
	public TemperatureBox temperature;
	/**speed is declared public for access by {@link GUILayeredPane} for enabling/disabling*/
	public SpeedometerBox speed;
	/**text is declared public for access by {@link GUILayeredPane} for enabling/disabling*/
	public TextBox text;
	
	//public BatteryBox battery;
	
	/**Tells layout manager where to position child components */
	GridBagConstraints c;

	/**Configures layout and adds child components.
	 @param drawW used to set {@link #drawingWidth}
     @param drawH used to set {@link #drawingHeight}
	 @param sizeW only used to pass to {@link BananaPanel1#BananaPanel1}; comes from {@link GUILayeredPane}.
	 @param sizeH only used to pass to {@link BananaPanel1#BananaPanel1}; comes from {@link GUILayeredPane}.*/
    public LayoutContainerPanel(int drawW, int drawH, int sizeW, int sizeH) {
    	
    	setBackground(GibbotGUI3.GLOBAL_BG);
    	setLayout(new GridBagLayout());
    	drawingWidth=drawW-1;
    	drawingHeight=drawH-1;
    	
    	bananapan = new BananaPanel1((int)(drawingWidth*2/3), (int)(drawingHeight*2/3), sizeW, sizeH);
    	
    	c = new GridBagConstraints();
    	//c.gridwidth = GridBagConstraints.REMAINDER;
    	
    	c.gridx=0;
    	c.gridy=0;
    	c.gridwidth=4;
    	c.gridheight=1;
    	c.weighty = .55;
    	c.weightx = 1;
    	c.fill=GridBagConstraints.BOTH;
    	add(bananapan,c);
    	
    	c.weighty = .3;
    	c.gridwidth = 1;
    	c.anchor = GridBagConstraints.SOUTH;
    	
    	text = new TextBox(drawingWidth, drawingHeight);
    	c.gridx = 0;
    	c.gridy = 1;
    	c.weightx = 0.8;//0.80
    	c.weighty = 0.31;//0.40
    	add(text, c);
    	
    	
    	speed = new SpeedometerBox(drawingWidth, drawingHeight);
    	c.gridx = 1;
    	c.gridy = 1;
    	//c.gridwidth = 1;
    	//c.gridwidth = GridBagConstraints.REMAINDER;
    	c.weightx = 0.33; //0.33
    	add(speed, c);
    	
    	
    	temperature = new TemperatureBox(drawingWidth, drawingHeight);
    	//temperature.setOpaque(false);
    	c.gridx = 2;
    	c.gridy = 1;
    	c.weightx = 0.16; //0.16
    	add(temperature, c);
    	
    	//c.gridwidth = 1;
    	torque = new TorqueBox(drawingWidth, drawingHeight);
    	c.gridx = 3;
    	c.gridy = 1;
    	c.weightx = 0.25; //0.25
    	add(torque, c);
    	
    }
}

