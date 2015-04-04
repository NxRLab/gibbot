/// @file
#include <boards/pv7.h>
#include <gibbot.h>

/// A simple example showing basic input/output functionality
int main()
{
    initialize_board(&pv7);

    // disable DMA3
    DMA3CONbits.CHEN = false;

    // set up loopback interface
    U2MODEbits.LPBACK = 1;

    char buf[4];
    buf[0] = 'a';
    buf[1] = 'b';
    buf[2] = 'c';
    buf[3] = '\0';

    //printf("writing the pic2pic peripheral in loop-back mode to test features.\n");
    write_pic2pic(buf, sizeof(buf));
    memset(buf, 0, sizeof(buf));
    read_pic2pic(buf, sizeof(buf));

    //printf("in the buffer: %s\n", buf);

    //printf("now enable dma on pic2pic RX\n");
    //printf("other board's data reads: mag enc: %ld mot enc: %ld\n",
    //    other_boards_data.magnet_enc, other_boards_data.motor_enc);

    // pretend we're a secondary board.
    init_motor_enc(1800);
    enable_dma4_on_rx();
    U2MODEbits.LPBACK = 1;

    OtherPICsData fake_data;

    //printf("before: other board's data reads: mag enc: %ld mot enc: %ld\n",
    //    other_boards_data.magnet_enc, other_boards_data.motor_enc);

    int i;
    for(i = 1; i < 5; i++) {
        fake_data.magnet_enc = 123 * i;
        fake_data.motor_enc = -987 + i;


        write_pic2pic(&fake_data, sizeof(fake_data));

        //printf("now: other board's data reads: mag enc: %ld mot enc: %ld\n",
        //    other_boards_data.magnet_enc, other_boards_data.motor_enc);
        
        //printf("\n");
    }


    my_magnet_enc.write(12345);
    my_motor_enc.write(12345);
    MAG = 1;
    //printf("my board's data reads: mag enc: %ld mot enc: %ld\n",
    //    my_magnet_enc.read(), my_motor_enc.read());

    enable_dma5_on_tx();

    __delay_ms(100);

    //printf("after dma5: other board's data is mag enc: %ld mot enc: %ld\n",
    //        other_boards_data.magnet_enc, other_boards_data.motor_enc);
     
    attn("Done!\n");
    while(1);

    return 0;
}
