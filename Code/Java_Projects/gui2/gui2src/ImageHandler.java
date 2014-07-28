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
    
    	//accel
    	Graphics2D g2 = accelChart.createGraphics();
    	g2.setColor(Color.WHITE);
    	g2.fillRect(0, 0, 254, 185);
    	g2.setFont(andale);
    	g2.setColor(Color.LIGHT_GRAY);
    	g2.fillRect(18, 15, 220, 156);
    	g2.setColor(Color.BLACK);
    	g2.drawLine(17, 15, 17, 170);
    	g2.drawLine(17, 93, 237, 93);
    	g2.setColor(new Color(0, 51, 153));
    	g2.drawString("arm 1", 31, 183);
    	//g2.drawString("head", 105, 183);
    	g2.drawString("arm 2", 175, 183);
    	g2.rotate(-Math.PI/2);
    	g2.drawString("acceleration  (m/s^2)", -168, 14);
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
    	g2.drawLine(17, 15, 17, 170);
    	g2.drawLine(17, 170, 237, 170);
    	g2.drawLine(237, 170, 237, 15);
    	g2.setColor(new Color(0, 51, 153));
    	g2.drawString("time", 102, 183);
    	g2.setColor(Color.LIGHT_GRAY);
    	g2.fillRect(18, 15, 219, 155);
    	g2.rotate(-Math.PI/2);
    	g2.setColor(Color.RED);
    	g2.drawString("current  (milliamps)", -170, 12);
    	g2.setColor(Color.CYAN);
    	g2.drawString("torque  (N*10^-3*m)", -165, 250);
    	g2.dispose();
    	map.put(imageNames[7], currentChart);
    	
    	//hardware
    	g2 = hardwareChart.createGraphics();
    	g2.setColor(Color.WHITE);
    	g2.fillRect(0, 0, 146, 185);
    	g2.setFont(andale);
    	g2.setColor(Color.BLACK);
    	g2.drawRect(19, 15, 24, 129);
    	g2.drawRect(77, 15, 48, 129);
    	g2.setColor(new Color(0, 51, 153));
    	g2.drawString("motor", 12, 155);
    	g2.drawString("temp", 12, 169);
    	g2.drawString("(deg F)", 5, 183);
    	g2.drawString("battery", 73, 155);
    	g2.drawString("life (%)", 70, 169);
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