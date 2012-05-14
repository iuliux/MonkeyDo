/*
 * MonkeyDo
 * 
 * part of MonkeySee-MonkeyDo project
 * Author: Iulius Curt
 */

#define F_CPU 16000000 /* Designed for ATmega16 */
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "diskio.h"
#include "pff.h"
#include "car_control.h"
#include "seven_segment.h"
#include "parser.h"

FATFS Fs;			/* File system object */
DIR Dir;			/* Directory object */
FILINFO Fno;		/* File information */

WORD rb;			/* Return value. Put this here to avoid bugs of avr-gcc */


/*
 * Plays the file with name `fn`. Will parse commands
 * sequentially and perform action using delays
 */
static UINT play (const char *fn){
	if (pf_open(fn)){
		/* Display an error code */
		sseg_error('F');
		return 1;
	}

	sseg_display('S'); /* Start */
	_delay_ms(1000);

	for (;;) {
		unsigned char movement = parse_movement();
		if(movement == PARSE_ERR)
			return 1;

		unsigned int duration = parse_duration();
		if(duration == 0)
			return 1;

		if((movement & (UCHAR)DIR_MASK) == (UCHAR)DIR_LFT){
			sseg_display('<');
			_delay_ms(600);
		}else if((movement & (UCHAR)DIR_MASK) == (UCHAR)DIR_RGT){
			sseg_display('>');
			_delay_ms(600);
		}

		if((movement & (UCHAR)ACC_MASK) == (UCHAR)ACC_FWD)
			sseg_display('^');
		else if((movement & (UCHAR)ACC_MASK) == (UCHAR)ACC_BKD)
			sseg_display('v');
		else if((movement & (UCHAR)ACC_MASK) == (UCHAR)ACC_BRK)
			sseg_display('-');

		// while(duration > 0){
		// 	sseg_display('0' + duration%10);
		// 	duration = duration / 10;
		// 	_delay_ms(600);
		// 	sseg_display(' ');
		// 	_delay_ms(100);
		// }
		// sseg_display(' ');
		// _delay_ms(1000);

		while(duration > 6000){
			/* Max time for _delay_ms is 6.5 secs */
			duration -= 6000;
			_delay_ms(6000.);
		}
		_delay_ms((double)duration);
		sseg_display(' ');
	}
}


/*
 * -----------------------------------------------------------------------
 * Main
 * -----------------------------------------------------------------------
 */
int main (void)
{
	DDRD |= (1<<PD7);
	DDRB &= ~(1<<PB1);
	PORTB |= (1<<PB1);

	init_car();
	init_sseg();
go_fwd();
	for (;;) {
		_delay_ms(1000);
		if (pf_mount(&Fs)){
			/* Display waiting animation */
			sseg_wait_anim();
			continue; /* Retry */
		} else {
			sseg_display(' '); /* Clear */
		}

		if (pf_opendir(&Dir, "")){	/* Open root dir */
			sseg_error('d');
			break;
		}
		while (!pf_readdir(&Dir, &Fno) && Fno.fname[0]) {
			if (!(Fno.fattrib & (AM_DIR|AM_HID)) && strcmp(Fno.fname, "MAIN.MKD") == 0) {
				// print_str(Fno.fname);
				// sseg_wait_anim();
				// _delay_ms(1000);
				if (play(Fno.fname)){
					sseg_error('P');
					break;
				}
			}
		}
	}
	PORTA = 0x00;
	return 0;
}
