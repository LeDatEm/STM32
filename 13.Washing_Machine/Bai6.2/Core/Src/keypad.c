
#include "main.h"
#include "port.h"



int keypad(void){
	uint8_t number = -1;
	GPIOA->BSRR = GPIO_PIN_0 << 16;
	GPIOA->BSRR = GPIO_PIN_1;
	GPIOA->BSRR = GPIO_PIN_2;
	GPIOA->BSRR = GPIO_PIN_3;
	if(!(GPIOA->IDR & GPIO_PIN_4))
		 number = 1;
	else if(!(GPIOA->IDR & GPIO_PIN_5))
		 number = 2;
	else if (!(GPIOA->IDR & GPIO_PIN_6))
		 number = 3;

	GPIOA->BSRR = GPIO_PIN_0;
	GPIOA->BSRR = GPIO_PIN_1 << 16;
	GPIOA->BSRR = GPIO_PIN_2;
	GPIOA->BSRR = GPIO_PIN_3;
	if(!(GPIOA->IDR & GPIO_PIN_4))
		 number = 4;
	else if(!(GPIOA->IDR & GPIO_PIN_5))
		 number = 5;
	else if (!(GPIOA->IDR & GPIO_PIN_6))
		 number = 6;

	GPIOA->BSRR = GPIO_PIN_0;
	GPIOA->BSRR = GPIO_PIN_1;
	GPIOA->BSRR = GPIO_PIN_2 << 16;
	GPIOA->BSRR = GPIO_PIN_3;
	if(!(GPIOA->IDR & GPIO_PIN_4))
		 number = 7;
	else if(!(GPIOA->IDR & GPIO_PIN_5))
		 number = 8;
	else if (!(GPIOA->IDR & GPIO_PIN_6))
		 number = 9;

	GPIOA->BSRR = GPIO_PIN_0;
	GPIOA->BSRR = GPIO_PIN_1;
	GPIOA->BSRR = GPIO_PIN_2;
	GPIOA->BSRR = GPIO_PIN_3 << 16;
	if(!(GPIOA->IDR & GPIO_PIN_4))
		 number = 10;
	else if(!(GPIOA->IDR & GPIO_PIN_5))
		 number = 0;
	else if (!(GPIOA->IDR & GPIO_PIN_6))
		 number = 11;

	GPIOA->BSRR = GPIO_PIN_3;
	return number;

}
