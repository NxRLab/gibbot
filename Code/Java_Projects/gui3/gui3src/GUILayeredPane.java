/**
 * @(#)GUILayeredPane.java
 *
 *
 * @author 
 * @version 1.00 2014/8/1
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*The highest panel in this GUI's hierarchy. Handles switching between "awake"
 *and "asleep" views (right now with a button, eventually with a serial signal
 *sent to indicate that battery needs to be recharges). If screen view size needs to be
 *adjusted, this is the place to do it, with the setBounds() methods on awake and 
 *asleep objects. If this causes major cut-offs, minor changes in setSize() method of
 *GibbotGUI3 can be made.
 *
 *This panel updates serial data at frequency set by GUITimer, but doesn't do anything
 *with it, just makes updated data available to other components that do use it.
 */ 

public class GUILayeredPane extends JLayeredPane implements ActionListener{
	
	LayoutContainerPanel awake;
	LayoutContainerPanel2 asleep;
	JPanel change = new JPanel();
	JButton b2 = new JButton("switch modes");
	
	private int timerCount = 0;
	private int factor = GUITimer.getSerialFactor();

    public GUILayeredPane(int widthOfContainer, int heightOfContainer) {
    	
    	awake = new LayoutContainerPanel(1300, 800);
    	awake.setOpaque(true);
    	awake.setBounds(0, 0, 1366, 775);
    	
    	add(awake, new Integer(0));
    	
    	asleep = new LayoutContainerPanel2(1300, 850);
    	asleep.setOpaque(false);
    	asleep.setVisible(false);
    	asleep.setBounds(0, 0, 1366, 775);
    	
    	add(asleep, new Integer(1));
    	
    	ButtonHandler listener = new ButtonHandler();
    	b2.addActionListener(listener);
    	
    	change.setBounds(0, 0, 1366, 750);
    	change.add(b2);
    	change.setOpaque(false);
    	
    	add(change, new Integer(2));
    	
    	GUITimer.addActionListener(this);
    }
    
    public void actionPerformed(ActionEvent evt){

		      	if(timerCount % factor == (factor - 1)){
    		
    				GUISerialPort.update();
    				timerCount = 0;
	      		}
	    	  	
	    	  	else
    	  			timerCount++;
      		}
    
    public class ButtonHandler implements ActionListener {
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