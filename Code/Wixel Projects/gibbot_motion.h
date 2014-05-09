#ifndef GIBBOT_MOTION_H_
#define GIBBOT_MOTION_H_
/*
 *  gibbot_motion.h
 *  
 *
 *  Created by Matt Collins on 5/5/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <uart0.h>
#include <stdio.h>
#include <radio_com.h>
#include <radio_link.h>
#include "encoder.h"

ISR(T1,0);

void motion_init();

uint16 motor_angle();

uint16 wall_angle();

void motion_gains_sprintf(char * buffer);

void motion_gains_sscanf(const char * buffer);

#endif