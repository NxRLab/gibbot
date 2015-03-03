

#define BUFFER_SIZE 4096	//the size of the input buffer, in items
#define N_VARS 3 		//the number of variables to write
#define MAXDATA 200

static volatile int r_buf[BUFFER_SIZE]; 	// holds the reference signal
static volatile int s_buf[BUFFER_SIZE]; 	// holds the sensor signal
static volatile int u_buf[BUFFER_SIZE]; 	// holds the control effort signal
static volatile unsigned int overflow = 0;	// the number of times the buffer overflows

static volatile unsigned int nsamples = 0; // the number of samples to record
static volatile unsigned int wsamples = 0; // the number of samples written

static volatile unsigned int w_pos = 0;	// position in the buffer from which to read
static volatile unsigned int r_pos = 0;	// position in the buffer from which to write


void streaming_begin(unsigned int nsamp)
{
	w_pos = 0;
	r_pos = 0;
	overflow = 0;
	wsamples = 0;
	nsamples = nsamp;
}


void streaming_record(int r, int s, int u)
{
	if(wsamples != nsamples)
	{
		r_buf[w_pos] = r;
		s_buf[w_pos] = s;
		u_buf[w_pos] = u;
		++w_pos;
		if(w_pos == BUFFER_SIZE)
		{
			w_pos = 0;
		}

		if(w_pos == r_pos) //an overflow has occurred
		{
			++overflow; //update the overflow count
				    //this means the next write will overwrite data
				    //so advance the r_pos by one to skip over the oldest data
			++r_pos;
			if(r_pos == BUFFER_SIZE)
			{
				r_pos = 0;
			}
		}
		else
		{	//if there was an overflow, then we skipped a sample, so only
			//increase the sample number when there is no overflow	
			++wsamples;
		}
	}
}

void streaming_write(void)
{
	char buffer[100];
	int rsamples = 0;

	//send the dimensions of the data
	sprintf(buffer,"%u %u\r\n",nsamples,N_VARS);
	write_string_UART(buffer,MAXDATA);
	for(rsamples = 0; rsamples != nsamples; ++rsamples)
	{
		//wait for data to become available
		while(w_pos == r_pos)
		{
			;
		}
		sprintf(buffer,"%d %d %d\r\n",r_buf[r_pos],s_buf[r_pos],u_buf[r_pos]);
		write_string_UART(buffer,MAXDATA);
		++r_pos;
		if(r_pos == BUFFER_SIZE)
		{
			r_pos = 0;
		}
	}
	
	if(overflow > 0)
	{
		sprintf(buffer,"\a%u overflows detected.",overflow);
		write_string_UART(buffer,MAXDATA);
	}
}
