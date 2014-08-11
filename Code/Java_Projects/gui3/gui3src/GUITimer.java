
import java.awt.event.*;
import javax.swing.*;

/**GUITimer is a wrapper class for Swing Timer; gets started by {@link GibbotGUI3} and is used for animations. 
 *{@link GUILayeredPane#actionPerformed} listens for timer fires and calls {@link GUISerialPort#update} in 
 *response, so that individual components don't all have to. Any object in the GUI that adds itself as an
 *ActionListener using {@link addActionListener} 'hears' the timer fires, and does with them what it wishes. */
public class GUITimer {
	
	/**Timer object that is wrapped by this class*/
	private static Timer timer;
	/**How many timer fires per one serial update (to limit bugs in serial comm without slowing down the whole program)*/
	private static int serialFactor = 10;
	/**Time, in milliseconds, between each timer fire*/
	private static int millisPerFrame = 33;
	
    /**Starts the timer object with initially no ActionListener objects associated with it
    */
    public static void start(){
    	timer = new Timer(millisPerFrame, null);
    	timer.start();
    }
    
    /**Objects in the GUI that need to 'hear' timer fires to run animations/updates call this method
    in their constructor.
    @param listener Listener to be added (must extend ActionListener interface)*/
    public static void addActionListener(ActionListener listener){
    	timer.addActionListener(listener);
    }
    
    /**Currently unused in code, but can be used if component should not 'hear' timer fires anymore for
    some reason.
    @param listener Listener to be added (must extend ActionListener interface)*/
    public static void removeActionListener(ActionListener listener){
    	timer.removeActionListener(listener);
    }
    
    /**Returns {@link #serialFactor}
    @return serialFactor*/
    public static int getSerialFactor(){
    	return serialFactor;
    }
    
    /**Returns {@link #millisPerFrame}
    @return millisPerFrame*/
    public static int getMillisPerFrame(){
    	return millisPerFrame;
    }
    
    
}