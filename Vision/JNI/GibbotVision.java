import java.util.concurrent.TimeUnit;
import java.awt.image.BufferedImage;

class GibbotVision {
    static {
        System.loadLibrary("GibbotVisionDLL");
    }

    public native boolean startCameras();
	public native boolean stopCameras();
	public native double[] getGibbotData();

    public static void main(String[] args) {
		GibbotVision viz = new GibbotVision();

		// start the cameras
		System.out.println("started?: " + viz.startCameras());
		

		// wait a sec so frames can be captures
		try {
			TimeUnit.SECONDS.sleep(1);
		} catch (Exception e) {
		
		}

		// print coordinate positions in pixels
		double[] pos =  viz.getGibbotData();
		System.out.println("position?: " + pos.length);
		for(int i = 0; i < pos.length; i++) {
			System.out.println(pos[i]);
		}


		// stop the cameras
		System.out.println("stopped?: " + viz.stopCameras());
    }
}
