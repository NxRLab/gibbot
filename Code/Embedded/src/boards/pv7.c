/// Board definitions for the v7 primary PCB
/** @file
*/

#include <boards/pv7.h>

const Board pv7 = {
        .name = BOARD_NAME,
        .init_pins = pv7_init_pins, 
        .init_periphs = pv7_init_periphs,
        .flash_lights = pv7_flash_lights,
    }; // all other values default to zero

// inherits all functions from v6 code
