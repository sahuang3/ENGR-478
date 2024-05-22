#include "stm32l476xx.h"


void configure_PB_pin(){
	
	// Enable clock for port B
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	
	// Reset pins for PB4 and PB5 
	GPIOB->MODER &= ~GPIO_MODER_MODER4;
	GPIOB->MODER &= ~GPIO_MODER_MODER5;
	GPIOB->MODER |= ~GPIO_MODER_MODER4_0;
	GPIOB->MODER |= ~GPIO_MODER_MODER5_0;
	
	// Configure GPIO Output Mode to 'Push-Pull'
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT4;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT5;
	
	//  Configure PB4 PB5 to "No Pull-up or Pull-down"
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5;
}

void configure_PC_pin(){
	
	// Enable clock for port C
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	
	// Reset pins for PC2 and PC3 
	GPIOB->MODER &= ~GPIO_MODER_MODER2;
	GPIOB->MODER &= ~GPIO_MODER_MODER3;
	
	// Configure GPIO Output Mode to 'Push-Pull'
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT2;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT3;
	
	//  Configure PB4 PB5 to "No Pull-up or Pull-down"
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD2;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD3;
}

// Configure LED 1
void turn_on_LED1(){
	GPIOB->ODR |= GPIO_ODR_OD4;
}

void turn_off_LED1(){
	GPIOB->ODR &= ~GPIO_ODR_OD4;
}

void toggle_LED1(){
	GPIOB->ODR ^= GPIO_ODR_OD4;
}

// Configure LED 2
void turn_on_LED2(){
	GPIOB->ODR &= GPIO_ODR_OD5;
}
void turn_off_LED2(){
	GPIOB->ODR |= ~GPIO_ODR_OD5;
}
void toggle_LED2(){
	GPIOB->ODR ^= GPIO_ODR_OD5;
}


int main(void){
	
	// Configure ports B and C
	configure_PB_pin();
	configure_PC_pin();
	turn_off_LED1();
	turn_off_LED2();
	
	int i;
	
	while(1){

		// When Switch 2 is pressed, turn off both LEDs
			if((GPIOC->IDR & GPIO_IDR_ID3) == 0){
				turn_off_LED1();
				turn_off_LED2();
			} else if((GPIOC->IDR & GPIO_IDR_ID2) == 0){
				// When Switch 1 is pressed, toggle LED1 and turn off LED2
				toggle_LED1();
				turn_off_LED2();
				for(i=0; i<150000; i++);
			} else{
				// When no buttons are pressed, turn off LED1 and toggle LED2
				turn_off_LED1();
				toggle_LED2();
				for(i=0; i<150000; i++);
			}
		}
}