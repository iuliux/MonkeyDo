#include "parser.h"

extern unsigned char parse_movement(){
	unsigned char *buff = malloc(sizeof(char));
	WORD rb = 0;
	char steering = 0;
	unsigned char dir = DIR_NON,
					acc = ACC_NON;
	(*buff)	= '\0';

	while((*buff) != '('){
		pf_read(buff, 1, &rb);
		if(!rb){
			free(buff);
			return PARSE_ERR;
		}
	}

	pf_read(buff, 1, &rb);
	if(!rb){
		free(buff);
		return PARSE_ERR;
	}

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
		if(!rb){
			free(buff);
			return PARSE_ERR;
		}
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
			free(buff);
			return PARSE_ERR;
	}

	/* Also consume the ')' */
	if(steering){
		pf_read(buff, 1, &rb);
		if(!rb){
			free(buff);
			return PARSE_ERR;
		}
	}

	free(buff);
	return (unsigned char)(acc | dir);
}

static int is_digit(char c){
	switch(c){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return 1;
	}
	return 0;
}

extern unsigned int parse_duration(){
	unsigned char *buff = malloc(sizeof(char));
	WORD rb = 0;
	unsigned int acc = 0;

	/* Consume whitespace */
	while(!is_digit(*buff)){
		pf_read(buff, 1, &rb);
		if(!rb){
			free(buff);
			return 0;
		}
	}

	while(is_digit(*buff)){
		acc *= 10;
		acc += (*buff) - '0';
		pf_read(buff, 1, &rb);
		if(!rb)
			break;
	}

	free(buff);
	return acc;
}
