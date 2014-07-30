
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import javax.swing.*;

public class CurrentSwipeTab extends SampleSwipeTab implements ActionListener {
	
	private int w;
	private int h;
	private double xscale;
	private double yscale;
	
	private Image chart = ImageHandler.getImage("currentChart");	
	
	private boolean timing;
	private int timerCount;
	private int factor = GUITimer.getSerialFactor();
	
	private int[] milliampsE;
	private int[] milliampsO;	
	private int[] milnewtmetsE;
	private int[] milnewtmetsO;
	private int[] t;  //x values for chart
	private int n;  //number of points drawn
	private int par;  //tracks which array to draw
	
	public CurrentSwipeTab(int widthOfContainer, int heightOfContainer, String s){
		super((int)(widthOfContainer/4), heightOfContainer, s);
		w = (int)widthOfContainer/4 -70;
		h = getHeight()-60;
		xscale = (w/254);
		yscale = (h/185);
		n = (int)(200*xscale/10); //points drawn 10 pixles apart
		
		milliampsE = new int[n];
		milliampsO = new int[n];
		milnewtmetsE = new int[n];
		milnewtmetsO = new int[n];
		t = new int[n];
		par = 0;
		
		for(int i = 0; i < n; i++){
			milliampsE[i] = 20 + (int)(93*yscale); //replace 20 w/ y coor where chart image is drawn
			milliampsO[i] = 20 + (int)(93*yscale);
			milnewtmetsE[i] = 20 + (int)(93*yscale);
			milnewtmetsO[i] = 20 + (int)(93*yscale);
			t[i] = 10*i + 25 + (int)(26*xscale);  //replace 25 w/ x coor where chart image is drawn
		}
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		if(getPulled()){
			if(!timing){
				timing = true;
				timerCount = 0;
				GUITimer.addActionListener(this);
			}
			
			g.drawImage(chart, 25, 20, w, h, this);
			if(par == 0){
				g.setColor(new Color(207, 46, 46));
    			g.drawPolyline(t, milliampsE, n);
    			g.setColor(new Color(36, 149, 176));
    			g.drawPolyline(t, milnewtmetsE, n);
			}    	
    		else{
    			g.setColor(new Color(207, 46, 46));
    			g.drawPolyline(t, milliampsO, n);
    			g.setColor(new Color(36, 149, 176));
    			g.drawPolyline(t, milnewtmetsO, n);	
    		}
		}
		
		else {
			if(timing){
				timing = false;
				GUITimer.removeActionListener(this);
				timerCount = 0;
			}
		}
	}
	
	public void updateForDrawing(){
		
		timerCount++;
		
		if(timerCount % factor/2 == 0){
			int[] data = GUISerialPort.getData();
			
			int newCurr = 20 + (int)(93*yscale) - data[3];
			int newTor = 20 + (int)(93*yscale) -  data[4];
		
			if(par == 0){
				par = 1;
				milliampsE[0] = newCurr;
				milnewtmetsE[0] = newTor;
    			for(int i = 0; i<n-2; i++){
    				milliampsE[i+1] = milliampsO[i];
	    			milnewtmetsE[i+1] = milnewtmetsO[i];
    			}
			}
	    	else{
    			par = 0;
    			milliampsO[0] = newCurr;
				milnewtmetsO[0] = newTor;
    			for(int i = 0; i<n-2; i++){
    				milliampsO[i+1] = milliampsE[i];
	    			milnewtmetsO[i+1] = milnewtmetsE[i];
    			}
			}
				
			repaint();
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