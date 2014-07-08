/**
 * @(#)ContentSwipeTab.java
 *
 *
 * @author 
 * @version 1.00 2014/7/3
 */
import java.awt.*;

public interface ContentSwipeTab {
	
	public void updateForDrawing(double t);
		/*update data from i/o with robot to apply to relevent presentation form*/
	
	public void draw(Graphics g);
		/*draw, presumably with updates*/
}
	
	