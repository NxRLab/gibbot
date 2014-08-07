/**
 * @(#)HardwareBox.java
 *
 *
 * @author 
 * @version 1.00 2014/7/31
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*Displays motor temperature and battery life in a bar chart graphic
 */

public class HardwareBox extends JPanel implements ActionListener{
	
	private Image chart = ImageHandler.getImage("hardwareChart");

    private int width;
    private int height;
    private int w;
	private int h;
	private double xscale;
	private double yscale;
	
	private int batt; 
	private int temp; 
	
	public HardwareBox(int widthOfContainer, int heightOfContainer){
		
		width = widthOfContainer/6;
		height = (int)(heightOfContainer/3.25);
		setPreferredSize(new Dimension(width, height));
		setBackground(GibbotGUI3.globalBg);
		w = width - 70;
		h = height - 60;
		xscale = w/146.0;
		yscale = h/185.0;
		GUITimer.addActionListener(this);
	}
	
	public void paintComponent(Graphics g){
		
		super.paintComponent(g);
		drawTab(width, height - 20, g);
		g.drawImage(chart, 30, 20, w, h, this);
		
		g.setColor(new Color(207, 46, 46, 125));
		g.fillRect((int)(30 + xscale*20) + 1, (int)(20 + yscale*144) - temp, (int)(xscale*21)-1, temp-2);
		g.setColor(new Color(36, 149, 176, 125));
		g.fillRect((int)(30 + xscale*78) + 1, (int)(20 + yscale*144) - batt, (int)(xscale*44)-1, batt-2);

	}
	
	public void updateForDrawing(){
	
		int[] data = GUISerialPort.getData();	
	
		batt = data[3]; 
		temp = data[2]; 
			
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
   		
   		g.setColor(new Color(240, 240, 240));
    	g.fillRoundRect(3, 3, width - 19, height, 12, 12);
    	
	}
	
	public void actionPerformed(ActionEvent evt){
		
		updateForDrawing();
		repaint();
	}
	
}