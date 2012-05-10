#ifndef __CAR_CONTROL
#define __CAR_CONTROL

#include <avr/io.h>

void init_car(void);

void go_fwd(void);
void go_bkd(void);
void brake(void);
void turn_left(void);
void turn_right(void);

void go_fwd_for(int milisecs);
void go_bkd_for(int milisecs);
void brake_for(int milisecs);
void turn_left_for(int milisecs);
void turn_right_for(int milisecs);

#endif
