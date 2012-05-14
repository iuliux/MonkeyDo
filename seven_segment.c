#include "seven_segment.h"

void init_sseg(){
	ADCSRA &= ~(1<<ADEN);

	DDRA = 0xFF;
	PORTA = 0x00;
}

/*
	Seven segment one character display
	 __7__
	|     |
	5     6
	|__4__|
	|     |
	1     3
	|__2__|

*/

extern void sseg_display(char c){
	switch(c){
		case ' ':
			/*
				Clear
			*/
			PORTA = 0x00;
			break;
		case '0':
		case 'O':
		case 'o':
		case 'D':
			/*
				 __
				|  |
				|__|

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA3) | (1<<PA5) |
					(1<<PA6) | (1<<PA7);
			break;
		case '1':
			/*

				|
				|

			*/
			PORTA = (1<<PA1) | (1<<PA5);
			break;
		case '2':
			/*
				 __
				 __|
				|__ 

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA4) | (1<<PA6) |
					(1<<PA7);
			break;
		case '3':
			/*
				 __
				 __|
				 __|

			*/
			PORTA = (1<<PA3) | (1<<PA2) |
					(1<<PA4) | (1<<PA6) |
					(1<<PA7);
			break;
		case '4':
			/*
			
				|__|
				   |

			*/
			PORTA = (1<<PA3) | (1<<PA4) |
					(1<<PA5) | (1<<PA6);
			break;
		case '6':
			/*
				 __
				|__ 
				|__|

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA4) | (1<<PA5) |
					(1<<PA7) | (1<<PA3);
			break;
		case '7':
			/*
				 __
				   |
				   |

			*/
			PORTA = (1<<PA3) | (1<<PA6) |
					(1<<PA7);
			break;
		case '9':
			/*
				 __
				|__|
				 __|

			*/
			PORTA = (1<<PA7) | (1<<PA2) |
					(1<<PA3) | (1<<PA4) |
					(1<<PA5) | (1<<PA6);
			break;
		case 'F':
		case 'f':
			/*
				 __
				|__
				|

			*/
			PORTA = (1<<PA1) | (1<<PA5) |
					(1<<PA4) | (1<<PA7);
			break;
		case 'E':
			/* Probably used for Error
				 __
				|__
				|__

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA4) | (1<<PA5) |
					(1<<PA7);
			break;
		case '8':
		case 'B':
			/*
				 __
				|__|
				|__|

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA3) | (1<<PA4) |
					(1<<PA5) | (1<<PA6) |
					(1<<PA7);
			break;
		case 'P':
			/*
				 __
				|__|
				|

			*/
			PORTA = (1<<PA1) | (1<<PA4) |
					(1<<PA5) | (1<<PA6) |
					(1<<PA7);
			break;
		case 'A':
		case 'R':
			/*
				 __
				|__|
				|  |

			*/
			PORTA = (1<<PA1) | (1<<PA3) |
					(1<<PA5) | (1<<PA6) |
					(1<<PA7) | (1<<PA4);
			break;
		case '5':
		case 'S':
			/*
				 __
				|__ 
				 __|

			*/
			PORTA = (1<<PA5) | (1<<PA2) |
					(1<<PA3) | (1<<PA4) |
					(1<<PA7);
			break;
		case 'L':
			/*
				 
				|
				|__

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA5);
			break;
		case 'b':
			/*
				 
				|__
				|__|

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA3) | (1<<PA4) |
					(1<<PA5);
			break;
		case 'd':
			/*
				 
				 __|
				|__|

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA3) | (1<<PA4) |
					(1<<PA6);
			break;
		case 'e':
			/*
				 __
				|__|
				|__ 

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA7) | (1<<PA4) |
					(1<<PA5) | (1<<PA6);
			break;
		case 'r':
			/*
			
				 __
				|

			*/
			PORTA = (1<<PA1) | (1<<PA4);
			break;
		case 'X':
		case 'H':
		case 'M':
		case 'N':
			/*
				
				|__|
				|  |

			*/
			PORTA = (1<<PA1) | (1<<PA6) |
					(1<<PA3) | (1<<PA4) |
					(1<<PA5);
			break;
		case 'K':
		case 'k':
			/*
				 __
				|__ 
				|  |

			*/
			PORTA = (1<<PA1) | (1<<PA3) |
					(1<<PA5) | (1<<PA4) |
					(1<<PA7);
			break;
		case 'U':
			/*
				
				|  |
				|__|

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA3) | (1<<PA5) |
					(1<<PA6);
			break;
		case 'n':
			/*
				
				 __
				|  |

			*/
			PORTA = (1<<PA1) | (1<<PA3) |
					(1<<PA4);
			break;
		case 'I':
		case 'i':
			/*

				   |
				   |

			*/
			PORTA = (1<<PA3) | (1<<PA6);
			break;
		case 'T':
		case 't':
			/*
				 __
				|   
				|   

			*/
			PORTA = (1<<PA1) | (1<<PA5) |
					(1<<PA7);
			break;
		case '.':
			/*
				
				 
				   |

			*/
			PORTA = (1<<PA3);
			break;

		/* Movement chars */
		case '^':
			/*
				 __
				|  |
				    

			*/
			PORTA = (1<<PA5) | (1<<PA6) |
					(1<<PA7);
			break;
		case 'v':
		case 'V':
		case 'u':
			/*
				
				 
				|__|

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA3);
			break;
		case '>':
			/*
				
				 __|
				   |

			*/
			PORTA = (1<<PA3) | (1<<PA4) |
					(1<<PA6);
			break;
		case '<':
			/*
				
				|__
				|  

			*/
			PORTA = (1<<PA1) | (1<<PA4) |
					(1<<PA5);
			break;
		case '-':
			/*
				
				 __
				   

			*/
			PORTA = (1<<PA4);
			break;

		/* Composed movement symbolic chars */
		case FWD_LEFT_CHAR:
			/*
				 __
				|  |
				|

			*/
			PORTA = (1<<PA1) | (1<<PA6) |
					(1<<PA5) | (1<<PA7);
			break;
		case FWD_RIGHT_CHAR:
			/*
				 __
				|  |
				   |

			*/
			PORTA = (1<<PA3) | (1<<PA6) |
					(1<<PA5) | (1<<PA7);
			break;
		case BKD_LEFT_CHAR:
			/*
				
				|
				|__|

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA3) | (1<<PA5);
			break;
		case BKD_RIGHT_CHAR:
			/*
				
				   |
				|__|

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA3) | (1<<PA6);
			break;
		
		default:
			/*
				 __
				 __
				 __ 

			*/
			PORTA = (1<<PA2) | (1<<PA4) |
					(1<<PA7);
	}
}


extern void sseg_wait_anim(){
	int i = 0;
	while(i++ < 6){
		switch(i){
			case 0:
				/*
					 __
					   |
					

				*/
				PORTA = (1<<PA6) | (1<<PA7);
				break;
			case 1:
				/*
					 
					   |
					   |

				*/
				PORTA = (1<<PA6) | (1<<PA3);
				break;
			case 2:
				/*
					
					
					__|

				*/
				PORTA = (1<<PA3) | (1<<PA2);
				break;
			case 3:
				/*
					
					
					|__

				*/
				PORTA = (1<<PA1) | (1<<PA2);
				break;
			case 4:
				/*
					 
					|
					|

				*/
				PORTA = (1<<PA1) | (1<<PA5);
				break;
			case 5:
				/*
					 __
					|
					

				*/
				PORTA = (1<<PA5) | (1<<PA7);
				break;
		}

		_delay_ms(50.);
	}
}

/* Displays an error message */
extern void sseg_error(char c){
	sseg_display('E');
	_delay_ms(600.);
	sseg_display(c);
	_delay_ms(600.);
}

/* Prints a string char by char
 * (Well, tries it's best, I mean) */
extern void print_str(char *str){
	while(str[0] != '\0'){
		sseg_display(str[0]);
		str++;
		_delay_ms(800.);
		sseg_display(' ');
		_delay_ms(50.);
	}
}
