#ifndef __SEVEN_SEGMENT
#define __SEVEN_SEGMENT

#include <avr/io.h>
#include <util/delay.h>

/*
	Seven segment one character display
	 ____
	|    |
	|____|
	|    |
	|____|

*/

void init_sseg(void);

/* Tries it's best to display the character `c`. If it is not a 
 * predefined character, it will display the default:
 * :
 * :	 ___
 * :	|   |
 * :	|___|
 */
void sseg_display(char c);

/* Plays one complete animation sequence. Does not loop. */
void sseg_wait_anim(void);

#endif
