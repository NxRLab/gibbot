
import java.awt.*;
import java.awt.image.*;
import java.io.*;
import java.util.*;
import javax.imageio.*;

/*ImageHandler downloads/draws all complex images at initialization of GUI (this class is 
 *called by GibbotGUI3). Also downloads AndaleMono font, which is used throughout
 *the GUI. Methods that need any images from here call getImage() before their
 *constructor method. Strongly discouraged from changing any fields declared final.
 */

public class ImageHandler {
	
	/**Used to read image files*/
	private static InputStream stream;
	
	/**Width, in pixels, of currentChart image. Set public for access by all "Box" classes.*/
	public static final int CURRENT_WIDTH = 254;
	/**Width, in pixels, of hardwareChart image. Set public for access by all "Box" classes.*/
	public static final int HARDWARE_WIDTH = 146;
	/**Width, in pixels, of speedometerChart image. Set public for access by all "Box" classes.*/
	public static final int SPEEDOMETER_WIDTH = 363;
	/**Width, in pixels, of currentChart image. Set public for access by all "Box" classes.*/
	public static final int HEIGHT = 185;
	
	/**Width, in pixels, of the gray graph plane area on current graphic. Set public for access by {@link CurrentBox}.*/
	public static final int CURRENT_PLANE_WIDTH = 190;
	/**X-coor of the left origin of the gray graph plane area on current graphic. Set public for access by {@link CurrentBox}.*/
	public static final int CURRENT_PLANE_XORIGIN = 26;
	/**Y-coor of the left origin of the gray graph plane area on current graphic. Set public for access by {@link CurrentBox}.*/
	public static final int CURRENT_PLANE_YORIGIN = 93;
	
	/**X-coor of left edge of temperature empty rectangle. Set public for access by {@link HardwareBox}.*/
	public static final int HARDWARE_TEMP_LEFT_EDGE = 15;
	/**Width, in pixels, of temperature empty rectangle. Set public for access by {@link HardwareBox}.*/
	public static final int HARDWARE_TEMP_WIDTH = 31;
	/**X-coor of left edge of battery empty rectangle. Set public for access by {@link HardwareBox}.*/
	public static final int HARDWARE_BATT_LEFT_EDGE = 76;
	/**Width, in pixels, of battery empty rectangle. Set public for access by {@link HardwareBox}.*/
	public static final int HARDWARE_BATT_WIDTH = 47;
	/**Y-coor of bottom edge of temperature and battery empty rectangles. Set public for access by {@link HardwareBox}.*/
	public static final int HARDWARE_BOTTOM_EDGE = 144;
	
	/**X-coor of where needles on speedometer graphic are anchored. Set public for access by {@link SpeedometerBox}.*/
	public static final int SPEEDOMETER_NEEDLE_XORIGIN = 182;
	/**Y-coor of where needles on speedometer graphic are anchored. Set public for access by {@link SpeedometerBox}.*/
	public static final int SPEEDOMETER_NEEDLE_YORIGIN = 163;
	
	
	/**Background color for chart animations*/
	private static final Color CHART_BG = GibbotGUI3.SECONDARY_GLOBAL_BG;
	
	/**Font used throughtout the GUI*/
	private static Font andale;
	/**For displaying data in CurrentBox*/
	private static BufferedImage currentChart = new BufferedImage(CURRENT_WIDTH, HEIGHT, BufferedImage.TYPE_BYTE_INDEXED);
	/**For displaying data in HardwareBox*/
	private static BufferedImage hardwareChart = new BufferedImage(HARDWARE_WIDTH, HEIGHT, BufferedImage.TYPE_BYTE_INDEXED);
	/**For displaying data in SpeedometerBox*/
	private static BufferedImage speedometerChart = new BufferedImage(SPEEDOMETER_WIDTH, HEIGHT, BufferedImage.TYPE_BYTE_INDEXED);
	
	/**Holds images in a map where each has a key of type String, so that other classes can easily access them.*/
	private static HashMap<String, Image> map = new HashMap<String, Image>(15);
	/**All the keys for {@link #map}*/
	private static String[] imageNames = new String[] {"currentChart", "hardwareChart", "speedometerChart",  
		"banana", "bananaBubble", "batteryArrow", "batteryBar", "board", "bunch", "gibbotBubble", 
		"gibbotTab1", "gibbotTab2", "gibbotTab3", "sleepBubble"};
    
    /**Loads png image files and AndaleMono font*/
    public static void loadImages(){ 
    
    	for(int i = 3; i < 14; i++){
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
    
    /**Draws chart images (currentChart, hardwareChart, and speedometerChart)*/
    public static void drawImages(){ 
    	
 		Graphics2D g2;
    
    	//currentChart
    	g2 = currentChart.createGraphics();
    	g2.setColor(CHART_BG);
    	g2.fillRect(0, 0, CURRENT_WIDTH, HEIGHT);
    	g2.setFont(andale);
    	g2.setColor(Color.BLACK);
    	g2.drawLine(CURRENT_PLANE_XORIGIN, 15, CURRENT_PLANE_XORIGIN, 170);
    	g2.drawLine(217, 170, 217, 15);
    	g2.setColor(new Color(0, 51, 153));
    	g2.drawString("time", 102, 183);
    	g2.setColor(Color.LIGHT_GRAY);
    	g2.fillRect(CURRENT_PLANE_XORIGIN + 1, 15, CURRENT_PLANE_WIDTH, 156);
    	g2.setColor(Color.BLACK);
    	g2.drawLine(CURRENT_PLANE_XORIGIN, CURRENT_PLANE_YORIGIN, 217, CURRENT_PLANE_YORIGIN);
    	g2.setFont(andale.deriveFont(12));
    	g2.drawString(Integer.toString(-10), 4, 173);
    	for(int i = 1; i < 5; i++)
    		g2.drawString(Integer.toString((2*i-10)), 11, 173 - 15*i);
    	for(int i = 5; i < 10; i++)
    		g2.drawString(Integer.toString((2*i-10)), 15, 173 - 15*i);
    	g2.drawString("10", 11, 24);
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
    	map.put(imageNames[0], currentChart);
    	
    	//hardwareChart
    	g2 = hardwareChart.createGraphics();
    	g2.setColor(CHART_BG);
    	g2.fillRect(0, 0, HARDWARE_WIDTH, HEIGHT);
    	g2.setFont(andale);
    	g2.setColor(Color.BLACK);
    	g2.drawRect(HARDWARE_TEMP_LEFT_EDGE, 15, HARDWARE_TEMP_WIDTH, 129);
    	g2.drawRect(HARDWARE_BATT_LEFT_EDGE, 15, HARDWARE_BATT_WIDTH, 129);
    	g2.setFont(andale.deriveFont(4));
    	for(int i = 1; i < 5; i++)
    		g2.drawString("-" + Integer.toString(i*50 + 50) + "-", 14, 148 - 30*(i));
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
    	g2.drawString("(deg F)", 5, 183);
    	g2.drawString("battery", 73, 155);
    	g2.drawString("life (V)", 70, 169);
    	g2.dispose();
    	map.put(imageNames[1], hardwareChart);
    	
    	//speedometerChart;
    	g2 = speedometerChart.createGraphics();
    	g2.setColor(CHART_BG);
    	g2.fillRect(0, 0, SPEEDOMETER_WIDTH, HEIGHT);
    	g2.setFont(andale);
    	g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
    	g2.setPaint(new GradientPaint(50, 75, new Color(0, 51, 153), 225, 75, new Color(207, 46, 46)));
    	g2.fillArc(27, 8, 310, 310, 0, 180);
    	g2.setColor(CHART_BG);
    	g2.fillArc(36, 17, 292, 292, 0, 180);
    	g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_OFF);
    	g2.setColor(new Color(225, 225, 225));
    	g2.fillRect(154, 65, 45, 17);
    	g2.setColor(Color.BLACK);
    	g2.setFont(andale.deriveFont(12));
    	g2.drawString("m/sec", 159, 78);
    	g2.fillOval(SPEEDOMETER_NEEDLE_XORIGIN - 7, SPEEDOMETER_NEEDLE_YORIGIN - 7, 7, 7);
    	for(int i = 0; i < 10; i++){
    		g2.drawString(Integer.toString(5*i), 
    			(int)(50 + 126*(1 - Math.cos(20*i*Math.PI/180))), (int)(161 - 126*Math.sin(20*i*Math.PI/180)));
    	}
    	g2.setFont(andale);
    	g2.setColor(new Color(0, 51, 153));
    	g2.drawString("speed of \"arms\"", 129, 183);
    	g2.dispose();
    	map.put(imageNames[2], speedometerChart);
    	
    }
    
    /**Returns the image in {@link #map} that's associated with the given key.
     *@param s Key for desired image
     *@return The image associated with key s.*/
    public static Image getImage(String s){
    	return map.get(s);
    }
    
    /**Returns AndaleMono font.
     *@return andale The AndaleMono font.*/
    public static Font getFont(){
    	return andale;
    }
    
    
}