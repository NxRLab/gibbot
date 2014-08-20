/**
 * @(#)ScaleTextField.java
 *
 *
 * @author 
 * @version 1.00 2014/8/20
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ScaleTextField extends JTextField implements ActionListener{
	
	private int TAG;

    public ScaleTextField(String s, int i) {
    	
    	super(s);
    	TAG = i;
    	GraphArrayUpdater.graphChoices[i] = 1;
   		addActionListener(this);
    	
    }
    
    public void actionPerformed(ActionEvent evt){

   		ScaleTextField src = (ScaleTextField)evt.getSource();
   		String str = src.getText();
   		if(str.matches("-?\\d+(\\.\\d+)?")){
   			int i = TAG;
   			GraphArrayUpdater.graphChoices[i] = Integer.parseInt(str);
   		}
   		else
   			src.setText("Not a number");	
   }
    
    public int getTag(){
    	return TAG;
    }
    
}