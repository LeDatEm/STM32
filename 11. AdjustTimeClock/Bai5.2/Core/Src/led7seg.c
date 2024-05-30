
#include "main.h"
#include "port.h"

unsigned char tbl47segA [] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xBF};
unsigned char buff [8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t delay_counter = 0;


void scanLED(int tx){
    uint16_t LED_PINS[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
    for(int i = 0; i < 8; ++i){
        HAL_GPIO_WritePin(LED7SEG_PORT, LED_PINS[i], GPIO_PIN_SET);
        LED7SEG_PORT->ODR &= 0xFF00;
        LED7SEG_PORT->ODR |= tbl47segA[buff[i]];
        //SysTick_delay(tx);
        while(++delay_counter < 100);
        delay_counter = 0;
        HAL_GPIO_WritePin(LED7SEG_PORT, LED_PINS[i], GPIO_PIN_RESET);
    }
}

void printLED(int hour, int minute, int second){
	buff[0] = hour / 10;
	buff[1] = hour % 10;
	buff[2] = 10;
	buff[3] = minute / 10;
	buff[4] = minute % 10;
	buff[5] = 10;
	buff[6] = second / 10;
	buff[7] = second % 10;

	scanLED(5);
}
