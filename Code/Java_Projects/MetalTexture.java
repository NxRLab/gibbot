import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import javax.swing.*;

/*For board graphics*/

public class MetalTexture {
	
	BufferedImage img;
	
	public MetalTexture(){
	
	try {
			img = ImageIO.read(new File("C:\\Users\\K\\Downloads\\sheet_metal.jpg"));
		}
		catch(IOException e){System.out.println("not found");}
	}
		
	public Image getImage() {
		return img;
	}
}

