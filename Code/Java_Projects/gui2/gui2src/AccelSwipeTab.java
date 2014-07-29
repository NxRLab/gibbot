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

public class AccelSwipeTab extends SampleSwipeTab implements ActionListener {
	
	private int w;
	private int h;
	private double xscale;
	private double yscale;
	
	private Image chart = ImageHandler.getImage("accelChart");
	
	private boolean timing;
	private int timerCount = 0;

	private int dt = GUITimer.getDelay(); //time b/t timer pulses, ms
	private int dT = dt*GUITimer.getSerialFactor(); //time b/t serial updates, ms
	private int arm1Slope = 0;
	private int arm2Slope = 0;
	private int arm1Accel = 0; //int?
	private int arm2Accel = 0; //int?
	
	public AccelSwipeTab(int widthOfContainer, int heightOfContainer, String s){
		super((int)(widthOfContainer/4), heightOfContainer, s);
		w = (int)widthOfContainer/4 - 70;
		h = getHeight()-60;
		xscale = w/254;
		yscale = h/185;
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		if(getPulled()){
			if(!timing){
				timing = true;
				GUITimer.addActionListener(this);
			}
			g.drawImage(chart, 30, 20, this);
			g.setColor(new Color(36, 149, 176));
			g.fillRect(30 + (int)(xscale*65), 20 + (int)(yscale*93) - arm1Accel, (int)(xscale*24), arm1Accel);
			g.fillRect(30 + (int)(xscale*178), 20 + (int)(yscale*93) - arm2Accel, (int)(xscale*24), arm2Accel);	
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
		
		if(timerCount % (dT/dt) == (dT/dt - 1)){
			int[] data = GUISerialPort.getData();
			arm1Slope = (int)((arm1Slope*(dT - dt) + (Math.sqrt(data[7]*data[7] + data[8]*data[8]) - arm1Accel)*1000)/(dT + 2*dt));
			arm2Slope = (int)((arm2Slope*(dT - dt) + (Math.sqrt(data[13]*data[13] + data[14]*data[14]) - arm2Accel)*1000)/(dT + 2*dt));
		
			arm1Accel = (int)(Math.sqrt(data[7]*data[7] + data[8]*data[8]));
			arm2Accel = (int)(Math.sqrt(data[13]*data[13] + data[14]*data[14]));
			
			timerCount = 0;
		}
		else {
			arm1Accel += (int)(arm1Slope*dt/1000);
			arm2Accel += (int)(arm2Slope*dt/1000);
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