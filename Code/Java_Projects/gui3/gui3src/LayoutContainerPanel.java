
import javax.swing.*;
import java.awt.*;

/**LayoutContainerPanel is the "awake" view of the GUI. Basically just handles layout for
 *all subpanels in that view: {@link BananaPanel1}, {@link TextBox}, {@link Speedometer}, {@link HardwareBox},
 *and {@link CurrentBox} instances.
 */
public class LayoutContainerPanel extends JPanel{
	
	/**Used to communicate available space to child components*/
	private int height;
	/**Used to communicate available space to child components*/
	private int width;

	/**bananapan is declared public for access by {@link GUILayeredPane} for enabling/disabling*/
	public BananaPanel1 bananapan;
	/**Tells layout manager where to position child components */
	GridBagConstraints c;

	/**Configures layout and adds child components.
	 @param widthOfContainer used to set {@link width}
     @param heightOfContainer used to set {@link height}*/

    public LayoutContainerPanel(int widthOfContainer, int heightOfContainer) {

    	setBackground(GibbotGUI3.globalBg);
    	setLayout(new GridBagLayout());
    	height=heightOfContainer-1;
    	width=widthOfContainer-1;
    	
    	bananapan = new BananaPanel1(width, height);
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
    	
    	TextBox text = new TextBox(width, height);
    	c.gridx = 0;
    	c.gridy = 1;
    	c.weightx = .25;
    	add(text, c);
    	
    	Speedometer speed = new Speedometer(width, height);
    	c.gridx = 1;
    	c.gridy = 1;
    	c.weightx = .33;
    	add(speed, c);
    	
    	HardwareBox hardware = new HardwareBox(width, height);
    	c.gridx = 2;
    	c.gridy = 1;
    	c.weightx = .16;
    	add(hardware, c);
    	
    	CurrentBox current = new CurrentBox(width, height);
    	c.gridx = 3;
    	c.gridy = 1;
    	c.weightx = .25;
    	add(current, c);
    }
}

