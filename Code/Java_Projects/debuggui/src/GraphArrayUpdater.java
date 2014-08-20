/**
 * @(#)GraphArrayUpdater.java
 *
 *
 * @author 
 * @version 1.00 2014/8/20
 */

import java.awt.*;
import java.awt.event.*;
import java.util.Arrays;

public class GraphArrayUpdater{
	
	public static int[] graphChoices = new int[19];
	public static double[] scales = new double[19];
	
	private static int par = 0;
	private static int[] angles = new int[3];
	private static float[] floats = new float[16];
	
	private static final int N = 20;
	public static int[][] odds = new int[19][N];
	public static int[][] evens = new int[19][N];
	public static int[][] yvals = new int[19][N];
	
	public static int currentHeight;
	public static int marginOfGraphs;
	
	private static UpdateListener listener = new UpdateListener();
	
	public static void start(){

		DebuggerGUITimer.addActionListener(listener);
	}
	
	private static class UpdateListener implements ActionListener{

	    public void actionPerformed(ActionEvent evt){
	    	
	    	angles = DebuggerGUISerialPort.getAngles();
	    	floats = DebuggerGUISerialPort.getFloats();
	    	par = par == 0 ? 1 : 0;
	    	updateArrays();
	    	
	    }
	    
	    public void updateArrays(){
	    	
	    	for(int i = 0; i < 3; i++){
	    		if(graphChoices[i] != 0){
	    			if(par == 0){
	    				evens[i][0] = (int)(currentHeight - marginOfGraphs - angles[i]*scales[i]);
		    			for(int j = 0; j < N - 1; j++)
		    				if(odds[i][j] == 0)
		    					evens[i][j+1] = currentHeight - marginOfGraphs;
		    				else
	    						evens[i][j+1] = odds[i][j];
	    			}
	    			else{
	    				odds[i][0] = (int)(currentHeight - marginOfGraphs - angles[i]*scales[i]);
	    				for(int j = 0; j < N - 1; j++)
	    					if(odds[i][j] == 0)
		    					odds[i][j+1] = currentHeight - marginOfGraphs;
		    				else
	    						odds[i][j+1] = evens[i][j];
	    			}
	    		}
	    	}
	    	
	    	for(int i = 3; i < 19; i++){
	    		if(graphChoices[i] != 0){
	    			if(par == 0){
	    				evens[i][0] = (int)(currentHeight - marginOfGraphs - floats[i - 3]*scales[i - 3]);
	    				System.out.println(scales[i - 3]);
		    			for(int j = 0; j < N - 1; j++)
	    					if(odds[i][j] == 0)
		    					evens[i][j+1] = currentHeight - marginOfGraphs;
		    				else
	    						evens[i][j+1] = odds[i][j];
	    			}
	    			else{
	    				odds[i][0] = (int)(currentHeight - marginOfGraphs - floats[i - 3]*scales[i-3]);
	    				System.out.println(scales[i - 3]);
	    				for(int j = 0; j < 19; j++)
	    					if(odds[i][j] == 0)
		    					odds[i][j+1] = currentHeight - marginOfGraphs;
		    				else
	    						odds[i][j+1] = evens[i][j];
	    			}
	    		}
	    	}
	    	
	    	yvals = par == 0 ? evens : odds;
	    }
	}
	    
	public static int getN(){
	   	return N;
	} 
	
	public static void setScale(int i, double val){
		scales[i] = val;
	}
}