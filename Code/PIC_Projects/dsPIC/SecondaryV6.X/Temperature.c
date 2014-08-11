#include <math.h>
#include "Temperature.h"


/*float thermistor_resistance(void){
    float voltage, resistance;
    voltage = read_ADC()*3.3/4096;
    resistance = 33000/voltage - 10000;
    return resistance;   
}

float motor_temp(float resistance){
    float temp;
    temp = 1/(3.354016e-03 + 2.933908e-04*log(resistance/10000) + 2*3.494314e-06*log(resistance/10000) - 3*7.712690e-07*log(resistance/10000));
    temp = temp - 273.15;
    return temp;
}
*/