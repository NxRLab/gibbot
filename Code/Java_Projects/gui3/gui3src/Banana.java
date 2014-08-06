/**
 * @(#)Banana.java
 *
 * Banana application
 *
 * @author 
 * @version 1.00 2014/6/30
 */
 
import java.awt.*;

/*Contains the data on where the robot is assigned to move, and image data for the user interface*/
 
public class Banana {
	
	private Image banana;

	private int x;
	private int y;
	
	public Banana() {
		banana = ImageHandler.getImage("banana");
        x = 0;
        y = 0;
	}
	
	public int getX() {
		return x;
	}
	
	public int getY() {
		return y;
	}
	
	public void setX(int cor){
		x=cor;
	}
	
	public void setY(int cor){
		y=cor;
	}
	
	public Image getImage() {
		return banana;
	}
}