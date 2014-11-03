/*A thermistor is used to monitor the motor temperature.  A thermistor voltage
 divider network is used to provide a voltage of 0V to 3.3V into an analog pin
 of the dsPIC, where the input voltage depends upon the resistance of the thermistor.
 This resistance is dependent upon the temperature.  The ADC module of the dsPIC
 reads in this voltage and converts it to an ADC count.  Using the voltage divider
 equation, the resistance of the thermistor can be found from the ADC count.  Then,
 using this resistance and an equation provided in the Vishay datasheet for the
 thermistor, the temperature can be calculated.*/

#include <math.h>
#include "Temperature.h"
#include "ADC.h"


float thermistor_resistance(void){
    /*This function returns the resistance of the thermistor.  This is done by
     * using the voltage divider equation Vout = Vin*R2/(R1+R2), where Vin is 3.3V,
     * R2 is 10k and R1 is the thermistor resistance.*/
    float voltage, resistance;
    voltage = read_ADC()*3.3/4096;
    resistance = 33000/voltage - 10000;
    return resistance;
}

float motor_temp(float resistance){
    /*This function takes the resistance of the thermistor as an input, and
     * using the function provided in the Vishay thermistor datasheet, calculates
     * the temperature in Kelvin.  This was then converted into fahrenheit.*/
    float temp;
    temp = 1/(3.354016e-03 + 2.933908e-04*log(resistance/10000) + 2*3.494314e-06*log(resistance/10000) - 3*7.712690e-07*log(resistance/10000));
    temp = temp * 9 / 5 - 459.67;
    return temp;
}
