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

public class HardwareSwipeTab extends SampleSwipeTab implements ActionListener {
	
	private int w;
	private int h;
	private double xscale;
	private double yscale;
	private Image chart = ImageHandler.getImage("hardwareChart");
	private boolean timing;
	private int batt; //int?
	private int temp; //int?
	
	public HardwareSwipeTab(int widthOfContainer, int heightOfContainer, String s){
		super((int)(widthOfContainer/6), heightOfContainer, s);
		w = (int)widthOfContainer/6 - 70;
		h = getHeight()-60;
		xscale = (w/146);
		yscale = (h/185);
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		if(getPulled()){
			if(!timing){
				timing = true;
				GUITimer.addActionListener(this);
			}
			g.drawImage(chart, 30, 20, this);
			g.setColor(Color.RED);
			g.fillRect((int)(30 + xscale*21) + 1, (int)(20 + yscale*144) - temp, (int)(xscale*20)-1, temp-2);
			g.setColor(Color.CYAN);
			g.fillRect((int)(30 + xscale*79) + 1, (int)(20 + yscale*144) - batt, (int)(xscale*44)-1, batt-2);
		}
		
		else {
			if(timing){
				timing = false;
				GUITimer.removeActionListener(this);
			}
		}
	}
	
	
	public void updateForDrawing(){
		
		float[] data = GUISerialPort.getDataF();
		
		batt = (int)data[3];
		temp = (int)data[2];
		
		//temporary simulation
		//batt = 75;
		//temp = 80;
		
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