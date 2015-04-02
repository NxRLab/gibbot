#ifndef SV7_BOARD_H
#define SV7_BOARD_H
/// @file

// inherit values from V6 board
#include <boards/sv6.h>

// except for board name
#ifdef BOARD_NAME
#undef BOARD_NAME
#endif

#define BOARD_NAME "Secondary V7 Board" /// Board name for Secondary v7 board

#define sv7_init_pins sv6_init_pins
#define sv7_init_periphs sv6_init_periphs
#define sv7_flash_lights sv6_flash_lights

extern const Board sv7;

#endif /* SV7_BOARD_H */
