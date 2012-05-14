#ifndef __CAR_CONTROL
#define __CAR_CONTROL

#include <avr/io.h>

void init_car(void);

void go_fwd(void);
void go_bkd(void);
void brake(void);

void turn_left(void);
void turn_right(void);

void no_movement(void);

#endif
