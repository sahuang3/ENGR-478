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
	GPIOA->PUPDR &= GPIO_PUPDR_PUPD5;
}

// Modular function to turn on the LD2 LED.
void turn_on_LED(){
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
	//2. Turn on the LD2 LED
	turn_on_LED();
	
	// Infinite loop to toggle the LED, making it blink at a specified frequency.
	while(1){
		for(i=0; i<100000; i++); 	// 1. Implement a simple delay to control the LED blinking speed
		toggle_LED();							//2. Toggle the LED
	}
}
