
#include "main.h"
#include "port.h"

unsigned char tbl47segA [] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xC3, 0xE1, 0xC8, 0xC7};
unsigned char buff [4] = {0, 0, 0, 0};
/* USER CODE END PV */

void scanLED(int tx){
    uint16_t LED_PINS[] = {LED1, LED2, LED3, LED4};
    for(int i = 0; i < 4; ++i){
        HAL_GPIO_WritePin(LED7SEG_PORT, LED_PINS[i], GPIO_PIN_SET);
        LED7SEG_PORT->ODR &= 0xFF00;
        LED7SEG_PORT->ODR |= tbl47segA[buff[i]];
        HAL_Delay(tx);
        HAL_GPIO_WritePin(LED7SEG_PORT, LED_PINS[i], GPIO_PIN_RESET);
    }
}

void printLED(int value){
	buff[0] = value / 1000;
	buff[1] = (value % 1000) / 100;
	buff[2] = ((value % 1000) % 100) /10;
	buff[3] = ((value % 1000) % 100) % 10;
	scanLED(1);
}

void printLEDCharWin(){
	buff[0] = 10;
	buff[1] = 11;
	buff[2] = 1;
	buff[3] = 12;
	scanLED(1);
}

void printLEDCharLoss(){
	buff[0] = 13;
	buff[1] = 0;
	buff[2] = 5;
	buff[3] = 5;
	scanLED(1);
}

