#include <boards/sv7.h>

const Board sv7 = {
        .name = BOARD_NAME,
        .init_pins = sv7_init_pins, 
        .init_periphs = sv7_init_periphs,
        .flash_lights = sv7_flash_lights,
    }; // all other values default to zero


// inherits all functions from v6 code
