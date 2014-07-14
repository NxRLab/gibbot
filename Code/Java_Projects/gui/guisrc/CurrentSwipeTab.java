
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import javax.swing.*;
import jssc.*;

public class CurrentSwipeTab extends SampleSwipeTab implements ContentSwipeTab, ActionListener {
	
	private double time;
	private double w;
	private double h;
	private Timer timer = new Timer(40, this);
	private double timerCount;
	private boolean timing = false;
	private GUISerialPort port = new GUISerialPort("COM3");
	private boolean updatingFromSerial = true;

	
	public CurrentSwipeTab(int widthOfContainer, int heightOfContainer, String s){
		super(widthOfContainer, heightOfContainer, s);
		w = (double)getWidth();
		h = (double)getHeight();
		setFont(getFont());
	}
	
	public CurrentSwipeTab(int widthOfContainer, int heightOfContainer){
		super(widthOfContainer, heightOfContainer);
		w = (double)getWidth();
		h = (double)getHeight();
		setFont(new Font("Serif", Font.PLAIN, 15));		
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		if(getPulled()){
			if(!timing){
				timerCount = 0;
				timing = true;
				timer.start();
				
				updatingFromSerial = port.openPort();
				
			}
			draw(g);
		}
		
		else {
			if(timing){
				timing = false;
				timer.stop();
			}
		}
	}
	
	//Currently a simulation
	//haha.
	private double amps = 0;
	
	public void updateForDrawing(double timerCount){
		
		time = timerCount/25;
		
		amps = (h/4)*Math.sin(70*Math.PI/(w-40)*time-(w-40)/16)+h/2;
		
		}
		
	public void updateForDrawingSerial(){
		
		amps = 8*port.getGraphVal();
		
	}
	
	public void draw(Graphics g){
		
		Graphics2D g2 = (Graphics2D)g;
		
		//y axis
		g2.drawLine(20, 20, 20, (int)h-20);
		g2.drawString("Amps", 5, 15);
		
		//x axis
		g2.drawLine(20, (int)h-20, (int)w-20, (int)h-20);
		
		if(updatingFromSerial)
			g2.setColor(Color.RED);
		else
			g2.setColor(Color.MAGENTA);
			
		g2.fillRect((int)w/4, (int)(h-amps-20), (int)(w-40)/2, (int)amps);
		
		}
		
	public void actionPerformed(ActionEvent evt){
		if(updatingFromSerial)
			updateForDrawingSerial();
		else
			updateForDrawing(timerCount);
		timerCount++;
		repaint();
	}
	
}