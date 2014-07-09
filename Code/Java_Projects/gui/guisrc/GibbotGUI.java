/**
 * @(#)GibbotGUI.java
 *
 *
 * @author 
 * @version 1.00 2014/7/8
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*Sets up external window to display content*/
 
public class GibbotGUI extends JFrame {
    
    public static void main(String[] args) {
    	
    	final JFrame window = new JFrame();
    	LayoutContainerPanel content = new LayoutContainerPanel(1300, 800);
    	window.setLayout(null);
    	//window.setBackground(Color.BLACK);
    	window.setContentPane(content);
    	//window.setExtendedState(Frame.MAXIMIZED_BOTH);
    	window.setSize(1300,800);
    	window.setUndecorated(false);
      	window.setLocation(50,50);
      	window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      	//window.setResizable(false);
      	window.setVisible(true);
      	
    	
    }
}