/**
 * @(#)ImageHandler.java
 *
 *
 * @author 
 * @version 1.00 2014/7/22
 */
import java.awt.*;
import java.awt.geom.*;
import java.awt.image.*;
import java.io.*;
import java.util.*;
import javax.imageio.*;

public class ImageHandler {
	
	private static InputStream stream;
	
	private static Font andale;
	private static BufferedImage accelChart = new BufferedImage(254, 185, BufferedImage.TYPE_BYTE_INDEXED);
	private static BufferedImage angleChart = new BufferedImage(363, 185, BufferedImage.TYPE_BYTE_INDEXED);
	private static BufferedImage currentChart = new BufferedImage(254, 185, BufferedImage.TYPE_BYTE_INDEXED);
	private static BufferedImage hardwareChart = new BufferedImage(146, 185, BufferedImage.TYPE_BYTE_INDEXED);
	
	private static HashMap<String, Image> map = new HashMap<String, Image>(9);
	private static String[] imageNames = new String[] {"banana", "bananaBubble", "board", "bucket", "gibbotBubble", 
		"accelChart", "angleChart", "currentChart", "hardwareChart"};

    public ImageHandler() {
    }
    
    public static void loadImages(){ //also loads AndaleMono Font
    
    	for(int i = 0; i < 5; i++){
    		try {
    			Image img = ImageIO.read(new File(imageNames[i]+".png"));
				map.put(imageNames[i], img);
			}
			catch(IOException e){
				System.out.println(imageNames[i] + " not found");
				map.put(imageNames[i], null);
			}
    	}
    	
    	try{
    		stream = new BufferedInputStream(new FileInputStream("AndaleMono.ttf"));
    		andale = (Font.createFont(Font.TRUETYPE_FONT, stream)).deriveFont(Font.BOLD, 12);
    	}
    	catch(Exception e){
    		System.out.println(e);
    		andale = new Font("Serif", Font.PLAIN, 15);
    	}
    }
    
    public static void drawImages(){ //draws all chart backgrounds for swipe tabs
    
    	Color LIGHTER_GRAY = new Color(225, 225, 225);
    
    	//accel
    	Graphics2D g2 = accelChart.createGraphics();
    	g2.setColor(Color.WHITE);
    	g2.fillRect(0, 0, 254, 185);
    	g2.setFont(andale);
    	g2.setColor(LIGHTER_GRAY);
    	g2.fillRect(28, 15, 210, 156);
    	g2.setColor(Color.BLACK);
    	g2.drawLine(27, 15, 27, 170);
    	g2.drawLine(27, 93, 237, 93);
    	g2.setColor(new Color(0, 51, 153));
    	g2.drawString("arm 1", 57, 183);
    	g2.drawString("arm 2", 170, 183);
    	g2.setFont(andale.deriveFont(8));
    	for(int i = 2; i > -3; i--)
    		if(i >= 0)
    			g2.drawString(Integer.toString(i), 18, 97 - i*35);
    		else
    			g2.drawString(Integer.toString(i), 11, 97 - i*35);
    	g2.setFont(andale);
    	g2.rotate(-Math.PI/2);
    	g2.drawString("acceleration  (g)", -156, 9);
    	map.put(imageNames[5], accelChart);
    	  	
    	//angle
    	g2 = angleChart.createGraphics();
    	g2.setColor(Color.WHITE);
    	g2.fillRect(0, 0, 363, 185);
    	g2.setFont(andale);
    	g2.setColor(new Color(0, 51, 153));
    	g2.drawString("arm 1", 78, 183);
    	g2.drawString("head", 185, 183);
    	g2.drawString("arm 2", 292, 183);
    	g2.rotate(-Math.PI/2);
    	g2.drawString("angular", -159, 15);
    	g2.drawString("velocity", -162, 29);
    	g2.drawString("(deg/sec)", -167, 43);
    	g2.drawString("theta", -60, 29);
    	g2.drawString("(degrees)", -75, 43);
    	g2.dispose();
    	map.put(imageNames[6], angleChart);
    	
    	//current
    	g2 = currentChart.createGraphics();
    	g2.setColor(Color.WHITE);
    	g2.fillRect(0, 0, 254, 185);
    	g2.setFont(andale);
    	g2.setColor(Color.BLACK);
    	g2.drawLine(26, 15, 26, 170);
    	g2.drawLine(217, 170, 217, 15);
    	g2.setColor(new Color(0, 51, 153));
    	g2.drawString("time", 102, 183);
    	g2.setColor(LIGHTER_GRAY);
    	g2.fillRect(27, 15, 190, 156);
    	g2.setColor(Color.BLACK);
    	g2.drawLine(26, 93, 217, 93);
    	g2.setFont(andale.deriveFont(12));
    	g2.drawString(Integer.toString(-10), 4, 173);
    	for(int i = 1; i < 5; i++)
    		g2.drawString(Integer.toString((2*i-10)), 11, 173 - 15*i);
    	for(int i = 5; i < 10; i++)
    		g2.drawString(Integer.toString((2*i-10)), 15, 173 - 15*i);
    	g2.drawString("10", 11, 24);
    	//for(int i = 1; i < 5; i++)
    	//	g2.drawString("-." + Integer.toString(-2*i+10), 219, 171 - 13*i);
    	for(int i = -1; i < 12; i++){
    		if (i == 5)
    			g2.drawString("0", 219, 98);
    		else{
	 			if(i>9 | i<1)
	 				g2.drawString(String.format("%.1f", .1*(2*i-10)), 219, 163 - 13*i);					
 				else{ 
 					if(i<5)
 						g2.drawString("-." + (-2*i+10), 218, 163 - 13*i); 						
 					else	
    					g2.drawString("." + (2*i-10), 219, 163 - 13*i);
 				}
    		}
    	}
    	g2.setFont(andale);
    	g2.rotate(-Math.PI/2);
    	g2.setColor(new Color(207, 46, 46));
    	g2.drawString("current  (amps)", -150, 9);
    	g2.setColor(new Color(36, 149, 176));
    	g2.drawString("torque  (N*m)", -147, 252);
    	g2.dispose();
    	map.put(imageNames[7], currentChart);
    	
    	//hardware
    	g2 = hardwareChart.createGraphics();
    	g2.setColor(Color.WHITE);
    	g2.fillRect(0, 0, 146, 185);
    	g2.setFont(andale);
    	g2.setColor(Color.BLACK);
    	g2.drawRect(18, 15, 25, 129);
    	g2.drawRect(76, 15, 47, 129);
    	g2.setFont(andale.deriveFont(4));
    	for(int i = 1; i < 5; i++)
    		g2.drawString("-" + Integer.toString(i*15) + "-", 17, 148 - 30*(i));
    	for(int i = 1; i < 8; i++){
  			if(i>2)
    			g2.drawString("---" + Integer.toString(i*4) + "-- ", 74, 148 - 16*(i));
    		else
    			g2.drawString("---" + Integer.toString(i*4) + "---", 76, 148 - 16*(i));
    	}
    	g2.setFont(andale);
    	g2.setColor(new Color(0, 51, 153));
    	g2.drawString("motor", 12, 155);
    	g2.drawString("temp", 12, 169);
    	g2.drawString("(deg C)", 5, 183);
    	g2.drawString("battery", 73, 155);
    	g2.drawString("life (V)", 70, 169);
    	g2.dispose();
    	map.put(imageNames[8], hardwareChart);
    	
    }
    
    public static Image getImage(String s){
    	return map.get(s);
    }
    
    public static Font getFont(){
    	return andale;
    }
    
    
}