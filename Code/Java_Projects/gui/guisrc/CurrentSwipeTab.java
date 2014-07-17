
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import javax.swing.*;
import jssc.*;

public class CurrentSwipeTab extends SampleSwipeTab implements ContentSwipeTab, ActionListener {
	
	private double w;
	private double h;
	private boolean timing;
	
	public CurrentSwipeTab(int widthOfContainer, int heightOfContainer, String s){
		super(widthOfContainer, heightOfContainer, s);
		w = (double)getWidth();
		h = (double)getHeight();
	}
	
	public CurrentSwipeTab(int widthOfContainer, int heightOfContainer){
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
	
	//Currently a simulation
	//haha.
	private double amps = 0;
	
	public void updateForDrawing(){
		
		amps = 7;
		
		}
	
	public void draw(Graphics g){
		
		Graphics2D g2 = (Graphics2D)g; //not sure if this is or will be necessary but I'll leave it for now.
		
		//y axis
		g2.drawLine(20, 20, 20, (int)h-20);
		g2.drawString("Amps", 5, 15);
		
		//x axis
		g2.drawLine(20, (int)h-20, (int)w-20, (int)h-20);
		
		g2.setColor(Color.MAGENTA);
			
		g2.fillRect((int)w/4, (int)(h-amps-20), (int)(w-40)/2, (int)amps);
		
		}
		
	public void actionPerformed(ActionEvent evt){
		if(!getPulled){
			super.actionPerformed(evt);
		}
		else{
			updateForDrawing();
			repaint();
		}
	}
	
}