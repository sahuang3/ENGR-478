#include "stm32l476xx.h"
#include "LED.h"
#include "button.h"
#include "Systick_timer.h"


int main(void){

	//1. Invoke configure_LED_pin() to initialize PA5 as an output pin, interfacing with the LD2 LED.
	configure_LED_pin();
	//2. Turn on the LD2 LED
	turn_on_LED();
	
	configure_Button_pin();
	
	config_EXTI();
	
	//3. Invoke SysTick_Init() to set up SysTick periodic exception. 
	//   The default processor clock is 4MHz provided by MSI. 
	//   The SysTick reload value is set to 4,000,000 - 1 to generate periodic exception every 1 s
	//SysTick_Init(4000000);

	
	while(1){
		
	}
}
