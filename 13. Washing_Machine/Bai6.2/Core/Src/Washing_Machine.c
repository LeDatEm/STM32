
#include "main.h"
#include "port.h"
#include "keypad.h"
#define MAX_FILL_DURATION 5
#define MAX_HEAT_DURATION 5
#define MAX_DRAIN_DURATION 5

typedef enum {INIT, START, FILL1, HEAT, WASH, DRAIN1, FILL2, RINSE, DRAIN2, ERROR_STATE} System_State;

static System_State current_state = INIT;
static unsigned char detergent[9] = {0, 1, 1, 1, 1, 0, 0, 0, 0};
static unsigned char heat[9] = {0, 1, 1, 1, 1, 0, 0, 0, 0};
static unsigned wash_mode = 0;
static unsigned time_in_state = 0;

int last_pressed_key = 0;
int sskey = 0;
void WASHER_Update(void) {

    switch(current_state) {
        case INIT:
            GPIOA->ODR &= ~((uint32_t)0x3FF80);
            GPIOB->ODR &= ~((uint32_t)0x3FFFF);
            keypad();

            while(1) {
                int key_pressed = keypad();
                if(key_pressed >= 1 && key_pressed <= 8) {
                    GPIOA->ODR &= ~((uint32_t)0xFF80);
                    GPIOA->ODR |= (1 << (6 + key_pressed));
                    last_pressed_key = key_pressed;
                } else if(key_pressed == 9) {

                    wash_mode = key_pressed ;
                    GPIOA->ODR &= ~((uint32_t)0xFF80);
                    GPIOA->ODR |= (1 << (6 + last_pressed_key));
                    current_state = START;

                    break;
                }
            }


            break;
        case START:

        	time_in_state++;
        	switch(time_in_state){
        	case 1:
        		GPIOA->ODR |= (1 << 15);
        		break;

        	case 2:
        		GPIOB->ODR |= (1 << 0);
        		break;

			case 3:
				GPIOB->ODR |= (1 << 1);
				break;

			case 4:
				if(detergent[last_pressed_key] == 1){
					GPIOB->ODR |= (1 << 2);
				}
					time_in_state = 0;
					current_state = FILL1;
				break;
        	}
            break;

        	case FILL1:
        	    GPIOB->ODR |= (1 << 3);
        	    sskey = keypad();
        	    if (sskey == 10) {
        	    	sskey = 0;
        	    	GPIOB->ODR &= ~(1 << 1);
        	        GPIOB->ODR &= ~(1 << 3);
        	        GPIOB->ODR |= (1 << 4);
        	        if (heat[last_pressed_key] == 1) {
        	            current_state = HEAT;
        	            time_in_state = 0;
        	        } else {
        	            current_state = WASH;
        	        }
        	    }
        	    if (++time_in_state >= MAX_FILL_DURATION) {
        	        current_state = ERROR_STATE;
        	    }
        	    break;
        case HEAT:
        	GPIOB->ODR |= (1 << 5);
    	    if (++time_in_state >= MAX_FILL_DURATION) {
    	        current_state = ERROR_STATE;
    	    }
        	sskey = keypad();
			if(sskey == 10){
					sskey = 0;
					GPIOB->ODR &= ~(1 << 5);
					GPIOB->ODR |= (1 << 6);
					current_state = WASH;
				}
            break;
        case WASH:
        	GPIOB->ODR |= (1 << 7);
        	current_state = DRAIN1;
            break;
        case DRAIN1:
        	GPIOB->ODR &= ~(1 << 7);
        	GPIOB->ODR |= (1 << 8);
			if (++time_in_state >= MAX_DRAIN_DURATION) {
				current_state = ERROR_STATE;
			}
			sskey = keypad();
			if(sskey == 11){
				sskey = 0;
				GPIOB->ODR &= ~(1 << 8);
				GPIOB->ODR |= (1 << 9);
				current_state = FILL2;
				time_in_state = 0;
			}
            break;
        case FILL2:
        	GPIOB->ODR |= (1 << 1);
    	    GPIOB->ODR |= (1 << 10);
    	    sskey = keypad();
    	    if (sskey == 10) {
    	    	sskey = 0;
    	    	GPIOB->ODR &= ~(1 << 1);
    	    	GPIOB->ODR &= ~(1 << 4);
    	        GPIOB->ODR &= ~(1 << 10);
    	        GPIOB->ODR |= (1 << 11);
    	        current_state = RINSE;
    	    }
    	    if (++time_in_state >= MAX_FILL_DURATION) {
    	        current_state = ERROR_STATE;
    	    }
            break;
        case RINSE:
        	GPIOB->ODR |= (1 << 12);
        	current_state = DRAIN2;
            break;
        case DRAIN2:
        	GPIOB->ODR &= ~(1 << 12);
			GPIOB->ODR |= (1 << 13);
			if (++time_in_state >= MAX_DRAIN_DURATION) {
				current_state = ERROR_STATE;
			}
			sskey = keypad();
			if(sskey == 11){
				sskey = 0;
				GPIOB->ODR &= ~(1 << 13);
				GPIOB->ODR |= (1 << 14);
				current_state = INIT;
				time_in_state = 0;
				}
            break;
        case ERROR_STATE:
        	GPIOA->ODR &= ~((uint32_t)0x3FF80);
        	GPIOB->ODR &= ~((uint32_t)0x3FFFF);
        	GPIOB->ODR |= (1 << 15);
            break;
        default:
            break;
    }
}
