#include "stm32l476xx.h"

// PA5  <--> Green LED (LD2)


void configure_LED_pin(){
  // 1. Enable the clock to GPIO Port A	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
		
	// 2. Configure GPIO Mode to 'Output': Input(00), Output(01), AlterFunc(10), Analog(11)
	GPIOA->MODER &= ~GPIO_MODER_MODER5; // Clear Mode bits for PA5
	GPIOA->MODER |= GPIO_MODER_MODER5_0; // Set the Mode bits to '01'

	// 3. Configure GPIO Output Type to 'Push-Pull': Output push-pull (0), Output open drain (1) 
	GPIOA ->OTYPER &= ~GPIO_OTYPER_OT5;
	
	// 4. Configure GPIO Pull-Up/Pull-Down to 'No Pull-up or Pull-down': No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
}

void configure_LED_button(){
	
	// Enable the clock for GPIO Port C
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	
	// Configure GPIO Mode to Input
	GPIOC->MODER &= ~GPIO_MODER_MODER13;
	
	// Configure GPIO Output Type to 'Push-Pull'
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT13;
	
	// Configure GPIO Pull-up/Pull-down to 'No Pull-up or Pull-down'
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR13;
	
}

// Modular function to turn on the LD2 LED.
void turn_on_LED(){
	GPIOA->ODR &= GPIO_ODR_OD5;
	GPIOA->ODR |= GPIO_ODR_OD5;
}

// Modular function to turn off the LD2 LED.
void turn_off_LED(){
	GPIOA->ODR &= ~GPIO_ODR_OD5;
}

// Modular function to toggle the LD2 LED.
void toggle_LED(){
	GPIOA->ODR ^= GPIO_ODR_OD5;
}

int main(void){
	int i;
	//1. Invoke configure_LED_pin() to initialize PA5 as an output pin, interfacing with the LD2 LED.
	configure_LED_pin();
	configure_LED_button();
	//2. Turn on the LD2 LED
	//turn_on_LED();
	
	// Infinite loop to toggle the LED, making it blink at a specified frequency.
	while(1){
		if((GPIOC->IDR & 1UL<<13) == 0){
			turn_on_LED();
		} else {
			turn_off_LED();
		}
	}
}