#ifndef GIBBOT_CURRENT_H_
#define GIBBOT_CURRENT_H_
/*
 *  gibbot_current.h
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

ISR(T4,0);

void timer3Init();

void timer4Init();

uint16 current_amps_get();

void shutdown_movement();

void start_up_movement();

void current_gains_sprintf(char * buffer);

void current_gains_sscanf(const char * buffer);

#endif