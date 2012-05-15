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

	sseg_start_anim(); /* Start */
	_delay_ms(1000);

	for (;;) { /* For each instruction/command */
		BOOL left = 0, right = 0;

		unsigned char movement = parse_movement();
		if(movement == PARSE_ERR)
			return 1;

		unsigned int duration = parse_duration();
		if(duration == 0) /* Yes, 0 duration is illegal */
			return 1;

		if((movement & (UCHAR)DIR_MASK) == (UCHAR)DIR_LFT){
			left = TRUE;
			turn_left();
		}else if((movement & (UCHAR)DIR_MASK) == (UCHAR)DIR_RGT){
			right = TRUE;
			turn_right();
		}

		if((movement & (UCHAR)ACC_MASK) == (UCHAR)ACC_FWD){
			if(left){
				sseg_display(FWD_LEFT_CHAR);
			}else if(right){
				sseg_display(FWD_RIGHT_CHAR);
			}else
				sseg_display('^');
				
			go_fwd();
		} else if((movement & (UCHAR)ACC_MASK) == (UCHAR)ACC_BKD){
			if(left){
				sseg_display(BKD_LEFT_CHAR);
			}else if(right){
				sseg_display(BKD_RIGHT_CHAR);
			}else
				sseg_display('v');

			go_bkd();
		} else if((movement & (UCHAR)ACC_MASK) == (UCHAR)ACC_BRK){
			sseg_display('-');
			brake();
		}

		while(duration > 6000){
			/* Max time for _delay_ms is 6.5 secs */
			duration -= 6000;
			_delay_ms(6000.);
		}
		_delay_ms((double)duration);
		sseg_display(' ');
		no_movement();
	}
}


/*
 * -----------------------------------------------------------------------
 * Main
 * -----------------------------------------------------------------------
 */
int main (void)
{
	/* Init SD/MMC */
	DDRD |= (1<<PD7);
	DDRB &= ~(1<<PB1);
	PORTB |= (1<<PB1);

	init_car();
	init_sseg();

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
			if (!(Fno.fattrib & (AM_DIR|AM_HID)) && strstr(Fno.fname, ".MKD")) {
				if (play(Fno.fname)){
					sseg_error('P');
					// break;
				}
			}
		}
	}

	sseg_display(' ');
	no_movement();
	return 0;
}
