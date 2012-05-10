#include "car_control.h"

extern void init_car(){
	DDRC = 0xFF;
	PORTC = 0x00;
}


extern void go_fwd(){
	/* Set forward command */
	PORTC |= (1<<PC4);
	/* Unset backward command */
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
	PORTC |= (1<<PC6);
	PORTC &= ~(1<<PC7);
}

extern void turn_right(){
	PORTC |= (1<<PC7);
	PORTC &= ~(1<<PC6);
}


extern void go_fwd_for(int milisecs){

}

extern void go_bkd_for(int milisecs){

}

extern void brake_for(int milisecs){

}

extern void turn_left_for(int milisecs){

}

extern void turn_right_for(int milisecs){

}
