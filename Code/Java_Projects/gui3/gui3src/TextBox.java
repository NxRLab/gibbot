/**
 * @(#)TextBox.java
 *
 *
 * @author 
 * @version 1.00 2014/7/31
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*Displays the message: "real time wireless data from the gibbot" with an animated
 *wireless signal. Note that font size is set in the first line.
 */

public class TextBox extends JPanel implements ActionListener{
	
	private Font andaleBig = ImageHandler.getFont().deriveFont(Font.BOLD, 36);
	
	private int width;
	private int height;
	
	private final int W0 = 0;
	private final int W1 = 1;
	private final int W2 = 2;
	private final int W3 = 3;
	
	private int wireless;
	private int timerCount;
	private int updateCount = (int)(750/GUITimer.getMillisPerFrame()); //symbol updates every .75 seconds
	
	private Color bg = new Color(204, 204, 255);
	JButton okButton;

    public TextBox(int widthOfContainer, int heightOfContainer) {
    	
    	width = widthOfContainer/4 - 20;
    	height = (int)(heightOfContainer/3.25) - 30;
    	super.setPreferredSize(new Dimension(width, height));
    	super.setBackground(bg);
    	timerCount = 0;
    	wireless = -1;
    	GUITimer.addActionListener(this);
    }
    
    public void paintComponent(Graphics g){
    	
    	super.paintComponent(g);
    	g.setFont(andaleBig);
    	drawTextBubble(10, 20, width - 30, height - 20, g);
    	
    }
    
    public void drawTextBubble(int x, int y, int width, int height, Graphics g){
   		
   		g.setColor(Color.WHITE); //white
    	g.fillRoundRect(x, y, width - 19, height, 12, 12);
    	
    	g.setColor(new Color(0, 51, 153));
    	g.drawString("real time", x + 15, 70);
    	g.drawString("wireless", x + 24, 110);
    	g.drawString("data from", x + 15, 150);
    	g.drawString("the gibbot", x + 6, 190);
    	
    	Graphics2D g2 = (Graphics2D)g;
    	g2.setStroke(new BasicStroke(5, BasicStroke.CAP_ROUND, BasicStroke.JOIN_BEVEL));
    	g2.setColor(Color.WHITE);
    	
    	switch(wireless){
    		case(W0):
    			g2.fillOval(width, height/2 + 15, 15, 15);
    			break;
    		case(W1):;
    			g2.fillOval(width, height/2 + 15, 15, 15);
    			g2.drawArc(width - 30, height/2 - 7, 60, 60, -45, 90);
    			break;
    		case(W2):;
    			g2.fillOval(width, height/2 + 15, 15, 15);
    			g2.drawArc(width - 30, height/2 - 7, 60, 60, -45, 90);
    			g2.drawArc(width - 45, height/2 - 22, 90, 90, -45, 90);
    			break;
    		case(W3):;
    			g2.fillOval(width, height/2 + 15, 15, 15);
    			g2.drawArc(width - 30, height/2 - 7, 60, 60, -45, 90);
    			g2.drawArc(width - 45, height/2 - 22, 90, 90, -45, 90);
    			g2.drawArc(width - 60, height/2 - 37, 120, 120, -45, 90);
    			break;
    	}
    }
    
    public void actionPerformed(ActionEvent evt){  //symbol changes every .75 seconds

	    	if(timerCount % updateCount == 0){
    			wireless++;
    			repaint();
	    	}
    		
	    	if(timerCount == updateCount*4){
    			timerCount = 1;
    			wireless = W0;
	    	}
    		else
    			timerCount++;
    	
    }
    
}