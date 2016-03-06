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




// Use pin 23 (GPIO4) as interrupt pin
#define INTERRUPT_PIN					4		
// AD0=AD1=AD2=Vss=Gnd 0x40, here 0x20
#define I2C_DEVICE						0x20	

// Base registers
#define INPUT_PORT_REGISTER_BASE 		0x00
#define OUTPUT_PORT_REGISTER_BASE 		0x08
#define IO_CONFIGURATION_REGISTER_BASE 	0x18
#define MASK_INTERRUPT_REGISTER_BASE	0x20

// Offset registers for ports
#define P0_OFFSET						0x00
#define P1_OFFSET						0x01
#define P2_OFFSET						0x02
#define P3_OFFSET						0x03
#define P4_OFFSET						0x04

// lookup table for 7segment (0 to F)
const unsigned char lookup_table_7seg [16] ={
                       0b00000011,
					   0b10011111,
					   0b00100101,
					   0b00001101,
					   0b10011001,
					   0b01001001,
					   0b01000001,
					   0b00011111,
					   0b00000001,
					   0b00001001,
					   0b00010001,
					   0b11000001,
					   0b01100011,
					   0b10000101,
					   0b01100001,
					   0b01110001};

// file descriptor
int fd;


/*---------------------------------------------------------------------------*/
/**
* \brief       Function called when interrupt occured
* \param       void There are no parameters needed.
* \return      No return values.
*/
void interrupt_callback_function(void)
{
    unsigned char interrupt_register = wiringPiI2CReadReg8(fd, INPUT_PORT_REGISTER_BASE + P3_OFFSET);
    interrupt_states |= interrupt_register;	
}

/*---------------------------------------------------------------------------*/
/**
* \brief       Initializing I2C and NXP PCA9698 Chip 
* \param       void There are no parameters needed.
* \return      Function returns 0 after success, 1 if it failed.
*/
unsigned char progc_init()
{	
    interrupt_states = 0x00;

    if (wiringPiSetup () < 0)
    {
        fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno)) ;
        return 1 ;
    }
    // Set [!OE] low
    pinMode(1, OUTPUT);
    digitalWrite(1, LOW);
    // Set  [!RESET] high
    pinMode(5, OUTPUT);
	// Reset Chip (making sure that the default values are set)
	digitalWrite(5, LOW);
    digitalWrite(5, HIGH);


    if ((fd = wiringPiI2CSetup(I2C_DEVICE)) < 0)
    {
        printf("I2C Setup error. fd = %d\n", fd);
        return 1;
    }

    // set I/O configuration of pins (0=ouput, 1=input)
    wiringPiI2CWriteReg8(fd, IO_CONFIGURATION_REGISTER_BASE + P0_OFFSET, 0x00); // set bank 0 as output (LEDs)
    wiringPiI2CWriteReg8(fd, IO_CONFIGURATION_REGISTER_BASE + P1_OFFSET, 0x00); // set bank 1 as output (0-6: LEDs)
    wiringPiI2CWriteReg8(fd, IO_CONFIGURATION_REGISTER_BASE + P2_OFFSET, 0x00); // set bank 2 as output (0-5: LEDs)
    wiringPiI2CWriteReg8(fd, IO_CONFIGURATION_REGISTER_BASE + P3_OFFSET, 0xFF); // set bank 3 as input  (0-5: Buttons, 6-7: Switches)
    wiringPiI2CWriteReg8(fd, IO_CONFIGURATION_REGISTER_BASE + P4_OFFSET, 0x00); // set bank 4 as output (7-Segment display)
	
	// set all output pins to 1 (LEDs off)
    wiringPiI2CWriteReg8(fd, OUTPUT_PORT_REGISTER_BASE + P0_OFFSET, 0xFF); // set bank 0 (LEDs)
    wiringPiI2CWriteReg8(fd, OUTPUT_PORT_REGISTER_BASE + P1_OFFSET, 0xFF); // set bank 1 (0-6: LEDs)
    wiringPiI2CWriteReg8(fd, OUTPUT_PORT_REGISTER_BASE + P2_OFFSET, 0xFF); // set bank 2  (0-5: LEDs)
    wiringPiI2CWriteReg8(fd, OUTPUT_PORT_REGISTER_BASE + P4_OFFSET, 0xFF); // set bank 4  (7-Segment display)

	// set Interrupt pin as input
	pinMode(INTERRUPT_PIN, INPUT);

	// Activate interrupt
	if (wiringPiISR (INTERRUPT_PIN, INT_EDGE_FALLING, &interrupt_callback_function) < 0)
    {
        fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
        return 1 ;
    }
	
	//Enable Interrupts for Port 3 (Pins 0-6)	
    wiringPiI2CWriteReg8(fd, MASK_INTERRUPT_REGISTER_BASE + P3_OFFSET, 0b11000000); // pins 0-6
	//wiringPiI2CWriteReg8(fd, MASK_INTERRUPT_REGISTER_BASE + P3_OFFSET, 0xF7); // only pin 3
	
	return 0;
}

/*---------------------------------------------------------------------------*/
/**
* \brief       Reading byte from port register
* \param       unsigned char Port number
* \return      Value in port register
*/
unsigned char progc_read(unsigned char port_nr)
{
    unsigned char port_address;
	switch (port_nr) {
	    case 0:
		case 1:
		case 2:
		case 4:
		    port_address = OUTPUT_PORT_REGISTER_BASE + port_nr;
		    break;
		case 3:
		    port_address = INPUT_PORT_REGISTER_BASE + port_nr;
		    break;
		default:
		    return -1;
	}
		
    return wiringPiI2CReadReg8(fd, port_address);
}

/*---------------------------------------------------------------------------*/
/**
* \brief       Writing byte to port register
* \param       unsigned char Port number, unsignec char value
* \return      No return values.
*/
unsigned char progc_write(unsigned char port_nr, unsigned char value)
{
    wiringPiI2CWriteReg8(fd, OUTPUT_PORT_REGISTER_BASE + port_nr, value);
	return 0;
}

/*---------------------------------------------------------------------------*/
/**
* \brief       Set number that is displayed in 7-Segment-Display
* \param       unsigned char hex number to be displayed
* \return      No return values.
*/
unsigned char progc_set_7Seg_Display(unsigned char value)
{
    if (value >=0 && value < 16) {
        wiringPiI2CWriteReg8(fd, OUTPUT_PORT_REGISTER_BASE + P4_OFFSET, lookup_table_7seg[value]);
	}
	else {
	    wiringPiI2CWriteReg8(fd, OUTPUT_PORT_REGISTER_BASE + P4_OFFSET, 0xff);
	}
	
	return 0;
}

/*---------------------------------------------------------------------------*/
/**
* \brief       Function called when interrupt occured
* \param       void There are no parameters needed.
* \return      returns 0 if ok, 1 if input is invalid.
*/
unsigned char progc_set_traffic_light_state(unsigned char light_identifier, unsigned char new_light_position)
{
    unsigned char new_value, port, mask, bit_position;
	
    switch (light_identifier) {
	    case LIGHT_S1:
			port 		 = PORT_0;
			mask		 = LIGHT_S1_MASK;
			bit_position = AMPEL_S1_1ST_BIT;
		    break;
		case LIGHT_S2:
			port 		 = PORT_0;
			mask		 = LIGHT_S2_MASK;
			bit_position = AMPEL_S2_1ST_BIT;
		    break;
		case LIGHT_S3:
			port 		 = PORT_1;
			mask		 = LIGHT_S3_MASK;
			bit_position = AMPEL_S3_1ST_BIT;
		    break;
		case LIGHT_P1:
			port 		 = PORT_1;
			mask		 = LIGHT_P1_MASK;
			bit_position = AMPEL_P1_1ST_BIT;
		    break;
		case LIGHT_P2:
			port 		 = PORT_2;
			mask		 = LIGHT_P2_MASK;
			bit_position = AMPEL_P2_1ST_BIT;
		    break;
		case LIGHT_P3:
			port 		 = PORT_2;
			mask		 = LIGHT_P3_MASK;
			bit_position = AMPEL_P3_1ST_BIT;
		    break;
		default:
			return 1;
		    break;
			
	}		
		new_value = progc_read(port);
		new_value |= mask;
		new_value &= ~(1 << (new_light_position + bit_position));
		progc_write(port, new_value);
		
		return 0;
}
