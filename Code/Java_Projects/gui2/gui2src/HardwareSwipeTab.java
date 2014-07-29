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
	private int timerCount = 0;
	private int factor = GUITimer.getSerialFactor();
	
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
			g.setColor(new Color(207, 46, 46, 125));
			g.fillRect((int)(30 + xscale*20) + 1, (int)(20 + yscale*144) - temp, (int)(xscale*21)-1, temp-2);
			g.setColor(new Color(36, 149, 176, 125));
			g.fillRect((int)(30 + xscale*78) + 1, (int)(20 + yscale*144) - batt, (int)(xscale*44)-1, batt-2);
		}
		
		else {
			if(timing){
				timing = false;
				GUITimer.removeActionListener(this);
			}
		}
	}
	
	
	public void updateForDrawing(){
		
		timerCount++;
		
		if(timerCount % factor == factor - 1){
		
			int[] data = GUISerialPort.getData();
		
			batt = data[6]; 
			temp = data[5]; 
			
			timerCount = 0;
		}
			
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