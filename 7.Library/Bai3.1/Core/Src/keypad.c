
#include "main.h"
#include "port.h"


uint8_t number;

int keypad(void){
	KEYPAD_PORT->BSRR = ~ROW1;
	KEYPAD_PORT->BSRR = ROW2;
	KEYPAD_PORT->BSRR = ROW3;
	KEYPAD_PORT->BSRR = ROW4;
	if(!(KEYPAD_PORT->IDR & COLUM1))
		 number = 1;
	else if(!(KEYPAD_PORT->IDR & COLUM2))
		 number = 2;
	else if (!(KEYPAD_PORT->IDR & COLUM3))
		 number = 3;

	KEYPAD_PORT->BSRR = ROW1;
	KEYPAD_PORT->BSRR = ~ROW2;
	KEYPAD_PORT->BSRR = ROW3;
	KEYPAD_PORT->BSRR = ROW4;
	if(!(KEYPAD_PORT->IDR & COLUM1))
		 number = 4;
	else if(!(KEYPAD_PORT->IDR & COLUM2))
		 number = 5;
	else if (!(KEYPAD_PORT->IDR & COLUM3))
		 number = 6;

	KEYPAD_PORT->BSRR = ROW1;
	KEYPAD_PORT->BSRR = ROW2;
	KEYPAD_PORT->BSRR = ~ROW3;
	KEYPAD_PORT->BSRR = ROW4;
	if(!(KEYPAD_PORT->IDR & COLUM1))
		 number = 7;
	else if(!(KEYPAD_PORT->IDR & COLUM2))
		 number = 8;
	else if (!(KEYPAD_PORT->IDR & COLUM3))
		 number = 9;

	KEYPAD_PORT->BSRR = ROW1;
	KEYPAD_PORT->BSRR = ROW2;
	KEYPAD_PORT->BSRR = ROW3;
	KEYPAD_PORT->BSRR = ~ROW4;
	if(!(KEYPAD_PORT->IDR & COLUM1))
		 number = 10;
	else if(!(KEYPAD_PORT->IDR & COLUM2))
		 number = 0;
	else if (!(KEYPAD_PORT->IDR & COLUM3))
		 number = 11;

	KEYPAD_PORT->BSRR = ROW4;
	return number;

}
