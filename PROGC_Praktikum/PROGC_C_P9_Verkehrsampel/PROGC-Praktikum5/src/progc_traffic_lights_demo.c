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

#include "progc_crossroad.h"



int main (void)
{
	printf("Start traffic lights system\n");
	
    // Initializ
    if (progc_init() != 0) {
        printf("Terminating program due to error during wiringpi/i2c - initialization.");
        return 1;
    }
	
	
	while (1) {
		progc_set_traffic_light_state(LIGHT_S3, RED);
		progc_set_traffic_light_state(LIGHT_S1, RED);
		progc_set_traffic_light_state(LIGHT_S2, RED);
		progc_set_7Seg_Display(0);
		
		while (interrupt_states == 0) {
			delay(100);
		}
		
		interrupt_states = 0;
		
		// if pressed button = ... , then:
		progc_set_7Seg_Display(1);
		
		delay(1000);
		progc_set_traffic_light_state(LIGHT_S1, ORANGE);
		delay(1000);
		progc_set_traffic_light_state(LIGHT_S1, GREEN);
		delay(2000);
		progc_set_traffic_light_state(LIGHT_S1, ORANGE);
		delay(1000);
		progc_set_traffic_light_state(LIGHT_S1, RED);
	}

	
	
    printf("Start loop..\n");
    unsigned char i = 0;
    while(1)
    {
        
        if (++i > 16)
        i = 0;

        printf("Interrupt states: %d\n", interrupt_states);
		interrupt_states = 0;
        delay(1000);
    }
    return 0;

}
