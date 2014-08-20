/**
 * @(#)ChoiceBox.java
 *
 *
 * @author 
 * @version 1.00 2014/8/18
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ChoiceBox extends JComboBox implements ActionListener{

   private final int TAG;
   
   public ChoiceBox(Object[] o, int i){
   	
   		super(o);
   		TAG = i;
   		GraphArrayUpdater.graphChoices[i] = 0;
   		addActionListener(this);
   }
   
   public int getTag(){
   	
   		return TAG;
   }
   
   public void actionPerformed(ActionEvent evt){
   	
   		ChoiceBox src = (ChoiceBox)evt.getSource();
   		int i = TAG;
   		GraphArrayUpdater.graphChoices[i] = (int)src.getSelectedItem();	
   }
    
}
