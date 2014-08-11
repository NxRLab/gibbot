
import java.lang.Math;
import java.awt.*;

/**A Gibbot object contains data on where the robot is on the board, to be translated to user interface.
 Right now its method for updating its own animation is a simulation, but a commented outline is above it
 for hypothetically getting the real coordinates from {@link GUISerialPort}, which also contains a dummy method now.
 All the get methods may not be neccessary (last four are currently unused) but they were left just in case.*/
public class Gibbot {
	
	/**Distance from motor to end of first link*/
	private final double ARM1W = 100;
	/**Distance from motor to end of second link*/
	private final double ARM2W = 100;
	/**Height of first link*/
	private final double ARM1H = 20;
	/**Height of second link*/
	private final double ARM2H = 20;

	/**Coordinates of center joint, ends of links*/
	private double pivotX, pivotY, arm1X, arm1Y, arm2X, arm2Y;
	/**Specifies size of circles at the joints of the gibbot animation*/
	private double radius = ARM1H/2; //NOTE: if height of arm1 and arm2 are different, this will need to be changed.
	/**Angle between links (currently unused in code)*/
	private double theta;

    /**Constructor initializes all coordinates. If initial coordinates need to be changed, make sure to change them
     *in {@link #reset}, as well.*/
    public Gibbot() {
    	pivotX = 250;
    	pivotY = 100;
    	arm2X = pivotX+ARM2W;
    	arm2Y = pivotY;
    	arm1X = pivotX-ARM2W;
    	arm1Y = pivotY;
  	
    }
    
    /**Returns x-coor of center joint (motor) in the animation (called by {@link BananaPanel1#paintComponent} 
    to draw a text bubble relative to it, and {@link BananaPanel1#actionPerformed} to check whether to continue
    animation).
    @return pivotX*/
    public double getPivotX(){
		return pivotX;
    }
    
    /**Returns y-coor of center joint (motor) in the animation (called by {@link BananaPanel1#paintComponent} 
    to draw a text bubble relative to it).
    @return pivotY;*/
    public double getPivotY(){
    	return pivotY;
    }
    
    /**Returns x-coor of end of first (initially left-most) link in the animation.
    @return arm1X;*/
    public double getArm1X(){
    	return arm1X;
    }
    
    /**Returns y-coor of end of first (initially left-most) link in the animation.
    @return arm1Y;*/
    public double getArm1Y(){
    	return arm1Y;
    }
    
    /**Returns x-coor of end of second (initially left-most) link in the animation.
    @return arm2X;*/
    public double getArm2X(){ 
    	return arm2X;
    }
    
    /**Returns y-coor of end of second (initially left-most) link in the animation.
    @return arm2Y;*/
    public double getArm2Y(){ 
    	return arm2Y;
    }
    
    /**Returns angle between the two links
    @return theta*/
    public double getTheta(){
    	return Math.atan(Math.abs(arm1X-pivotX)/Math.abs(arm1Y-pivotY))+Math.atan(Math.abs(arm2X-pivotX)/Math.abs(arm2Y-pivotY));
    }
    	
    
    /**This will update the animation based on real input from the robot*/
     	public void updateRealCoors(){
     	
     		double[] coors = GUISerialPort.getRealCoors();
     		
     		arm1X=(int)coors[0];
     		arm1Y=(int)coors[1];
     		pivotX=(int)coors[2];
     		pivotY=(int)coors[3];
     		arm2X=(int)coors[4];
     		arm2Y=(int)coors[5];
     }
     
     /**Animation simulation. Called by {@link BananaPanel1#actionPerformed}.
      *@param frameCount Stands for time value in motion equations
     */
     public void arcMotionUpdate(double frameCount){
    	
     		if((int)(frameCount/50)%2 == 0){             
     			arm1X += 8;							   
     			arm1Y = Math.sqrt(4*Math.pow(ARM1W,2)-Math.pow((arm1X-arm2X),2))+arm2Y;
     			pivotX += 4;
     			pivotY = Math.sqrt(Math.pow(ARM1W,2)-Math.pow((pivotX-arm2X),2))+arm2Y;
     		}
     		else{
     			arm2X += 8;
     			arm2Y = Math.sqrt(4*Math.pow(ARM1W,2)-Math.pow((arm2X-arm1X),2))+arm1Y;
     			pivotX += 4;
     			pivotY = Math.sqrt(Math.pow(ARM1W,2)-Math.pow((pivotX-arm1X),2))+arm1Y;
     		}
     }	
     			
	/**Draws gibbot animation, mostly to minimize clutter in {@link BananaPanel1#paintComponent}.
	Right now it is drawn as two thick lines and three circles.
	@param g passed from {@link BananaPanel1#paintComponent}
	*/
	public void draw(Graphics g){ 
	
		Graphics2D g2=(Graphics2D)g;
		
		g2.fillOval((int)pivotX-10, (int)pivotY-15, (int)ARM1H+12, (int)ARM1H+12);
		g2.fillOval((int)arm1X-15, (int)arm1Y-15, (int)ARM1H+12, (int)ARM1H+12);
		g2.fillOval((int)arm2X-15, (int)arm2Y-15, (int)ARM1H+12, (int)ARM1H+12);
		
		g2.setStroke(new BasicStroke((int)ARM1H));
		g2.drawLine((int)arm1X, (int)arm1Y, (int)pivotX, (int)pivotY);
		g2.drawLine((int)arm2X, (int)arm2Y, (int)pivotX, (int)pivotY);
	}
	
	/**Called by {@link BananaPanel1#actionPerformed} when the animated robot reaches the banana image. Not sure
	if this will be needed when using actual coordinates for animation.
	*/
	public void reset(){ 
		pivotX = 250;
    	pivotY = 100;
    	arm2X = pivotX+ARM2W;
    	arm2Y = pivotY;
    	arm1X = pivotX-ARM2W;
    	arm1Y = pivotY;
	}
}   
    
