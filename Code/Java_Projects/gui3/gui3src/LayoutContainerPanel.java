
import javax.swing.*;
import java.awt.*;

/**LayoutContainerPanel is the "awake" view of the GUI. Basically just handles layout for
 *all subpanels in that view: {@link BananaPanel1}, {@link TextBox}, {@link Speedometer}, {@link HardwareBox},
 *and {@link CurrentBox} instances.
 */
public class LayoutContainerPanel extends JPanel{
	
	/**Specified by GUILayeredPane parent. Used to communicate available space to child components*/
	private int drawingHeight;
	/**Specified by GUILayeredPane parent. Used to communicate available space to child components*/
	private int drawingWidth;

	/**bananapan is declared public for access by {@link GUILayeredPane} for enabling/disabling*/
	public BananaPanel1 bananapan;
	/**Tells layout manager where to position child components */
	GridBagConstraints c;

	/**Configures layout and adds child components.
	 @param drawW used to set {@link #drawingWidth}
     @param drawH used to set {@link #drawingHeight}
	 @param sizeW only used to pass to {@link BananaPanel1#BananaPanel1}; comes from {@link GUILayeredPane}.
	 @param sizeH only used to pass to {@link BananaPanel1#BananaPanel1}; comes from {@link GUILayeredPane}.*/
    public LayoutContainerPanel(int drawW, int drawH, int sizeW, int sizeH) {

    	setBackground(GibbotGUI3.globalBg);
    	setLayout(new GridBagLayout());
    	drawingHeight=drawH-1;
    	drawingWidth=drawW-1;
    	
    	bananapan = new BananaPanel1(drawingWidth, drawingHeight, sizeW, sizeH);
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
    	
    	TextBox text = new TextBox(drawingWidth, drawingHeight);
    	c.gridx = 0;
    	c.gridy = 1;
    	c.weightx = .25;
    	add(text, c);
    	
    	Speedometer speed = new Speedometer(drawingWidth, drawingHeight);
    	c.gridx = 1;
    	c.gridy = 1;
    	c.weightx = .33;
    	add(speed, c);
    	
    	HardwareBox hardware = new HardwareBox(drawingWidth, drawingHeight);
    	c.gridx = 2;
    	c.gridy = 1;
    	c.weightx = .16;
    	add(hardware, c);
    	
    	CurrentBox current = new CurrentBox(drawingWidth, drawingHeight);
    	c.gridx = 3;
    	c.gridy = 1;
    	c.weightx = .25;
    	add(current, c);
    }
}

