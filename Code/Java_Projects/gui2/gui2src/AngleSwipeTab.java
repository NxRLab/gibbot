
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
	
	private int head;
	private int arm1 = 0;
	private int arm2 = 0;
	
	private String avhead = "";
	private String avarm1 = "";
	private String avarm2 = "";

	private boolean timing;
	
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
		
			g.setColor(Color.RED);	
			g.fillArc((int)(20 + xscale*78), (int)(20 + yscale*10), rcircle, rcircle, 0, arm1);
			g.fillArc((int)(20 + xscale*185), (int)(20 + yscale*10), rcircle, rcircle, 0, head);
			g.fillArc((int)(20 + xscale*292), (int)(20 + yscale*10), rcircle, rcircle, 0, arm2);
			
			g.drawString(avarm1, 20 + (int)(xscale*78), 145);
			g.drawString(avarm2, 20 + (int)(xscale*292), 145);
			
			//g.drawString("ang vel", 20 + (int)(xscale*78), 145);
			//g.drawString("vals", 20 + (int)(xscale*185), 145);
			//g.drawString("here", 20 + (int)(xscale*292), 145);
			
			//g.drawString(avarm1, xscale*60, 125);
			//g.drawString(avhead, xscale*60, 125);
			//g.drawString(avarm2, xscale*60, 125);;
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
		
		String[] data = GUISerialPort.getDataS();
		float[] dataF = GUISerialPort.getDataF();
		
		head = Integer.parseInt(data[1]); //indicies will likely change
		arm1 = Integer.parseInt(data[0]);
		arm2 = Integer.parseInt(data[2]);
		
		//avhead = GUISerialPort.getData()[];
		avarm1 = Float.toString(dataF[9]);
		avarm2 = Float.toString(dataF[15]); 
	}	
		
}
