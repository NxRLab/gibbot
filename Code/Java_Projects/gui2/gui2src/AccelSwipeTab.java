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
	private int headAccel; //int?
	private int arm1Accel; //int?
	private int arm2Accel; //int?
	
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
			g.setColor((Color.RED));
			g.fillRect(30 + (int)(xscale*43), 20 + (int)(yscale*93) - arm1Accel, (int)(xscale*24), arm1Accel);
			g.fillRect(30 + (int)(xscale*187), 20 + (int)(yscale*93) - arm2Accel, (int)(xscale*24), arm2Accel);	
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
		arm1Accel = (int)(Math.sqrt(data[4]*data[4] + data[5]*data[5]));
		arm2Accel = (int)(Math.sqrt(data[10]*data[10] + data[11]*data[11]));
		
		//headAccel = 20;
		//arm1Accel = 20;
		//arm2Accel = 20;
		
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