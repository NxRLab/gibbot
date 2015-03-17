 
import java.awt.*;

/**A Banana object contains a banana image's coordinates.*/
  
public class Banana {

	/**X-coor of where the user has dragged the banana image*/
	private int x;
	/**X-coor of where the user has dragged the banana image*/
	private int y;
	
	/**Returns x-coor.
	@return x*/
	public int getX() {
		return x;
	}
	/**Returns y-coor.
	@return y*/
	public int getY() {
		return y;
	}
	
	/**Sets x-coor.
	@param cor Horizontal coordinate */
	public void setX(int cor){
		x=cor;
	}
	
	/**Sets y-coor.
	@param cor Vertical coordinate*/
	public void setY(int cor){
		y=cor;
	}
}