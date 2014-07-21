import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;

class BoardPanel extends JPanel {
	
	MetalTexture board = new MetalTexture();
	//BananaPanel1 panel = new BananaPanel1();

    public BoardPanel() {
    	this.setBackground(Color.WHITE);
    	//this.add(panel, -1);
    }
    
    public void paintComponent(Graphics g) {
    	super.paintComponent(g);
    	
    	g.setColor(Color.LIGHT_GRAY);
    	g.fillRect(30, 30, getWidth()-60, getHeight()-60);
    	g.setColor(Color.DARK_GRAY);
		g.drawRect(40, 40, getWidth()-80, getHeight()-80);
    	g.drawRect(50, 50, getWidth()-100, getHeight()-100);    	
    	Graphics2D g2d = (Graphics2D)g;   	
    	
    	g2d.drawImage(board.getImage(), 60, 60, getWidth()-120, getHeight()-120, this);	
    }
  
}
