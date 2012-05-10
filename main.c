/*---------------------------------------------------------------*/
/* 8-pin SD audio player R0.04                     (C)ChaN, 2010 */
/*---------------------------------------------------------------*/

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <string.h>
#include "diskio.h"
#include "pff.h"
#include "car_control.h"
#include "seven_segment.h"
#include "parser.h"

#define FCC(c1,c2,c3,c4)	(((DWORD)c4<<24)+((DWORD)c3<<16)+((WORD)c2<<8)+(BYTE)c1)	/* FourCC */


/*---------------------------------------------------------*/
/* Work Area                                               */
/*---------------------------------------------------------*/

volatile BYTE FifoRi, FifoWi, FifoCt;	/* FIFO controls */

unsigned char Buff1[256];		/* Wave output FIFO */
unsigned char Buff2[256];		/* Wave output FIFO */

FATFS Fs;			/* File system object */
DIR Dir;			/* Directory object */
FILINFO Fno;		/* File information */

WORD rb;			/* Return value. Put this here to avoid bugs of avr-gcc */


/*---------------------------------------------------------*/

static UINT play (const char *fn){
	int i = 0;

	if (pf_open(fn)){
		/* Display an error code */
		sseg_display('E');
		_delay_ms(500);
		sseg_display('F');
		return 1;
	}

	sseg_display('S'); /* Start */
	_delay_ms(200);

	for (;;) {
		// pf_read(Buff1, 1, &rb);			/* Get Chunk ID and size */
		// if (rb != 1){
		// 	sseg_display('E');
		// 	_delay_ms(500);
		// 	sseg_display('r');
		// 	return 1;
		// }

		unsigned char movement = parse_movement();
		sseg_display(movement);

		// for(i = 0; i < 8; i++){
		// 	if((movement >> i) & 0x01 == 0)
		// 		sseg_display('0');
		// 	else
		// 		sseg_display('1');
		// 	_delay_ms(600);
		// 	sseg_display(' ');
		// 	_delay_ms(100);
		// }
		// sseg_display(' ');
		// _delay_ms(1000);

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

		// sseg_display(Buff1[0]);

		_delay_ms(800);
		sseg_display(' ');
		_delay_ms(50);
	}
}




/*-----------------------------------------------------------------------*/
/* Main                                                                  */


int main (void)
{
	DDRD |= (1<<PD7);
	DDRB &= ~(1<<PB1);
	PORTB |= (1<<PB1);

	init_car();
	init_sseg();

	// int i = 0;
	// while(1){
	// 	switch(i){
	// 		case 0:
	// 			turn_left();
	// 			sseg_display('L');
	// 			break;
	// 		case 1:
	// 			PORTC = 0x00;
	// 			sseg_display('0');
	// 			break;
	// 		case 2:
	// 			turn_right();
	// 			sseg_display('F');
	// 			break;
	// 		case 3:
	// 			brake();
	// 			sseg_display('1');
	// 			break;
	// 		case 4:
	// 			sseg_display('E');
	// 			break;
	// 		case 5:
	// 			sseg_display('b');
	// 			break;
	// 		case 6:
	// 			sseg_display('r');
	// 			break;
	// 	}
	// 	if(i++ == 7)
	// 		i = 0;

	// 	_delay_ms(500);
	// }
	
	for (;;) {
		_delay_ms(1000);
		if (pf_mount(&Fs)){
			/* Display an error code */
			sseg_display('E');
			_delay_ms(500);
			sseg_display('0');
			// sseg_wait_anim();
			continue; /* Retry */
		} else {
			sseg_display(' '); /* Clear */
		}

		for (;;) {
			if (pf_opendir(&Dir, "")){	/* Open root dir */
				sseg_display('E');
				_delay_ms(500);
				sseg_display('1');
				break;
			}
			while (!pf_readdir(&Dir, &Fno) && Fno.fname[0]) {
				// if (!(Fno.fattrib & (AM_DIR|AM_HID)) && strcmp(Fno.fname, "main.doit") == 0) {
					if (play(Fno.fname)){
						sseg_display('E');
						_delay_ms(500);
						sseg_display('P');
						break;
					}
				// }
			}
		}
	}
	PORTD = 0x00;
}



