/**
 * @(#)GPanel.java
 *
 *
 * @author 
 * @version 1.00 2014/7/9
 */

import java.awt.*;
import java.awt.event.*;
import java.util.Random;
import javax.swing.*;
import javax.swing.Timer;

public class GPanel extends JPanel implements ActionListener, MouseListener {

	private int n;
	private int height;
	
	private int[] xs;
	private int[] yse;
	private int[] yso;
	private int[] temp;
	
	private int newy;
	private int par;
	
	private Timer timer = new Timer(25, this);
	private Random generator = new Random();
	private boolean running;

    public GPanel(int width, int h) {
    	
    	n = (int)(width/5);
    	height = h;
    	xs = new int[n];
    	yse = new int[n];
    	yso = new int[n];
    	temp = new int[n];
    	
    	for(int i = 0; i<n; i++){
    		xs[i] = 5*i;
    		yse[i] = 0;
    		yso[i] = 0;
    		temp[i] = 0;
    	}
    	
    	addMouseListener(this);
    	
    	running = false;
    	par = 0;
    }
    
    public void paintComponent(Graphics g){
    	
    	super.paintComponent(g);
    	if(par%2 == 0)
    		g.drawPolyline(xs, yse, n);
    	
    	else
    		g.drawPolyline(xs, yso, n);	
    }
    
    public void actionPerformed(ActionEvent evt){
    	
    	newy = generator.nextInt(height);
    	par++;
    	
    	if(par%2 == 0){
    		yse[0] = newy;
    		for(int i = 0; i<n-2; i++)
    			yse[i+1] = yso[i];
    	}
    	
    	else{
    		yso[0] = newy;
    		for(int i = 0; i<n-2; i++)
				yso[i+1] = yse[i];	
    	}
    	
    	repaint();
    	}
    
    public void mouseClicked(MouseEvent evt){
    	if(!running){
   			running = true;
    		timer.start();
    		}
    }
    
    public void mousePressed(MouseEvent evt){}
    public void mouseReleased(MouseEvent evt){}
    public void mouseEntered(MouseEvent evt){}
    public void mouseExited(MouseEvent evt){}
    
    
}