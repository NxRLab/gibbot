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

public class TextBox extends JPanel implements ActionListener{
	
	private Color bg = new Color(204, 204, 255);
	private Font andaleBig = ImageHandler.getFont().deriveFont(Font.BOLD, 36);
	private int width;
	private int height;
	private Polygon triangle;
	
	private final int W0 = 0;
	private final int W1 = 1;
	private final int W2 = 2;
	private final int W3 = 3;
	
	private int wireless;
	private int timerCount;
	private int updateCount = (int)(750/GUITimer.getMillisPerFrame()); //symbol updates every .75 seconds
	
	JButton okButton;

    public TextBox(int widthOfContainer, int heightOfContainer) {
    	
    	width = (int)(widthOfContainer/4) - 20;
    	height = (int)(heightOfContainer/3.25) - 30;
    	super.setPreferredSize(new Dimension(width, height));
    	super.setBackground(bg);
    	timerCount = 0;
    	wireless = -1;
    	GUITimer.addActionListener(this);
    	
    	okButton = new JButton("OK");
    	ButtonHandler listener = new ButtonHandler();
    	okButton.addActionListener(listener);
    }
    
    public void paintComponent(Graphics g){
    	
    	super.paintComponent(g);
    	g.setFont(andaleBig);
    	drawTextBubble(10, 20, width - 30, height - 20, g);
    	
    }
    
    public void drawTextBubble(int x, int y, int width, int height, Graphics g){
    	
    	/*g.setColor(new Color(125, 125, 125, 50)); //lightest gray
    	g.fillRoundRect(x + 4, y + 4, width - 7, height + 12, 12, 12);
    	
    	g.setColor(new Color(125, 125, 125, 100)); //light gray
    	g.fillRoundRect(x + 4, y + 4, width - 11, height + 8, 12, 12);
        
        g.setColor(new Color(125, 125, 125, 150)); //middle gray
    	g.fillRoundRect(x + 4, y + 4, width - 15, height + 4, 12, 12);
    	
    	g.setColor(new Color(130, 130, 130, 200)); //dark gray
    	g.fillRoundRect(x + 4, y + 4, width - 19, height, 9, 9);*/
   		
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