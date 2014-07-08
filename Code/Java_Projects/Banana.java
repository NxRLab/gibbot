/**
 * @(#)Banana.java
 *
 * Banana application
 *
 * @author 
 * @version 1.00 2014/6/30
 */
 
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import javax.swing.*;

/*Contains the data on where the robot is assigned to move and image data for the user interface*/
public class Banana {

	private int x;
	private int y;
	BufferedImage img;

	public Banana() {
		
		try {
			img = ImageIO.read(new File("C:\\Users\\K\\Downloads\\bananas_clip_art_edit.png"));
		}
		catch(IOException e){System.out.println("not found");}
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
		return img;
	}
}