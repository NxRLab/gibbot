
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**GUILayeredPane is the highest panel in this GUI's hierarchy (contained by an instance of a {@link GibbotGUI3} frame).
 * Handles switching between "awake" and "asleep" views (right now with a button, 
 *eventually with a serial signal sent to indicate that battery needs to be recharges).
 *Note that change panel only exists to hold this buttons. 
 *If screen view size needs to be adjusted, this is the place to do it. Alter {@link SIZING_WIDTH} or {@link SIZING_HEIGHT} 
 *within specified ranges. If that is not sufficient, minor changes to {@link DRAWING_WIDTH} or {@link DRAWING_HEIGHT} can 
 *be made, though this will decrease the quality of some graphics.
 *
 *This panel updates serial data through {@link GUISerialPort} at frequency set by {@link GUITimer}.
 */ 
public class GUILayeredPane extends JLayeredPane implements ActionListener{
	
	/**Width of rectangle drawn on: avoid altering!*/
	private final int DRAWING_WIDTH = 1300;
	/**Height of rectangle drawn on: avoid altering!*/
	private final int DRAWING_HEIGHT = 800;
	/**Width of screen: adjust as neccesary. Suggested range: 1320 - 1420 (designed for 1366)*/
	private final int SIZING_WIDTH = 1366;
	/**Height of screen: adjust as neccesary. Suggested range: 685 - 775 (designed for 775)*/	
	private final int SIZING_HEIGHT = 775;
	
	/**The panel containing "awake mode" content*/
	private LayoutContainerPanel awake;
	/**The panel containing "asleep mode" content*/
	private LayoutContainerPanel2 asleep;
	
	JPanel change = new JPanel();//wouldn't be in final version
	JButton b2 = new JButton("switch modes");//wouldn't be in final version
	
	/**Used for serial data updates*/
	private int timerCount = 0;
	/**Used for serial data updates*/
	private int factor = GUITimer.getSerialFactor();
	/**Minimum value for battery before changing to sleep mode (may not be needed if another kind of signal is used)*/
	private final int MIN_BATTERY = 0; //???
	/**Maximum value for battery before changing to awake mode (may not be needed if another kind of signal is used)*/
	private final int MAX_BATTERY = 100; //???
   
    /**Constructor method adds panels and sets bounds on them to fit screen size. Also adds this panel as an 
    ActionListener for {@link GUITimer}.*/
    public GUILayeredPane() {
    	
    	awake = new LayoutContainerPanel(DRAWING_WIDTH, DRAWING_HEIGHT, SIZING_WIDTH, SIZING_HEIGHT); //don't change these parameters unless very necessary!
    	//awake = new LayoutContainerPanel(1300, 800, 1366, 775);
    	awake.setOpaque(true);
    	awake.setBounds(0, 0, SIZING_WIDTH, SIZING_HEIGHT); //first two parameters are (x, y) of the upper left corner. These can
    														//also be adjusted, including to negative values. They don't affect the 
    														//internal coordinates of awake and asleep panels.
    	
    	add(awake, new Integer(0));
    	
    	asleep = new LayoutContainerPanel2(SIZING_WIDTH);
    	asleep.setOpaque(false);
    	asleep.setVisible(false);
    	asleep.setBounds(0, 0, SIZING_WIDTH, SIZING_HEIGHT);
    	
    	add(asleep, new Integer(1));
    	
    	ButtonHandler listener = new ButtonHandler();//wouldn't be in final version
    	b2.addActionListener(listener);//wouldn't be in final version
    	
    	change.setBounds(0, 0, SIZING_WIDTH, SIZING_HEIGHT);//wouldn't be in final version
    	change.add(b2); //wouldn't be in final version
    	change.setOpaque(false);//wouldn't be in final version
    	
    	add(change, new Integer(2));//wouldn't be in final version
    	
    	GUITimer.addActionListener(this);
    }
    
    /**Specifies how to respond to timer events from {@link GUITimer}. This panel uses events as a signal
    to update serial data via {@link GUISerialPort}, and would be the place to implement some signal to 
    indicate the panel needs to switch from awake to asleep mode/ vice versa.
    @param evt The timer event (not important to code but required by {@link java.awt.event#ActionListener} interface)
    */
    public void actionPerformed(ActionEvent evt){

		    if(timerCount % factor == (factor - 1)){	
    			GUISerialPort.update();
    			timerCount = 0;
    			if(GUISerialPort.getData()[6] < MIN_BATTERY || GUISerialPort.getData()[6] > MAX_BATTERY){ //or some other signal
    			//{copy and paste content of actionPerformed() method from ButtonHandler}
    			}
		    }	
	    	  else
    	  		timerCount++;
      		}
      		
    /**Right now ButtonHandler specifies how to switch between awake and asleep modes.*/
    public class ButtonHandler implements ActionListener { //wouldn't be in final version
    	
    	/**Specifies how to respond to button click. Code from this method can be copy/pasted 
    	into GUILayeredPane's {@link GUILayeredPane#actionPerformed} method when battery 
    	signal is figured out.
    	@param evt The timer event (not important to code but required by {@link java.awt.event#ActionListener} interface)
    	*/
    	public void actionPerformed(ActionEvent evt){    			
    		awake.setEnabled(awake.isEnabled() ? false : true);
    		if(!awake.isEnabled()){
    			awake.bananapan.removeMouseListener(awake.bananapan);
    		}
    		else{
    			awake.bananapan.addMouseListener(awake.bananapan);
    			asleep.resetTabs();
    		}
    		
    		asleep.setEnabled(asleep.isEnabled() ? false : true);
    		asleep.setVisible(asleep.isVisible() ? false : true);
    	}
    }
    
}