/**
 * @(#)ButtonPanel.java
 *
 *
 * @author 
 * @version 1.00 2014/8/15
 */
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.nio.*;
import java.nio.charset.*;
import java.sql.Timestamp;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Date;
import javax.swing.*;
import jssc.*;

public class ButtonPanel extends JPanel{
	
	private LogButton log = new LogButton();
	private ToBytesButton bytes = new ToBytesButton();
	private ToValsButton vals = new ToValsButton();

    public ButtonPanel() {
    	add(log);
    	add(bytes);
    	add(vals);
    }
    
    public class LogButton extends JButton implements ActionListener{
	
		private final String START = "Start logging";
		private final String STOP = "Stop logging";
	
		private boolean logging;

    	public LogButton() {
    		super("Start logging");
	    	addActionListener(this);
    	}
    
	    public void actionPerformed(ActionEvent evt){
    		
	    	if(logging){
    			this.setText(START);
    			//DebuggerGUITimer.removeActionListener(something);
    			logging = false;
    			bytes.setEnabled(true);
    			vals.setEnabled(true);
	    	}
    	
    		else{
    			this.setText(STOP);
    			//DebuggerGUITimer.addActionListener(something);
	    		logging = true;
	    		bytes.setEnabled(false);
	    		vals.setEnabled(false);
    		}
    	}
    }
    
    public class ToBytesButton extends JButton implements ActionListener{

	    public ToBytesButton() {
    		super("Send data to bytes file");
    		addActionListener(this);
	    	setEnabled(false);
    	}
	    
	    public void actionPerformed(ActionEvent evt){
	    	setEnabled(false);
	    	SwingUtilities.invokeLater(new Runnable(){
	    		public void run(){
	    			recordAsReadableBytes();
	    		}
	    	});
	    	setEnabled(true);
	    }
   		 
   		 public void recordAsReadableBytes() {
	    	
	    	final String SOURCE_FILE_NAME = DebuggerGUISerialPort.OUTPUT_FILE_NAME;
    		final String READABLE_BYTES_OUTPUT_FILE_NAME = "outputs_as_bytes.txt";
    		
    		byte[] time = new byte[23];
    		byte[] lineLength = new byte[1];
    		byte[] data;
	    	
	    	BufferedInputStream bis = null;
    		OutputStreamWriter osw = null;
    		
    		int bytesInLine;
    		
    		final int CR = 13; //carriage return
			final int NL = 10; //new line
			final int SPACE = 32;
			final String ASTERIX = "*";
    	
    		try{
    			bis = new BufferedInputStream(new FileInputStream(SOURCE_FILE_NAME));
    			osw = new OutputStreamWriter
	    				(new BufferedOutputStream
    						(new FileOutputStream(READABLE_BYTES_OUTPUT_FILE_NAME)));
    		}
    	
	    	catch(FileNotFoundException e){
    			System.out.println(e);
    		}
    	
	    	try{	
    			while(true){
    				if(bis.read() == -1){
    					System.out.println("broke");
    					osw.close();
						bis.close();
    					break;
    				}
    				System.out.println("didn't break");	
    				bis.read(time);
    				System.out.println(new String(time));    					
    				osw.write(new String(time));
    				osw.write(SPACE);
    				System.out.println("written"); 			
    			
	    			bis.read(lineLength);
	    			bytesInLine = lineLength[0];
	    			data = new byte[bytesInLine];
	    			System.out.println(bytesInLine);
	    			bis.read(data);
    				String first = Integer.toString(data[0]);
    				first = (first.equals("42")) ? ASTERIX : first;
    				osw.write(first);
    				osw.write(SPACE);

	    			for(int i = 1; i < bytesInLine; i++){
    					osw.write(Integer.toString(data[i]));
    					osw.write(SPACE);
    				}
    				osw.write(CR);
	    			osw.write(NL);
					
    			}
    		}	
    	
    		catch(IOException e){
    			e.printStackTrace();
    		}
    	}
    }
    
    public class ToValsButton extends JButton implements ActionListener{

	    public ToValsButton() {
    		super("Send data to numerical values file");
    		setEnabled(false);
	    }
	    
	    public void actionPerformed(ActionEvent evt){
	    	setEnabled(false);
	    	SwingUtilities.invokeLater(new Runnable(){
	    		public void run(){
	    			recordAsReadableValues();
	    		}
	    	});
	    	setEnabled(true);
	    }
	    
	    public void recordAsReadableValues() {
    		
	    	final String SOURCE_FILE_NAME = DebuggerGUISerialPort.OUTPUT_FILE_NAME;
    		final String READABLE_VALUES_OUTPUT_FILE_NAME = "outputs_as_bytes.txt";
    	
	    	byte[] time = new byte[23];
	    	byte[] lineLength = new byte[0];
    		byte[] intVal = new byte[2];
    		byte[] floatVal = new byte[4];
    	
    		ByteBuffer bb;
    		BufferedInputStream bis = null;
	    	OutputStreamWriter osw = null;
    	
    		int bytesInLine;
    	
    		final int CR = 13; //carriage return
			final int NL = 10; //new line
			final int SPACE = 32;
			final String ASTERIX = "*";
    	
	    	try{
    			bis = new BufferedInputStream(new FileInputStream(SOURCE_FILE_NAME));
    			osw = new OutputStreamWriter
    						(new BufferedOutputStream
    								(new FileOutputStream(READABLE_VALUES_OUTPUT_FILE_NAME)));
    		}	
    	
	    	catch(FileNotFoundException e){
    			System.out.println(e);
    		}
    		
	    	try{	
    			while(true){
    				
    				if(bis.read() == -1){
    					osw.close();
    					bis.close();
    					break;
    				}
    				
    				bis.read(time);
    				osw.write(new String(time));
    				osw.write(SPACE);	 			
    			
	    			bis.read(lineLength);
	    			bytesInLine = lineLength[0];
	    			data = new byte[bytesInLine];
	    			bis.read(data);
    				String first = Integer.toString(data[0]);
    				first = (first.equals("42")) ? ASTERIX : first;
    				osw.write(first);
    				osw.write(SPACE);
    				
    				int offset = 1;
    			
	    			for(int i = 0; i < 3; i++){
    					if(bytesInLine > 1){
    						bb = ByteBuffer.wrap(data, offset, 2);
    						osw.write(Integer.toString(bb.getInt()));
    						osw.write(SPACE);
    						bytesInLine -= 2;
    						offset += 2;
	    				}
    				}
    				
	    			if(bytesInLine > 3){
    					for(int i = 0; i < 16; i++){
    						if(bytesInLine > 3){
    							bb = ByteBuffer.wrap(data, offset, 4);
    							osw.write(Float.toString(bb.getFloat()));
    							osw.write(SPACE);
    							bytesInLine -= 4;
    							offset += 4;
	    					}
    					}
    				}
    				
    				//deal w/ extra bytes here if desired
    			
	    			osw.write(CR);
    				osw.write(NL);
    				osw.flush();
    			
    			}  
			}
		
			catch(IOException e){
    			System.out.println(e);
    		}
    	}
	}
}

