#include "progc_crossroad.h"




/*
 Functions to use from progc_crossroad.h
 
 - unsigned char progc_init();
 - unsigned char progc_read(unsigned char port);
 - unsigned char progc_write(unsigned char port, unsigned char value);
 - unsigned char progc_set_7Seg_Display(unsigned char value);
 - unsigned char progc_set_traffic_light_state(unsigned char light_identifier, unsigned char new_light_position);

*/
int main (void)
{
	printf("Start traffic lights system\n");
	
    if (progc_init() != 0) {
        printf("Terminating program due to error during wiringpi/i2c - initialization.\n");
        return 1;
    }
		
	while (1) {
	
	}
    return 0;
}
