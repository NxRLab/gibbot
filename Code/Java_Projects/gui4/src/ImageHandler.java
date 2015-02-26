
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
	
	/**Background color for chart animations*/
	private static final Color CHART_BG = GibbotGUI3.SECONDARY_GLOBAL_BG;
	
	/**Font used throughout the GUI*/
	private static Font andale;
	private static Font digital;
	
	
	/** Array of supported extensions for the images */
    static final String[] EXTENSIONS = new String[]{
    	"png", "jpg", "jpeg" // and other formats you need
    };
    
//http://stackoverflow.com/questions/11300847/load-and-display-all-the-images-from-a-folder
	
    /**Filter to identify images based on their extensions */
	static final FilenameFilter IMAGE_FILTER = new FilenameFilter(){
        public boolean accept(final File dir, final String name) {
            for (final String ext : EXTENSIONS) {
                if (name.endsWith("." + ext)) {
                    return (true);
                }
            }
            return (false);
        }
	};
	
	
	/**Holds images in a map where each has a key of type String, so that other classes can easily access them.*/
	private static HashMap<String, Image> map = new HashMap<String, Image>();
	
    /**Loads png image files and AndaleMono font*/
    public static void loadImages(File directory){ 
    	if(directory.isDirectory()){ // make sure it is a valid directory
			for(final File f : directory.listFiles(IMAGE_FILTER)){
				try {
					BufferedImage img = ImageIO.read(f);
					map.put(f.getName(), img);
				}
				catch(IOException e) {
					System.out.println(f.getName() + " not found");
					map.put(f.getName(), null);
				}
			}
			
		}
		try{
    		stream = new BufferedInputStream(new FileInputStream("AndaleMono.ttf"));
    		andale = (Font.createFont(Font.TRUETYPE_FONT, stream)).deriveFont(Font.BOLD, 12);
    		stream = new BufferedInputStream(new FileInputStream("DS-DIGIT.TTF"));
    		digital = (Font.createFont(Font.TRUETYPE_FONT, stream)).deriveFont(Font.BOLD, 12);
    	}
    	catch(Exception e){
    		System.out.println(e);
    		andale = new Font("Serif", Font.PLAIN, 15);
    		digital = new Font("Serif", Font.PLAIN, 15);
    	}
    }

    
    
    /**Returns the image in {@link #map} that's associated with the given key.
     *@param s Key for desired image
     *@return The image associated with key s.*/
    public static Image getImage(String s){
    	return map.get(s);
    }
    
    /**Returns AndaleMono font.
     *@return andale The AndaleMono font.*/
    public static Font getAndaleFont(){
    	return andale;
    }
    public static Font getDigitalFont(){
    	return digital;
    }
    
}