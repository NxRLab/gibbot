/**
 * @(#)DebuggerGraphPanel.java
 *
 *
 * @author 
 * @version 1.00 2014/8/18
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class DebuggerGraphPanel extends JPanel implements ActionListener{
	
	private final Color GRAPH_BG = new Color(200, 200, 200);
	public final int MARGIN = 20;
	private final String message;
	private final int ID;
	
	private int oldWidth = 0;
	private int n;
	private int[] xvals;

    public DebuggerGraphPanel(String s, int i) {
    	super();
    	setBackground(Color.WHITE);
    	message = s; 
    	ID = i;
    	n = GraphArrayUpdater.getN();
    	DebuggerGUITimer.addActionListener(this);
    	GraphArrayUpdater.marginOfGraphs = MARGIN;
    }
    
    public void paintComponent(Graphics g){
    	
    	int width = getWidth();
    	int height = getHeight();
    	GraphArrayUpdater.currentHeight = height;
    	
    	super.paintComponent(g);
    	
    	g.setColor(GRAPH_BG);
    	g.fillRect(MARGIN, MARGIN + 12, width - 2*MARGIN, height - 2*MARGIN - 12);
    	
    	g.setColor(Color.BLACK);
    	g.drawLine(MARGIN, MARGIN + 12, MARGIN, height - MARGIN);
    	g.drawLine(MARGIN, height - MARGIN, width - MARGIN, height - MARGIN);
    	
    	g.drawString(message, width/2, MARGIN + 9);
    	
    	g.setColor(Color.BLUE);
    	for(int i = 0; i < 19; i++){
    		if(GraphArrayUpdater.graphChoices[i] == ID)
    			g.drawPolyline(xvals, GraphArrayUpdater.yvals[i], n);
    	}
    	
    }
    
    public void actionPerformed(ActionEvent evt){
    
    	if(getWidth() != oldWidth){
    		oldWidth = getWidth();
    		xvals = new int[n];
    		for(int i = 0; i < n; i++)
    			xvals[i] = MARGIN + i*(oldWidth/(n + 1));
    	}
    	
    	repaint();
    }
    
}