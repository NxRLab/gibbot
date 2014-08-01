/**
 * @(#)Speedometer.java
 *
 *
 * @author 
 * @version 1.00 2014/7/31
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class Speedometer extends JPanel implements ActionListener{

    private int width;
    private int height;
    private int w;
	private int h;
	private double xscale;
	private double yscale;
	
	private Image chart = ImageHandler.getImage("speedometer");
	private Color bg = new Color(204, 204, 255);
	//private Color bg = new Color(255, 255, 255);
	
	private int arm1vel; 
	private int arm2vel; 
	
	public Speedometer(int widthOfContainer, int heightOfContainer){
		
		width = (int)(widthOfContainer/3);
		height = (int)(heightOfContainer/3.25);
		super.setPreferredSize(new Dimension(width, height));
		super.setBackground(bg);
		w = width - 70;
		h = height - 60;
		xscale = (w/363);
		yscale = (h/185);
		GUITimer.addActionListener(this);
	}
	
	public void paintComponent(Graphics g){
		
		super.paintComponent(g);
		drawTab(width, height - 20, g);
		g.drawImage(chart, 30, 20, this);
		
		Graphics2D g2 = (Graphics2D)g;
		g2.setColor(new Color(150, 150, 150, 100));
		g2.setStroke(new BasicStroke(4, BasicStroke.CAP_ROUND, BasicStroke.JOIN_BEVEL));
		g2.drawLine((int)(xscale*182) + 30, (int)(yscale*163 + 20), 
			(int)(xscale*(182 - 117*Math.cos(arm1vel*Math.PI/180))), (int)(yscale*(170 - 117*Math.sin(arm1vel*Math.PI/180))));
		g2.setColor(new Color(36, 149, 176, 125));
		g2.drawLine((int)(xscale*182) + 30, (int)(yscale*163 + 20), 
			(int)(xscale*(182 - 117*Math.cos(arm2vel*Math.PI/180))), (int)(yscale*(170 - 117*Math.sin(arm2vel*Math.PI/180))));

	}
	
	public void updateForDrawing(){
	
		int[] data = GUISerialPort.getData();	
	
		arm1vel = data[12]; 
		arm2vel = data[18]; 
			
	}
			
	
	public void drawTab(int width, int height, Graphics g){
    	
    	Graphics2D g2 = (Graphics2D)g;
    	
    	g2.setColor(new Color(125, 125, 125, 50)); //lightest gray
    	g2.fillRoundRect(7, 7, width - 7, height + 12, 12, 12);
    	
    	g2.setColor(new Color(125, 125, 125, 100)); //light gray
    	g2.fillRoundRect(7, 7, width - 11, height + 8, 12, 12);
        
        g2.setColor(new Color(125, 125, 125, 150)); //middle gray
    	g2.fillRoundRect(7, 7, width - 15, height + 4, 12, 12);
    	
    	g2.setColor(new Color(130, 130, 130, 200)); //dark gray
    	g2.fillRoundRect(7, 7, width - 19, height, 9, 9);
   		
   		g2.setColor(Color.WHITE); //white
    	g2.fillRoundRect(3, 3, width - 19, height, 12, 12);
    	
    	g2.setStroke(new BasicStroke(4));  //blue
    	g2.setColor(new Color(0, 51, 153)); 
    	//g2.drawRoundRect(13, 13, width - 39, height-20, 9, 9);
    	
    	g2.setStroke(new BasicStroke(1));

	}
	
	public void actionPerformed(ActionEvent evt){
		
		updateForDrawing();
		repaint();
	}
	
}