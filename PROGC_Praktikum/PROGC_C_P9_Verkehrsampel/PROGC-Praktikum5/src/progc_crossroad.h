/*******************************************************************************
*  _____       ______   ____
* |_   _|     |  ____|/ ____|  Institute of Embedded Systems
*   | |  _ __ | |__  | (___    Wireless Group
*   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur
*  _| |_| | | | |____ ____) |  (University of Applied Sciences)
* |_____|_| |_|______|_____/   8401 Winterthur, Switzerland
*
*******************************************************************************
*
* Copyright (c) 2013, Institute Of Embedded Systems at Zurich University
* of Applied Sciences. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
* 3. Neither the name of the Institute nor the names of its contributors
*    may be used to endorse or promote products derived from this software
*    without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*/
/*---------------------------------------------------------------------------*/
/**
* \file
*                           Functions for Raspberry Pi Extension Board by ZHAW
* \author
*                           Mathias Gugg
* \version
*                           0.1
* \since
*                           10.04.2013
*/
/*---------------------------------------------------------------------------*/

#ifndef PROGC_CROSSROAD_H
#define PROGC_CROSSROAD_H

// Ports
#define PORT_0 	0
#define PORT_1	1
#define PORT_2	2
#define PORT_3	3
#define PORT_4	4

// Light position 
#define RED 		0
#define ORANGE 		1
#define GREEN 		2
#define ORANGE_2nd 	3

// Traffic lights (Ports 0-2)
#define LIGHT_S1	0
#define LIGHT_S2	1
#define LIGHT_S3	2
#define LIGHT_P1	3
#define LIGHT_P2	4
#define LIGHT_P3	5

// Traffic light mask withhin byte (Ports 0-2)
#define LIGHT_S1_MASK 0b00001111
#define LIGHT_S2_MASK 0b11110000
#define LIGHT_S3_MASK 0b00001111
#define LIGHT_P1_MASK 0b01110000
#define LIGHT_P2_MASK 0b00000111
#define LIGHT_P3_MASK 0b00111000

// Traffic light start in byte (Ports 0-2)
#define AMPEL_S1_1ST_BIT 0
#define AMPEL_S2_1ST_BIT 4
#define AMPEL_S3_1ST_BIT 0
#define AMPEL_P1_1ST_BIT 4
#define AMPEL_P2_1ST_BIT 0
#define AMPEL_P3_1ST_BIT 3

// Button bit position (Port 3)
#define BUTTON_P1 0
#define BUTTON_P2 1
#define BUTTON_P3 2
#define BUTTON_C1 3
#define BUTTON_C2 4
#define BUTTON_C3 5



// If a button has been pressed, it will be written into interrupt_states. Bit must be set back to 0 manually.
unsigned char interrupt_states;

unsigned char progc_init();
unsigned char progc_read(unsigned char port);
unsigned char progc_write(unsigned char port, unsigned char value);
unsigned char progc_set_7Seg_Display(unsigned char value);
unsigned char progc_set_traffic_light_state(unsigned char light_identifier, unsigned char new_light_position);

//include these files
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include "wiringPiI2C.h"
#include <wiringPi.h>

#endif /* PROGC_CROSSROAD_H */
