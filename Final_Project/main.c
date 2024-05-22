#include "stm32l476xx.h"
#include "ADC.h"
#include "LED.h"
#include "button.h"
#include "Systick_timer.h"

volatile long counter = 0;


void delay(uint32_t delay) {
    // Implement a simple software delay function
    volatile uint32_t i;
    for (i = 0; i < delay; ++i) {
        // Do nothing
    }
}



int main(void){
 int i;
	//1. Invoke configure_LED_pin() to initialize PA5 as an output pin, interfacing with the LD2 LED.
	 configure1_LED_GREEN_pin();
   configure1_LED_YELLOW_pin();
   configure1_LED_RED_pin();
	


	//2. Turn on the LD1 LED
   turn1_off_LED_GREEN();
   turn1_off_LED_YELLOW();
   turn1_off_LED_RED();
 

	configure_Button_pin();

	//ADC_Init();
	
	// After initialization, begin ADC conversion with a software trigger by setting ADSTART bit in ADC1_CR.
//ADC1->CR |= ADC_CR_ADSTART;	

	
	config_EXTI();
	


while(1){
   
		
			if (counter == 0) {
				turn1_on_LED_GREEN();
				turn1_off_LED_RED();
				turn1_off_LED_YELLOW();
				delay(500000);
				SysTick_Handler();
				counter = 1;
				
			} 
			if (counter == 1) {
				turn1_on_LED_YELLOW();
				turn1_off_LED_GREEN();
				turn1_off_LED_RED();
				delay(500000);
				SysTick_Handler();
				counter = 2;
				
			}
			if (counter == 2) {
				turn1_on_LED_RED();
				turn1_off_LED_GREEN();
				turn1_off_LED_YELLOW();
				delay(500000);
				SysTick_Handler();
				counter = 0;

			}
			
	
}
}
