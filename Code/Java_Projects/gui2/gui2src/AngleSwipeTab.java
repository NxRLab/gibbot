
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import javax.swing.*;

class AngleSwipeTab extends SampleSwipeTab implements ActionListener {
	
	private Image chart = ImageHandler.getImage("angleChart");
	
	private int w;
	private int h;
	private int rcircle;
	private double xscale;
	private double yscale;
	
	private int head = 0;
	private int arm1 = 0;
	private int arm2 = 0;
	private int headSlope = 0;
	private int arm1Slope = 0;
	private int arm2Slope = 0;
	
	private int avarm1 = 0;
	private int avarm2 = 0;
	private int avarm1Slope = 0;
	private int avarm2Slope = 0;

	private boolean timing;
	private int timerCount = 0;
	private int dt = GUITimer.getDelay();
	private int dT = dt*GUITimer.getSerialFactor();
	
	public AngleSwipeTab(int widthOfContainer, int heightOfContainer, String s){
		super((int)(widthOfContainer/3), heightOfContainer, s);
		w = (int)widthOfContainer/3 -70; //-60 to account for border/shadow
		h = getHeight()-60;
		
		xscale = (w/363);
		yscale = (h/185);
		
		if(xscale*50 > yscale*75)
			rcircle = (int)(yscale*75);
		else
			rcircle = (int)(xscale*50);
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		
		if(getPulled()){
			if(!timing){
				timing = true;
				GUITimer.addActionListener(this);
			}
		
			g.drawImage(chart, 20, 20, w, h, this);
		
			g.setColor(new Color(207, 46, 46));	
			g.fillArc((int)(20 + xscale*78), (int)(20 + yscale*10), rcircle, rcircle, 0, arm1);
			g.fillArc((int)(20 + xscale*185), (int)(20 + yscale*10), rcircle, rcircle, 0, head);
			g.fillArc((int)(20 + xscale*292), (int)(20 + yscale*10), rcircle, rcircle, 0, arm2);
			
			g.drawString(Integer.toString(avarm1), 20 + (int)(xscale*78), 145);
			g.drawString(Integer.toString(avarm2), 20 + (int)(xscale*292), 145);
		
		}
		
		else {
			if(timing){
				timing = false;
				GUITimer.removeActionListener(this);
			}
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
	
	public void updateForDrawing(){
		
		timerCount++;		
		
		if(timerCount % (dT/dt) == (dT/dt - 1)){
			int[] data = GUISerialPort.getData();
		
			avarm1Slope = (int)((avarm1Slope*(dT - dt) + (data[12] - avarm1)*1000)/(dT + 2*dt));
			avarm1 = data[12];
			
			avarm2Slope = (int)((avarm2Slope*(dT - dt) + (data[18] - avarm2)*1000)/(dT + 2*dt));
			avarm2 = data[18];
			
			headSlope = (int)((headSlope*(dT - dt) + (data[1] - head)*1000)/(dT + 2*dt)); 
			head = data[1];
			
			arm1Slope = (int)((arm1Slope*(dT - dt) + (data[0] - arm1)*1000)/(dT + 2*dt));
			arm1 = data[0];
			
			arm2Slope = (int)((arm2Slope*(dT - dt) + (data[2] - arm2)*1000)/(dT + 2*dt));
			arm2 = data[2];
			
			timerCount = 0;
		}
		
		else{
			head = (head + (int)(dt*headSlope)/1000) % 360;
			arm1 = (arm1 + (int)(dt*arm1Slope)/1000) % 360;
			arm2 = (arm2 + (int)(dt*arm2Slope)/1000) % 360;
			avarm1 += (int)(dt*avarm1Slope/1000);
			avarm2 += (int)((dt*avarm2Slope)/1000);
			
		} 
	}	
		
}
