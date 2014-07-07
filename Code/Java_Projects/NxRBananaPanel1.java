/**
 * @(#)NxRBananaPanel1.java
 *
 * NxRBananaPanel1 application
 *
 * @author 
 * @version 1.00 2014/6/30
 */
 
import javax.swing.*;
import java.awt.*;

/*Sets up external window to display content*/

import java.awt.event.*;
 
public class NxRBananaPanel1 extends JFrame {
    
    public static void main(String[] args) {
    	
    	final JFrame window = new JFrame();
    	LayoutContainerPanel content = new LayoutContainerPanel(1300, 800);
    	window.setLayout(null);
    	window.setBackground(Color.WHITE);
    	/*window.addKeyListener(new KeyAdapter(){
    		public void keyTyped(KeyEvent evt) {	
    			if(evt.getKeyCode()==KeyEvent.VK_ESCAPE)
    				window.dispose();}
    	});*/
    	//BananaPanel1 content = new BananaPanel1();
    	window.setContentPane(content);
    	window.setExtendedState(Frame.MAXIMIZED_BOTH);
    	window.setSize(1300,800);
    	window.setUndecorated(false);
      	window.setLocation(50,50);
      	window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      	//window.setResizable(false);
      	window.setVisible(true);
      	
    	
    }
}

