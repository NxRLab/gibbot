
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.util.HashMap;
import java.math.BigDecimal;

import javax.swing.*;

/**CurrentBox displays torque as an animated bicep.*/
public class TorqueBox extends JPanel implements ActionListener{
	
    private Image torque = ImageHandler.getImage("bicep.png");
    private final Font ANDALE_BIG;
    
    private double testTorqueLevel = 0;
    
    /**Curves used to draw muscle definition on the torque bicep*/
    QuadCurve2D q1 = new QuadCurve2D.Float();
    QuadCurve2D q2 = new QuadCurve2D.Float();
    QuadCurve2D q3 = new QuadCurve2D.Float();
    
    /**Specified by LayoutContainerPanel parent. Used to set preferred dimensions in constructor*/
	private int height;
	/**Specified by LayoutContainerPanel parent. Used to set preferred dimensions in constructor*/
	private int width;
	
	/**Proportion of horizontal space this box will take up in {@link LayoutContainerPanel}. Stronly recommended not to alter.*/
	private final double CURRENT_WIDTH_ALLOCATION = 0.25;
	/**Proportion of vertical space this box will take up in {@link LayoutContainerPanel}. Stronly recommended not to alter.*/
	private final double CURRENT_HEIGHT_ALLOCATION = 0.30;
	
	//USED FOR BETA TEST
	private int i = 0; 
	private int wait = 0;
	private int betaTest[] = {0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0};
	
	/**Constructor sets preferred size to tell layout manager of {@link LayoutContainerPanel} how to draw this panel;
    Initializes chart size variables as well as {@link #milliampsE}, {@link #milliampsO}, {@link #millinewtmetsE}, 
    and {@link #millinewtmetsO} (all to 0).
    @param widthOfContainer used to set {@link #width}
    @param heightOfContainer used to set {@link #height}*/
	public TorqueBox(int widthOfContainer, int heightOfContainer){
		
		width = (int)(widthOfContainer*CURRENT_WIDTH_ALLOCATION);
		height = (int)(heightOfContainer*CURRENT_HEIGHT_ALLOCATION);
		
		ANDALE_BIG = ImageHandler.getAndaleFont().deriveFont(Font.BOLD, (int)(width*0.096));
		
		setPreferredSize(new Dimension(width, height));
    	setBackground(GibbotGUI3.GLOBAL_BG);
    	setFont(ANDALE_BIG);
		
		GUITimer.addActionListener(this);
	}
	
	/**Override of {@link javax.swing.JComponent#paintComponent}. super.paintComponent() call fills background color.
    This is what is executed whenever repaint() is called in the program. 
    Calls {@link #drawTab} to draw containing rectangle and shadow, draws chart image, then draws line graphs for current and torque. 
    @param g Graphics context for drawing. Kind of a black box; gets handled in the background somehow
     */ 
	public void paintComponent(Graphics g){
		
		super.paintComponent(g);
		
		int upperX = (int)(width/5);
		int upperY = (int)(height/20);
		int size = (int)(width*0.6);
		
		
		g.drawImage(torque, upperX, upperY, size, size, this);
		
		Graphics2D g2 = (Graphics2D)g;
		g2.setStroke(new BasicStroke((int)testTorqueLevel));
		q1.setCurve((int)(upperX*1.4), (int)(upperY*9.2), (int)(upperX*1.35), (int)(upperY*11.9), (int)(upperX*1.73), (int)(upperY*12.8));
		q2.setCurve((int)(upperX*2.29), (int)(upperY*13.27), (int)(upperX*2.45), (int)(upperY*11), (int)(upperX*2.94), (int)(upperY*11));
		q3.setCurve((int)(upperX*3.18), (int)(upperY*9.64), (int)(upperX*3.42), (int)(upperY*9.18), (int)(upperX*3.5), (int)(upperY*7.36));
		g2.draw(q1);
		g2.draw(q2);
		g2.draw(q3);
		
		BigDecimal conversion = new BigDecimal(testTorqueLevel*(100/7));
	    conversion.setScale(4);
		g.drawString(conversion+"%", (int)(upperX*3.71), (int)(upperY*16.4));
		
	}
	
	/**Gets current and torque values from {@link GUISerialPort#data} and updates {@link #milliampsE}, {@link #milliampsO},
	 *{@link #millinewtmetsE}, and {@link #millinewtmetsO}. Called by {@link #actionPerformed}.
	*/
	public void updateForDrawing(){
		//testTorqueLevel = GUISerialPort.getData().get("motorTorque");
		//above will be used in live-updating
		
		if(BananaPanel1.getAnimating()){
			/*For beta test*/
			if(wait % 3 == 0){
				if(i >= betaTest.length){
					i = 0;
				}
				testTorqueLevel = betaTest[i];
				i++;
			}
			wait++;
		}
		else{
			testTorqueLevel = 0;
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