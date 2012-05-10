#include "parser.h"

extern unsigned char parse_movement(){
	unsigned char *buff = malloc(sizeof(char));
	WORD rb = 0;
	char steering = 0;
	unsigned char dir = DIR_NON,
					acc = ACC_NON;

	while((*buff) != '('){
		pf_read(buff, 1, &rb);
		if(!rb)
			return 'P';
	}

	pf_read(buff, 1, &rb);
	if(!rb)
		return PARSE_ERR;

	switch((*buff)){
		case '<':
			steering = 1;
			dir = DIR_LFT;
			break;
		case '>':
			steering = 1;
			dir = DIR_RGT;
			break;
	}

	/* Advance if steering command present */
	if(steering){
		pf_read(buff, 1, &rb);
		if(!rb)
			return PARSE_ERR;
	}

	switch((*buff)){
		case '-':
			acc = ACC_BRK;
			break;
		case '^':
		case 'A':
			acc = ACC_FWD;
			break;
		case 'v':
		case 'V':
			acc = ACC_BKD;
			break;
		default:
			return 'X';
	}

	/* Also consume the ')' */
	if(steering){
		pf_read(buff, 1, &rb);
		if(!rb)
			return PARSE_ERR;
	}

	return (unsigned char)(acc | dir);
}
