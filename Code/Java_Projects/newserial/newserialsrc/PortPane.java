/**
 * @(#)PortPane.java
 *
 *
 * @author 
 * @version 1.00 2014/7/8
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class PortPane extends JPanel {
	
	private String[] options;
	private JComboBox combo;
	
	public boolean buttonClicked;

    public PortPane(String[] ss) {
    	
    	super(new BorderLayout());
    	buttonClicked = false;
    	options = ss;
    	combo = new JComboBox(options);
    	add(combo, BorderLayout.NORTH);
    	add(new okButton(), BorderLayout.SOUTH);
    }
    
    public void paintComponent(Graphics g){
    	
    	super.paintComponent(g);
    }
    
    public class okButton extends JButton implements ActionListener {
    	
    	public okButton(){
    		
    		super("Set port");
    		addActionListener(this);
    	}
    	
    	public void actionPerformed(ActionEvent evt){
    		
    		buttonClicked = true;
    		System.out.println("clicked");
    	}
    
    }
    
    public String getDesiredMessage(){
    	
    	System.out.println("message passed");
    	return (String)combo.getSelectedItem();
    }
    
    
}