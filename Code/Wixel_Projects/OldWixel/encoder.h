#ifndef ENCODER_H__
#define ENCODER_H__ 
/*
 *  encoder.h
 *  
 *
 *  Created by Matt Collins on 4/8/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <uart0.h>
#include <stdio.h>

uint16 motor_encoder_read(void);

uint16 wall_encoder_read(void);

void motor_encoder_reset(void);

void wall_encoder_reset(void);

#endif