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
    	
    	setLayout(new GridBagLayout());
    	
    	GridBagConstraints c = new GridBagConstraints();
    	
    	c.anchor=GridBagConstraints.CENTER;
    	
    	c.weightx = 1;
    	
    	c.weighty = .4;
    	c.gridy = 0;
    	c.anchor = GridBagConstraints.EAST;
    	add(new SelectorPanel(), c);
    	
    	c.weighty = .3;
    	c.anchor = GridBagConstraints.WEST;
    	
    	c.gridy = 1;
    	add(log, c);
    	c.gridy = 2;
    	add(bytes, c);
    	c.gridy = 3;
    	add(vals, c);
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
    			DebuggerGUISerialPort.stopLogging();	    		
    			this.setText(START);
    			logging = false;
    			bytes.setEnabled(true);
    			vals.setEnabled(true);
	    	}
    	
    		else{
    			DebuggerGUISerialPort.startLogging();
    			this.setText(STOP);
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
    		
    		byte[] byteCount = new byte[1];
    		byte[] time;
    		byte[] data;
	    	
	    	BufferedInputStream bis = null;
    		OutputStreamWriter osw = null;

    		int bytesInLine;
    		int bytesInTimestamp;
    		
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
    					osw.close();
						bis.close();
						System.out.println("done");
    					break;
    				}
    				
    				bis.read(byteCount);
	    			bytesInTimestamp = byteCount[0];
	    			time = new byte[bytesInTimestamp];
    					
    				bis.read(time);   					
    				osw.write(new String(time));
    				osw.write(SPACE); 			
    			
	    			bis.read(byteCount);
	    			bytesInLine = byteCount[0];
	    			if(bytesInLine < 0)
	    				bytesInLine += 256;
	    			data = new byte[bytesInLine + 1];
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
	    			osw.write(CR);
	    			osw.write(NL);
	    			osw.flush();
					
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
    		addActionListener(this);
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
    		final String READABLE_VALUES_OUTPUT_FILE_NAME = "outputs_as_values.txt";
    	
	    	byte[] byteCount = new byte[1];
	    	byte[] time;
	    	byte[] data;
    	
    		ByteBuffer bb;

    		BufferedInputStream bis = null;
	    	OutputStreamWriter osw = null;
    	
    		int bytesInLine;
    		int bytesInTimestamp;
    	
    		final int CR = 13; //carriage return
			final int NL = 10; //new line
			final String ASTERIX = "*";
			final String ASTERIX_STRING = "42";
			final int SPACE = 32;
			final String SPACE_STRING = " ";
			final String COMMA = ",";
    	
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
    					System.out.println("done");
    					break;
    				}
    				
    				bis.read(byteCount);
	    			bytesInTimestamp = byteCount[0];
	    			time = new byte[bytesInTimestamp];
    				
    				bis.read(time);
    				osw.write(new String(time));
    				osw.write(SPACE);	 			
    			
	    			bis.read(byteCount);
	    			bytesInLine = byteCount[0];
	    			if(bytesInLine < 0)
	    				bytesInLine += 256;
	    			data = new byte[bytesInLine + 1];
	    			bis.read(data);
    				String first = Integer.toString(data[0]);
    				first = (first.equals(ASTERIX_STRING)) ? ASTERIX : SPACE_STRING;
    				osw.write(first);
    				osw.write(SPACE);
    				
    				int offset = 1;
    			
	    			for(int i = 0; i < 3; i++){
    					if(bytesInLine > 1){
    						bb = ByteBuffer.wrap(data, offset, 2);
    						bb.order(ByteOrder.LITTLE_ENDIAN);
    						osw.write(Integer.toString(bb.getChar()));
    						osw.write(COMMA);
    						osw.write(SPACE);
    						bytesInLine -= 2;
    						offset += 2;
	    				}
    				}
    				
	    			if(bytesInLine > 3){
    					for(int i = 0; i < 16; i++){
    						if(bytesInLine > 3){
    							bb = ByteBuffer.wrap(data, offset, 4);
    							bb.order(ByteOrder.LITTLE_ENDIAN);
    							osw.write(Float.toString(bb.getFloat()));
    							osw.write(COMMA);
    							osw.write(SPACE);
    							bytesInLine -= 4;
    							offset += 4;
	    					}
    					}
    				}
    				
    				//deal w/ extra bytes here if desired
    			
	    			osw.write(CR);
    				osw.write(NL);
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

