// Misc Functions
#include <jvp002.h>

// See page 32 of CPU.pdf for description of registers,
void CP0Init(void)
{
	int temp_val;
    /*
    *   To set to Multi-vectored Interrupt Mode
    *   EBase ? 00000
    *   VS<4:0> bits (IntCtl<9:5>) ? 00000
    *   IV bit (Cause<23>) = 1
    *   EXL bit (Status<1>) = 0
    *   BEV bit (Status<22>) = 0
    *   MVEC bit (INTCON<12>) = 1       Taken care of in interrupts.c
    *   IE bit (Status<0>) = 1
    */


    // Set the exception base address to 0xBD000000
    temp_val = _CP0_GET_EBASE();
    temp_val |= (0xBD0000000 >> 2);
    _CP0_SET_STATUS(temp_val);

    // Set the spacing between each interrupt vector as 512
    temp_val = _CP0_GET_INTCTL();
    temp_val |= (0x10000000 >> 22);
    _CP0_SET_STATUS(temp_val);

    // Set the IV (interrupt vector bit)
    temp_val = _CP0_GET_CAUSE();
    temp_val |= 0x00800000;
    _CP0_SET_CAUSE(temp_val);

    // Clear the EXL (exception level bit, bit 2)
    temp_val = _CP0_GET_STATUS();
    temp_val &= 0xFFFFFFFD;
    _CP0_SET_STATUS(temp_val);

    // Clear the BEV (bootstrap exception vector control bit)
    temp_val = _CP0_GET_STATUS();
    temp_val &= 0xFFBFFFFF;
    _CP0_SET_STATUS(temp_val);

     // Set Interrupt Enable bit
    temp_val = _CP0_GET_STATUS();
    temp_val |= 0x00000001;
    _CP0_SET_STATUS(temp_val);
     
}

// Set up the interrupts
void INTInitialize(void)
{

    // Disable all interrupts
    IEC0 = 0x00000000;
    IEC1 = 0x00000000;
    IEC2 = 0x00000000;

    // Configure as multi-vector interrupt
    INTCONbits.MVEC = 1;
    INTCONbits.TPC = 0x00;      // Disable the interrupt proximity timer
       
    // If enabled, external interrupts caused on the falling edge
    INTCONbits.INT4EP = 0;
    INTCONbits.INT3EP = 0;
    INTCONbits.INT2EP = 0;
    INTCONbits.INT1EP = 0;
    INTCONbits.INT0EP = 0;

    // Clear the Interrupt Flag status register
    IFS0 = 0x00000000;
    IFS1 = 0x00000000;
    IFS2 = 0x00000000;

    // Set all interrupt priorities and sub-priorities to 0
    IPC0 = 0x00000000;
    IPC1 = 0x00000000;
    IPC2 = 0x00000000;
    IPC3 = 0x00000000;
    IPC4 = 0x00000000;
    IPC5 = 0x00000000;
    IPC6 = 0x00000000;
    IPC7 = 0x00000000;
    IPC8 = 0x00000000;
    IPC9 = 0x00000000;
    IPC10 = 0x00000000;
    IPC11 = 0x00000000;
    IPC12 = 0x00000000;
}


void wait(int num)
{
	int i = 0;	
	while(i<num) i++;
}

// In this version, we need A and another button pressed to change state
int CheckButtons(void)
{
	int ret;
	int i;
	int total = -1;
	if(BUTTON_A == 0 || BUTTON_B == 0 || BUTTON_C == 0 || BUTTON_D == 0)
	{
		if(BUTTON_A == 0 && BUTTON_B == 0)
		{
			while(total != 0)
			{
				total = 0;
				for(i=0;i<1000;i++)	
					total += BUTTON_B;
			}
			while(total != 1000)
			{
				total = 0;
				for(i=0;i<1000;i++)	
					total += BUTTON_B;
			}
			wait(1000);		// wait for debounce
			ret = 1;
		}
		else if(BUTTON_A == 0 && BUTTON_C == 0)
		{
			while(total != 0)
			{
				total = 0;
				for(i=0;i<1000;i++)	
					total += BUTTON_C;
			}
			while(total != 1000)
			{
				total = 0;
				for(i=0;i<1000;i++)	
					total += BUTTON_C;
			}
			wait(1000);
			ret = 2;
		}
		else if(BUTTON_A == 0 && BUTTON_D == 0)
		{
			while(total != 0)
			{
				total = 0;
				for(i=0;i<1000;i++)	
					total += BUTTON_D;
			}
			while(total != 1000)
			{
				total = 0;
				for(i=0;i<1000;i++)	
					total += BUTTON_D;
			}
			wait(1000);
			ret = 3;
		}
		// Only A is pressed, which is command button
		else
			ret = 0;
	}
	else	// no buttons pushed
		ret = -1;

	return ret;
}


void SetupButtons(void)
{
	// Buttons are input
	TRISGbits.TRISG15 = 1;
	TRISAbits.TRISA0 = 1;
	TRISAbits.TRISA1 = 1;
	TRISDbits.TRISD14 = 1;


	// Turn them all off to begin
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;
}


void SetupIO(void)
{
	TRISDbits.TRISD15 = 0;
	TRISFbits.TRISF3 = 0;
	TRISFbits.TRISF2 = 0;

}


double CalculateVoltage(int an1)
{
	double temp;
	double ret;
	// There are 1023 counts in the ADC module
	// While there is a range of 0-3.3 Volts in the potentiometer
	// This corresponds to 3.3/1023 = 3.23mV per count
	// Thus multiply the counts by 3.23
	// And divide by 1000.
	
	temp = an1 * 3.3;
	ret = temp / 1000;

	return ret;
}


void IncPWMDutyCycle(int num, double perc, int dir)
{
	short int duty;

	switch(num)
	{
		case 0:
		case 1:
			break;
		case 3:
			if(dir == UP)
			{
				if(PWM0 >= MAX_PWMT3 && PWM0 <= 0xFFFF0000)
				{
					PWM0 = MAX_PWMT3;
					return;
				}
				PWM0 += (short int)(MAX_PWMT3 * perc);
			}
			else
			{
				if(PWM0 >= 0xFFFF0000 || PWM0 <= 0x0FFF)
				{
					PWM0 = 0;
					return;
				}
				PWM0 -= (short int)(MAX_PWMT3 * perc);
			}
			break;
		case 4:
		default:
			break;
	}
}



void SetPWMDutyCycle(int num,double perc)
{
	short int duty;

	switch(num)
	{
		case 0:
		case 1:
			break;
		case 3:
			PWM0 = (short int)(MAX_PWMT3 * perc);
			break;
		case 4:
		default:
			break;
	}
}






