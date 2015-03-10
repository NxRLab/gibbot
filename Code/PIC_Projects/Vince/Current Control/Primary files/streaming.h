#ifndef _STREAMING_H_
#define _STREAMING_H_
/// @file streaming.h
/// @brief Allows the user to stream data over the UART.  Data is written to a buffer by high priority interrupts and
///	   sent over the UART at a lower priority
/// @author Matthew Elwin
/// @version 1.0
/// @date 2014-03-02


/// @brief  Start streaming data.  This means the streaming module will begin recording
///
/// @param nsamp The number of samples to record. After nsamp samples are recorded, calling stream_record will have no effect
/// @post streaming begins sets the number of samples that should be acquired
///	  every subsequent call to streaming_record will now save a sample in a buffer, until streaming_record has been called nsamp times
void streaming_begin(unsigned int nsamp);

/// @brief  Call this function in your control loops to send data to the PC for plotting.
///         Details:
///		Called from control loop interrupt to record values into the buffer
///	    	If there are still samples requested, this will record the data in the buffer, otherwise it will do nothing.
/// @param r - the reference signal
/// @param s - the sensor signal
/// @param u - the control effort
void streaming_record(int r, int s, int u);


/// @brief Called from the communication code to write the samples over the serial port. 
void streaming_write(void);

#endif
