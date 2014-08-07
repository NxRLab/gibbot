
/*GUILayeredPane is the highest panel in this GUI's hierarchy (contained by an instance of a {@link GibbotGUI3} frame).
 * Handles switching between "awake" and "asleep" views (right now with a button, 
 *eventually with a serial signal sent to indicate that battery needs to be recharges).
 *Note that change panel only exists to hold this buttons. 
 *If screen view size needs to be adjusted, this is the place to do it, with the 
 *setBounds() calls on awake and asleep objects in the constructor code. If this causes cut-offs, 
 *minor changes on setSize() params in GibbotGUI3 can be made.
 *
 *This panel updates serial data at frequency set by {@link GUITimer}.
 */ 

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class GUILayeredPane extends JLayeredPane implements ActionListener{
	
	/*The panel containing "awake mode" content*/
	private LayoutContainerPanel awake;
	/*The panel containing "asleep mode" content*/
	private LayoutContainerPanel2 asleep;
	
	JPanel change = new JPanel();//wouldn't be in final version
	JButton b2 = new JButton("switch modes");//wouldn't be in final version
	
	/*Used for serial data updates*/
	private int timerCount = 0;
	/*Used for serial data updates*/
	private int factor = GUITimer.getSerialFactor();
	/*Minimum value for battery before changing to sleep mode (may change if another kind of signal is used*/
	private final int MIN_BATTERY = 0; //???

    
    
    public GUILayeredPane() {
    	
    	awake = new LayoutContainerPanel(1300, 800);
    	awake.setOpaque(true);
    	awake.setBounds(0, 0, 1366, 775);
    	
    	add(awake, new Integer(0));
    	
    	asleep = new LayoutContainerPanel2(1300, 850);
    	asleep.setOpaque(false);
    	asleep.setVisible(false);
    	asleep.setBounds(0, 0, 1366, 775);
    	
    	add(asleep, new Integer(1));
    	
    	ButtonHandler listener = new ButtonHandler();//wouldn't be in final version
    	b2.addActionListener(listener);//wouldn't be in final version
    	
    	change.setBounds(0, 0, 1366, 750);//wouldn't be in final version
    	change.add(b2); //wouldn't be in final version
    	change.setOpaque(false);//wouldn't be in final version
    	
    	add(change, new Integer(2));//wouldn't be in final version
    	
    	GUITimer.addActionListener(this);
    }
    
    public void actionPerformed(ActionEvent evt){

		    if(timerCount % factor == (factor - 1)){	
    			GUISerialPort.update();
    			timerCount = 0;
    			if(GUISerialPort.getData()[6] < MIN_BATTERY){} //or some other signal
    			//{copy and paste content of actionPerformed() method from ButtonHandler}
    			
    			//Can insert another test into this if statement to conversely see if the 
    			//battery is done charging; not sure what this would look like yet.
		    }	
	    	  else
    	  		timerCount++;
      		}
    
    public class ButtonHandler implements ActionListener { //wouldn't be in final version
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