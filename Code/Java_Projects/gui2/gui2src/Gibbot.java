/**
 * @(#)Gibbot.java
 *
 *
 * @author Katie
 * @version 1.00 2014/6/30
 */
import java.lang.Math;
import java.awt.*;
import java.awt.geom.*;

/*Contains data on where the robot is to be translated to user interface*/
public class Gibbot {
	
	private double pivotX, pivotY, armX, armY, legX, legY;
	private final double ARMW = 100;
	private final double LEGW = 100;
	private final double ARMH = 20;
	private final double LEGH = 20;
	private double radius = ARMH/2; //NOTE: if height of arm and leg are different, this will need to be changed.
	private double theta;
	private RoundRectangle2D arm = new RoundRectangle2D.Double();
	private RoundRectangle2D leg = new RoundRectangle2D.Double();
	private Shape rotatedArm;
	private Shape rotatedLeg;
	
	AffineTransform transform = new AffineTransform();

    public Gibbot() {
    	pivotX = 250;
    	pivotY = 100;
    	legX = pivotX+LEGW;
    	legY = pivotY;
    	armX = pivotX-LEGW;
    	armY = pivotY;
    	
    	
    }
    
    public double getPivotX(){
		return pivotX;
    }
    
    public double getPivotY(){
    	return pivotY;
    }
    
    public double getArmX(){
    	return armX;
    }
    
    public double getArmY(){
    	return armY;
    }
    
    public double getLegX(){ //Calculate third point based on known position of other two, length of arms, and angle b/t them
    	return legX;
    }
    
    public double getLegY(){ //Ditto
    	return legY;
    }
    
    public double getTheta(){
    	return Math.atan(Math.abs(armX-pivotX)/Math.abs(armY-pivotY))+Math.atan(Math.abs(legX-pivotX)/Math.abs(legY-pivotY));
    }
    	
    
    /***This will update the animation based on real input from the robot***
     *	public void updateRealCoors(double x1, double y1, double x2, double y2, double x3, double y3){
    /*	
     *		armX=x1;
     *		armY=y1;
     *		pivotX=x2;
     *		pivotY=y2;
     *		legX=x3;
     *		legY=y3;}*/
     
     public void arcMotionUpdate(double frameCount){
    	
     		if((int)(frameCount/50)%2==0){             //frameCount/(ARMW/2)
     			armX+=8;							   //+=(2*ARMW)/framespersec
     			armY=Math.sqrt(4*Math.pow(ARMW,2)-Math.pow((armX-legX),2))+legY;
     			pivotX+=4;
     			pivotY=Math.sqrt(Math.pow(ARMW,2)-Math.pow((pivotX-legX),2))+legY;
     		}
     		else{
     			legX+=8;
     			legY=Math.sqrt(4*Math.pow(ARMW,2)-Math.pow((legX-armX),2))+armY;
     			pivotX+=4;
     			pivotY=Math.sqrt(Math.pow(ARMW,2)-Math.pow((pivotX-armX),2))+armY;
     		}
     }	
     			
     
	
	public void draw(Graphics g){ //Handles its own redrawing so the panel class doesn't have to deal with all the variables
	
		Graphics2D g2=(Graphics2D)g;
		
		g2.fillOval((int)pivotX-10, (int)pivotY-15, (int)ARMH+12, (int)ARMH+12);
		g2.fillOval((int)armX-16, (int)armY-15, (int)ARMH+12, (int)ARMH+12);
		g2.fillOval((int)legX-10, (int)legY-15, (int)ARMH+12, (int)ARMH+12);
		
		g2.setStroke(new BasicStroke((int)ARMH));
		g2.drawLine((int)armX, (int)armY, (int)pivotX, (int)pivotY);
		g2.drawLine((int)legX, (int)legY, (int)pivotX, (int)pivotY);
		
	}
	
	public double calcRotAngle(double x, double y){
		
		if(x==pivotX&&y>pivotY)
			return Math.PI/-2;
		
		if(x==pivotX&&y<pivotY)
			return Math.PI/2;
		
		if((x<pivotX))
			return(Math.PI+Math.atan((-y+pivotY)/(x-pivotX)));
		else
			return Math.atan((-y+pivotY)/(x-pivotX));
	}
	
	public void reset(){ //For when it reaches the bananas
		pivotX = 250;
    	pivotY = 100;
    	legX = pivotX+LEGW;
    	legY = pivotY;
    	armX = pivotX-LEGW;
    	armY = pivotY;
	}
	}   
    
