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
			/*
				 __
				|__
				|

			*/
			PORTA = (1<<PA1) | (1<<PA5) |
					(1<<PA4) | (1<<PA7);
			break;
		case 'E':
		case 0xFF:
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
		case 'r':
			/*
			
				 __
				|

			*/
			PORTA = (1<<PA1) | (1<<PA4);
			break;
		case 'X':
		case 'H':
			/*
				
				|__|
				|  |

			*/
			PORTA = (1<<PA1) | (1<<PA6) |
					(1<<PA3) | (1<<PA4) |
					(1<<PA5);
			break;
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
		case '<':
			/*
				
				 __|
				   |

			*/
			PORTA = (1<<PA3) | (1<<PA4) |
					(1<<PA6);
			break;
		case '>':
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
		default:
			/*
				 
				 __
				|__|

			*/
			PORTA = (1<<PA1) | (1<<PA2) |
					(1<<PA3) | (1<<PA4);
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

		_delay_ms(1000);
	}
}