#include "menu.h"
#include "core.h"
#include "current_control.h"
#include "streaming.h"
#include "initializeV6.h"

#define COAST 0
#define PWM 1
#define TUNE 2
#define TRACK 3
#define HOLD 4
#define TEST 5

static char buffer[200]; // used for storing incoming and outgoing requests
static const unsigned int BUF_SIZE = sizeof(buffer)/sizeof(buffer[0]);

#define MAXDATA 200

static const char assert_fail[] = "\\a%s:%d Assertion failed. %s "; // format string for failed assertions

/// @brief The sub-menu related to current control
static void current_menu(void);


/// @brief The sub-menu related to motion control
//static void motion_menu(void);


/// @brief The sub-menu related to diagnostics
static void diagnostic_menu(void);


/// @brief Sends a response back to the PC
///	   The response to send is stored in buffer.
///	   "\r\n" will be sent regardless of whether buf ends with "\r\n"
static void send_response(const char * buffer);

void menu_run(void)
{
        LED1 = 1;

	//core_gains_load(); //commented out until gain saving/loading is functional
	while(1)
	{
            __delay32(40000000);
		read_string_UART(buffer,BUF_SIZE);	//we expect the next character to be the menu command
		switch (buffer[0])
		{
			case 'i':
			{
                                LED2 = 1;
				current_menu();
				break;
			}
			case 'm':
			{
				//motion_menu();
				break;
			}
			case 'd':
			{
				diagnostic_menu();
				break;
			}
			case 's':
			{
				//core_gains_save();
				break;
			}
			case 'l':
			{
				//core_gains_load();
				break;
			}
                        case 255: // returned from read_string_uart
                        {
                            break;
                        }
			default: 
			{
				// The final status message starts with a '\a' to indicate an error
				write_string_UART("\\aUnrecognized Command.",MAXDATA);
				break;					   
			}
		}


                memset(buffer, 0, BUF_SIZE);
                sprintf(buffer, "core state: %d\r\n", core_state);
                write_string_UART(buffer,MAXDATA);

                memset(buffer, 0, BUF_SIZE);
                sprintf(buffer, "TRACK: %d\r\n", TRACK);
                write_string_UART(buffer,MAXDATA);

                memset(buffer, 0, BUF_SIZE);
                sprintf(buffer, "TUNE: %d\r\n", TUNE);
                write_string_UART(buffer,MAXDATA);

                memset(buffer, 0, BUF_SIZE);
                sprintf(buffer, "IDLE: %d\r\n", COAST);
                write_string_UART(buffer,MAXDATA);

                memset(buffer, 0, BUF_SIZE);
                sprintf(buffer, "random number: %d\r\n", -12);
                write_string_UART(buffer,MAXDATA);


#if 0

		// there are certain states we should never be in after running a menu command.
		// catch these errors and report them.  These are programming errors and indicate
		// a bug in the code if they are ever triggered.
		if (core_state == TRACK)
		{
			core_state = COAST;
			sprintf(buffer,assert_fail,__FILE__,__LINE__,"Invalid state TRACK");
			write_string_UART(buffer,MAXDATA);
		}
		else if(core_state == TUNE)
		{
			core_state = COAST;
			sprintf(buffer,assert_fail,__FILE__,__LINE__,"Invalid state TUNE");
			write_string_UART(buffer,MAXDATA);
		}
#endif
		write_string_UART("\r\n",MAXDATA); //send the acknowledgment that Matlab expects
	}
}


static void current_menu(void)
{
	read_string_UART(buffer,BUF_SIZE);
	switch (buffer[0])
	{
		case 'k':	// get and set the controller gains
		{
                        LED3 = 0;
                        core_state = COAST;	// don't change the gains while we could potentially be executing a controller

			// get the current gains as a string and write them to serial
			current_gains_sprintf(buffer);
			send_response(buffer);

			// receive the new gains from serial and set them
			read_string_UART(buffer,BUF_SIZE);
			current_gains_sscanf(buffer);
			break;
		}
		case 'r':  
		{
			core_state = COAST;			//stop whatever we were doing
			unsigned int nsamps = 50;		// the number of samples to record
			read_string_UART(buffer,BUF_SIZE);	// read the number of samples from the uart
			sscanf(buffer,"%d",&nsamps);
			
			streaming_begin(nsamps); 		// setup data streaming

			core_state = TUNE;			// start tuning mode
			streaming_write();			// write the data as it is generated
			core_state = COAST;			// stop moving
			break;
		}
		case 'b':
		{
			current_pwm_set(0);
			core_state = PWM;
			break;
		}
		case 'c':
		{
			core_state = COAST;
			break;
		}
		default:	//ignore unrecognized commands
		{
			write_string_UART("\\acurrent_menu: Unrecognized Command.",MAXDATA);
			break;
		}
	}
}

/*static void motion_menu(void) //motion menu removed - changes to this code need to be made before implementing this section of the menu
{//this section is very similar to the current control menu
	read_string_UART(buffer,BUF_SIZE);
	static  int length = 0; //keep track of the loaded motion trajectory length
	switch(buffer[0])
	{
		case 'k':
		{
			core_state = IDLE;
			
			// get the motion controller gains as a string and write them to serial
			motion_gains_sprintf(buffer);
			send_response(buffer);

			NU32_ReadUART1(buffer,BUF_SIZE);
			motion_gains_sscanf(buffer);
			break;
		}
		case 'l': // load trajectory
		{
			//read in the length of the trajectory
			int new_length = 0;
			NU32_ReadUART1(buffer,BUF_SIZE);
			sscanf(buffer,"%d",&new_length);
			if (new_length < 0)
			{
				; // trajectory loading aborted, do nothing
			}
			else if (!motion_trajectory_set(0,new_length-1))
			{
				sprintf(buffer,"\amotion_menu:l Trajectory too long");
				NU32_WriteUART1(buffer);
			}
			else if (new_length > 0)
			{
				length = new_length;
				NU32_WriteUART1("\r\n"); //signal to the pc to start sending the data
				//load the trajectory
				int i = 0, angle = 0;	
				for(i = 0; i != length; ++i)
				{
					NU32_ReadUART1(buffer,BUF_SIZE);
					sscanf(buffer,"%d",&angle);
					motion_trajectory_set(angle,i);
				}
			}
			break;
		}
		case 'x': // execute trajectory
		{
			if (length <= 0)
			{
				//we are expecting the number of extra samples to be sent, so read that
				NU32_ReadUART1(buffer,BUF_SIZE);
				//however, we cannot execute the trajectory
				NU32_WriteUART1("\aCannot Execute, No Trajectory Loaded");
			}
			else
			{
				int xtra = 0;
				NU32_ReadUART1(buffer,BUF_SIZE);
				sscanf(buffer,"%d",&xtra);	//the number of extra samples
				motion_trajectory_reset(LAST,0);//start the trajectory from the beginning, hold at the end
				streaming_begin(length+xtra);	// setup the number of data samples	
				core_state = TRACK;		// track the trajectory
				streaming_write();		// stream the data to the PC
				core_state = HOLD;		// hold the last position
			}
			break;
		}
		case 'h': // hold the current position
		{
			int nsamples = 0;
			//read the number of samples
			NU32_ReadUART1(buffer,BUF_SIZE);
			sscanf(buffer,"%d",&nsamples);
			
			motion_trajectory_reset(NOW,0); // hold at the current angle
			streaming_begin(nsamples);  // setup the number of data samples to stream
			core_state = HOLD;	    // begin holding
			streaming_write();	    // stream the data to the PC
			break;
		}
		case 'g': // goto a position
		{
			int abort = -1;
			NU32_ReadUART1(buffer,BUF_SIZE);
			sscanf(buffer,"%d",&abort);
			if(abort < 0) //the command has been aborted
			{
				;
			}
			else
			{
				//read the angle
				int angle = 0;
				NU32_ReadUART1(buffer,BUF_SIZE);
				sscanf(buffer,"%d",&angle);

				// read the number of samples
				int nsamples = 0;
				NU32_ReadUART1(buffer,BUF_SIZE);
				sscanf(buffer,"%d",&nsamples);

				// set the holding angle
				motion_trajectory_reset(ANGLE,angle);
				//begin streaming and start the goto
				streaming_begin(nsamples);
				core_state = HOLD;
				streaming_write();
			}
			break;
		}
		case 's': // stop trajectory
		{
			core_state = IDLE;
			break;
		}
		default:
		{
			NU32_WriteUART1("\amotion_menu: Unrecognized Command"); 
			break;
		}
	}
}

*/

static void diagnostic_menu(void)
{
	read_string_UART(buffer,BUF_SIZE);
	switch(buffer[0])
	{
		/*case 'e':
		{
			read the encoder count
			sprintf(buffer,"%d\r\n",core_encoder_read());
			write_string_UART(buffer,MAXDATA);
			break;
		}
		case 'd':
		{
			sprintf(buffer,"%d\r\n",motion_angle());
			NU32_WriteUART1(buffer);
			break;
		}
                
		case 'r':
		{
			//reset the encoder count
			//core_encoder_reset();
			break;
		}
                */
		case 'p':
		{
			int duty = 0;
			read_string_UART(buffer,BUF_SIZE);
			sscanf(buffer,"%d",&duty);
			if (duty < -100 || duty > 100)
			{
				write_string_UART("\\adiagnostic_menu: Enter a duty cycle between -100 and 100",MAXDATA);
			}
			else
			{
				current_pwm_set(duty);
				core_state = PWM;
			}
			break;
		}
		case 'a': // read the adc ticks and return them
		{
			sprintf(buffer,"%d\r\n",core_adc_read());
			write_string_UART(buffer,MAXDATA);
			break;
		}
		case 'i': //read the current in mA and return it
		{
			sprintf(buffer,"%d\r\n",current_amps_get());
			write_string_UART(buffer,MAXDATA);
			break;
		}
		case 'x':
		{
			sprintf(buffer,"%d\r\n",core_state);
			write_string_UART(buffer,MAXDATA);
			break;
		}
		default:
		{
			write_string_UART("\\adiagnostic_menu: Unrecognized Command.",MAXDATA);
			break;
		}
	}
}


void send_response(const char * buf)
{
	write_string_UART(buf,MAXDATA);
	
	// Make this work regardless of whether buffer ends with "\r\n". Only print it if missing.
	if(buf[strlen(buf) - 1] != '\n')
	{
		write_string_UART("\r\n",MAXDATA);
	}
}
