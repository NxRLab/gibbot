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
    	//GraphArrayUpdater.scales[i] = 1;
   		addActionListener(this);
    	
    }
    
    public void actionPerformed(ActionEvent evt){

   		ScaleTextField src = (ScaleTextField)evt.getSource();
   		String str = src.getText();
   		if(str.matches("-?\\d+(\\.\\d+)?")){
   			int i = TAG;
   			GraphArrayUpdater.setScale(i, Double.parseDouble(str));
   		}
   		else
   			src.setText("NaN");	
   }
    
    public int getTag(){
    	return TAG;
    }
    
}