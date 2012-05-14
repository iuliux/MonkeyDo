#include "car_control.h"

extern void init_car(){
	DDRC = 0xFF;
	PORTC = 0x00;
}


extern void go_fwd(){
	/* Set forward command */
	PORTC |= (1<<PC4);
	/* Unset backward command, just in case */
	PORTC &= ~(1<<PC5);
}

extern void go_bkd(){
	PORTC |= (1<<PC5);
	PORTC &= ~(1<<PC4);
}

extern void brake(){
	/* Set both forward and backward */
	PORTC |= (1<<PC4);
	PORTC |= (1<<PC5);
}

extern void turn_left(){
	/* Set left command */
	PORTC |= (1<<PC7);
	/* Unset right command */
	PORTC &= ~(1<<PC6);
}

extern void turn_right(){
	PORTC |= (1<<PC6);
	PORTC &= ~(1<<PC7);
}

extern void no_movement(){
	PORTC = 0x00;
}
