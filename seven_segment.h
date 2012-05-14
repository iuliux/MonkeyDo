#ifndef __SEVEN_SEGMENT
#define __SEVEN_SEGMENT

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

/*
	Seven-segments one character display
	 ____
	|    |
	|____|
	|    |
	|____| o

*/

void init_sseg(void);

/* Tries it's best to display the character `c`. If it is not a 
 * predefined character, it will display the default:
 * :	 ___
 * :	.   .
 * :	.___.
 * :	.   .
 * :	.___. .
 */
void sseg_display(char c);

/* Plays one complete animation sequence. Does not loop. */
void sseg_wait_anim(void);

/* Displays an error message */
void sseg_error(char c);

/* Prints a string char by char
 * (Well, tries it's best, I mean) */
void print_str(char *str);

#endif
