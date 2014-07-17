
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import javax.swing.*;
import jssc.*;

class AngleSwipeTab extends SampleSwipeTab implements ContentSwipeTab, ActionListener {
	
	private double w;
	private double h;
	private int rx;
	private int ry;
	private int rcircle;
	
	private int head;
	private int arm1;
	private int arm2;

	private boolean timing;
	
	public AngleSwipeTab(int widthOfContainer, int heightOfContainer, String s){
		super(widthOfContainer, heightOfContainer, s);
		w = (double)getWidth();
		h = (double)getHeight();
		
		rx = (int)((w)/3);
		ry = (int)(h - 63)/2;
		
		if(rx > ry)
			rcircle = ry;
		else
			rcircle = rx;
	}
	
	public AngleSwipeTab(int widthOfContainer, int heightOfContainer){
		super(widthOfContainer, heightOfContainer);
		w = (double)getWidth();
		h = (double)getHeight();
		
		rx = (int)((w)/3);
		ry = (int)(h - 63)/2;
		
		if(rx > ry)
			rcircle = ry;
		else
			rcircle = rx;		
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
	
	public void actionPerformed(ActionEvent evt){
		/*if(!getPulled){
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
		head = GUISerialPort.getAngles()[0];
		arm1 = GUISerialPort.getAngles()[1];
		arm2 = GUISerialPort.getAngles()[2];
	}
		
	
	public void draw(Graphics g){

		g.setColor(Color.RED);	
		g.fillArc(3, 10, rcircle, rcircle, 0, arm1);
		g.fillArc(3 + rx, 10 + ry, rcircle, rcircle, 0, head);
		g.fillArc(3 + 2*rx, 10, rcircle, rcircle, 0, arm2);
		
		g.setColor(Color.BLACK);
		g.drawString("Arm 1", 16, 30 + ry);
		g.drawString("Head", 16 + rx, 30 + 2*ry);
		g.drawString("Arm 2", 16 + 2*rx, 30 + ry);
	}	
		
}
