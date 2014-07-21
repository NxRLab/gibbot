/**
 * @(#)AccelSwipeTab.java
 *
 *
 * @author 
 * @version 1.00 2014/7/21
 */
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import javax.swing.*;
import jssc.*;

public class AccelSwipeTab extends SampleSwipeTab implements ContentSwipeTab, ActionListener {
	
	private double w;
	private double h;
	private boolean timing;
	private int headAccel; //int?
	private int arm1Accel; //int?
	private int arm2Accel; //int?
	
	public AccelSwipeTab(int widthOfContainer, int heightOfContainer, String s){
		super(widthOfContainer, heightOfContainer, s);
		w = (double)getWidth();
		h = (double)getHeight();
	}
	
	public AccelSwipeTab(int widthOfContainer, int heightOfContainer){
		super(widthOfContainer, heightOfContainer);
		w = (double)getWidth();
		h = (double)getHeight();	
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		if(getPulled()){
			if(!timing){
				timing = true;
				GUITimer.addActionListener(this);
			}
			draw(g);
		}
		
		else {
			if(timing){
				timing = false;
				GUITimer.removeActionListener(this);
			}
		}
	}
	
	
	public void updateForDrawing(){
		
		//headAccel = GUISerialPort.getAccelVals()[0];
		//arm1Accel = GUISerialPort.getAccelVals()[1];
		//arm2Accel = GUISerialPort.getAccelVals()[2];
		
		//temporary simulation
		headAccel = 20;
		arm1Accel = 20;
		arm2Accel = 20;
		
		}
	
	public void draw(Graphics g){
		
		//hold
		
		}
		
	public void actionPerformed(ActionEvent evt){
		/*if(!getPulled()){
			super.actionPerformed(evt);
		}
		else{
			updateForDrawing();
			repaint();
		}*/
		updateForDrawing();
		repaint();
		
	}
	
}