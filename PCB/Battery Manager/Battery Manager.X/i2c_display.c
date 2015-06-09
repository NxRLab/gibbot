/* 
 * File:   i2c_display.c
 * Author: ryanyu
 *
 * Created on April 13, 2015, 3:04 PM
 */

#include "i2c_master_int.h"
#include "i2c_display.h"
#include <stdlib.h>
// control the SSD1306 OLED display
// Not meant as a full driver, just demonstrates the basics
// note that resetting the PIC does not perform a reset on the OLED display, only power cycling does

#define DISPLAY_ADDR 0x3C

#define SIZE WIDTH*HEIGHT/8 //display size, in bytes

static unsigned char video_buffer[SIZE+1] = {0};          // buffer for sending over i2c. The first byte allows us to store the control character
static unsigned char * gddram = video_buffer + 1;   // actual video ram. write pixels to gddram


void display_command(unsigned char cmd) { // write a command to the display
  unsigned char to_write[] = {0x00,cmd};  // first byte is 0 (CO = 0, DC = 0), second byte is the command
  i2c_write_read(DISPLAY_ADDR, to_write,2, NULL, 0);
}

void display_init() {
  i2c_master_setup();
                          // goes through the reset procedure
  display_command(0xAE);  // turn off display

  display_command(0xA8);     // set the multiplex ratio (how many rows are updated per oled driver clock) to the number of rows in the display
  display_command(HEIGHT-1); // the multiplex ratio set is the value sent + 1, so subtract 1

                         // we will always write the full display on a single update.
  display_command(0x20); // set address mode
  display_command(0x00); // horizontal address mode
  display_command(0x21); // set column address
  display_command(0x00); // start at 0
  display_command(0xFF); // end at 127
                         // with this address mode, the address will go through all the pixels and then return to the start,
                         // hence we never need to set the address again

  display_command(0x8d); // charge pump
  display_command(0x14); // turn charge pump on (creates the ~7 Volts needed to light pixels)
  display_command(0xAF); // turn on the display
  video_buffer[0] = 0x40; // co = 0, dc =1, allows us to send data directly from video buffer,
                          //0x40 is the "next bytes have data" byte
}

void display_draw() {        // copies data to the gddram on the oled chip
  i2c_write_read(DISPLAY_ADDR, video_buffer, SIZE + 1, NULL, 0);
}

void display_clear() {
  memset(gddram,0,SIZE);
}

static inline int pixel_pos(int row, int col) { // get the position in gddram of the pixel position
  return (row/8)*WIDTH + col;
}

static inline unsigned char pixel_mask(int row) { // get a bitmask for the actual pixel position, based on row
  return 1 << (row % 8);
}

void display_pixel_set(int row, int col,int val) { // invert the pixel at the given row and column
  if(val) {
    gddram[pixel_pos(row,col)] |= pixel_mask(row);   // set the pixel
  } else {
    gddram[pixel_pos(row,col)] &= ~pixel_mask(row);  // clear the pixel
  }
}

int display_pixel_get(int row, int col) {
  return (gddram[pixel_pos(row,col)] & pixel_mask(row)) != 0;
}

