
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
	public CurrentBox current;
	/**hardware is declared public for access by {@link GUILayeredPane} for enabling/disabling*/
	public HardwareBox hardware;
	/**speed is declared public for access by {@link GUILayeredPane} for enabling/disabling*/
	public SpeedometerBox speed;
	/**text is declared public for access by {@link GUILayeredPane} for enabling/disabling*/
	public TextBox text;
	
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
    	c.weightx = .25;
    	add(text, c);
    	
    	
    	speed = new SpeedometerBox(drawingWidth, drawingHeight);
    	c.gridx = 1;
    	c.gridy = 1;
    	c.weightx = .33;
    	add(speed, c);
    	
    	hardware = new HardwareBox(drawingWidth, drawingHeight);
    	c.gridx = 2;
    	c.gridy = 1;
    	c.weightx = .16;
    	add(hardware, c);
    	
    	current = new CurrentBox(drawingWidth, drawingHeight);
    	c.gridx = 3;
    	c.gridy = 1;
    	c.weightx = .25;
    	add(current, c);
    	
    }
}

