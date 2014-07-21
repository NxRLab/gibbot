/**
 * @(#)HardwareSwipeTab.java
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

public class HardwareSwipeTab extends SampleSwipeTab implements ContentSwipeTab, ActionListener {
	
	private double w;
	private double h;
	private boolean timing;
	private int battLevel; //int?
	private int temp; //int?
	
	public HardwareSwipeTab(int widthOfContainer, int heightOfContainer, String s){
		super(widthOfContainer, heightOfContainer, s);
		w = (double)getWidth();
		h = (double)getHeight();
	}
	
	public HardwareSwipeTab(int widthOfContainer, int heightOfContainer){
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
		
		//battLevel = GUISerialPort.getBattLevel();
		//temp = GUISerialPort.getTemp();
		
		//temporary simulation
		battLevel = 75;
		temp = 80;
		
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