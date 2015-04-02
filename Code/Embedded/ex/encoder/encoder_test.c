/// An example program showing how to use the encoder struct
/** @file
*/

#include <boards/breakout.h>
#include <gibbot.h>

int main()
{
    int n;
    long int value;
    char buf[128];

    initialize_board(&breakout);

    warn("DON'T TURN PART YET!!!\n");
    printf("magnet encoder qei: %d\n", QEI1ICL);
    printf("magnet encoder qei: %d\n", QEI1ICH);

    printf("magnet encoder value: %ld\n", my_magnet_enc.value);
    printf("magnet encoder low16: %ld\n", my_magnet_enc.low16);
    printf("magnet encoder high16: %ld\n", my_magnet_enc.low16);
    printf("magnet encoder offset: %ld\n", my_magnet_enc.offset);
    printf("magnet encoder cpr: %ld\n", my_magnet_enc.cpr);
    printf("magnet encoder read: %ld\n", my_magnet_enc.read());
    
    n = 0;
    while(n < 1) {
        printf("enter an integer: ");
        n = sscanf(getsn(buf, sizeof(buf)), "%ld\n", &value); 
    }

    printf("\n\n ************** \n\n");

    printf("magnet encoder write! %ld\n", value);

    my_magnet_enc.write(value);
    printf("magnet encoder low16: %ld\n", my_magnet_enc.low16);
    printf("magnet encoder high16: %ld\n", my_magnet_enc.low16);
    printf("magnet encoder offset: %ld\n", my_magnet_enc.offset);
    printf("magnet encoder cpr: %ld\n", my_magnet_enc.cpr);
    printf("magnet encoder read: %ld\n", my_magnet_enc.read());
    printf("magnet encoder degrees: %Lg\n", DEGREES(my_magnet_enc));


    info("NOW TURN PART!!!\n");
    __delay_ms(1500);
    n = 0;
    while(n < 1000) {
        printf("magnet encoder read: %ld\n", my_magnet_enc.read());
        n++;
        __delay_ms(200);
    }

    attn("Done!\n");
    while(1);

    return 0;
}
