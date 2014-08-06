/**
 * @(#)CurrentBox.java
 *
 *
 * @author 
 * @version 1.00 2014/7/31
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*Displays current and torque as an animated line graph with a double y-axis.
 *Stores points in two different arrays and updates/draws them alternatively 
 *depending on the value of the par (parity) variable - which is either zero or
 *one. This was done to cut back on lengthy array updating functions.
 */

public class CurrentBox extends JPanel implements ActionListener{

    private Image chart = ImageHandler.getImage("currentChart");
    
    private int width;
    private int height;
    private int w;
	private int h;
	private double xscale;
	private double yscale;
	
	private Color bg = new Color(204, 204, 255);	
	private int[] milliampsE;
	private int[] milliampsO;	
	private int[] milnewtmetsE;
	private int[] milnewtmetsO;
	private int[] t;  //x values for chart
	private int n;  //number of points drawn
	private int par;  //tracks which array to draw
	
	public CurrentBox(int widthOfContainer, int heightOfContainer){
		
		width = widthOfContainer/4;
		height = (int)(heightOfContainer/3.25);
		
		super.setPreferredSize(new Dimension(width, height));
    	super.setBackground(bg);
		
		w = (int)width -70;
		h = height-60;
		xscale = w/254.0;
		yscale = h/185.0;
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
		
		GUITimer.addActionListener(this);
	}
	
	public void paintComponent(Graphics g){
		
		super.paintComponent(g);
		drawTab(width, height - 20, g);	
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
	
	public void updateForDrawing(){
		
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

	}
	
	public void drawTab(int width, int height, Graphics g){
    	
    	g.setColor(new Color(125, 125, 125, 50)); //lightest gray
    	g.fillRoundRect(7, 7, width - 7, height + 12, 12, 12);
    	
    	g.setColor(new Color(125, 125, 125, 100)); //light gray
    	g.fillRoundRect(7, 7, width - 11, height + 8, 12, 12);
        
        g.setColor(new Color(125, 125, 125, 150)); //middle gray
    	g.fillRoundRect(7, 7, width - 15, height + 4, 12, 12);
    	
    	g.setColor(new Color(130, 130, 130, 200)); //dark gray
    	g.fillRoundRect(7, 7, width - 19, height, 9, 9);
   		
   		g.setColor(Color.WHITE); //white
    	g.fillRoundRect(3, 3, width - 19, height, 12, 12);

	}
	
	public void actionPerformed(ActionEvent evt){
		
		updateForDrawing();
		repaint();
	}
	
}