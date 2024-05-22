#include "LED.h"
#include "ADC.h"
#include "Systick_timer.h"
#include "button.h"
// PA5  <--> Green LED
#define LED_GREEN_PIN    5
// PA6  <--> YELLOW LED 
#define LED_YELLOW_PIN   6
// PA7  <--> RED LED
#define LED_RED_PIN      7
//extern int counter;


void configure1_LED_GREEN_pin(){
  // 1. Enable the clock to GPIO Port A	

  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;   
		
	// 2. Configure GPIO Mode to 'Output': Input(00), Output(01), AlterFunc(10), Analog(11)
	GPIOA->MODER &= ~(3UL<<(2*LED_GREEN_PIN));  
	GPIOA->MODER |=   1UL<<(2*LED_GREEN_PIN);   // Output(01)

	// 3. Configure GPIO Output Type to 'Push-Pull': Output push-pull (0), Output open drain (1) 
		GPIOA->OTYPER &= ~(1<<LED_GREEN_PIN);   // Push-pull
	
	// 4. Configure GPIO Push-Pull to 'No Pull-up or Pull-down': No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOA->PUPDR  &= ~(0b11<<(2*LED_GREEN_PIN)); // No pull-up, no pull-down
}

//-------------------------------------------------GREEN-------------------------------------------------------------------------------
void configure1_LED_YELLOW_pin(){
  // 1. Enable the clock to GPIO Port A	
	//# define RCC_AHB2ENR_GPIOAEN ((uint32_t)0x00000001U)
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;   
		
	// 2. Configure GPIO Mode to 'Output': Input(00), Output(01), AlterFunc(10), Analog(11)
	GPIOA->MODER &= ~(3UL<<(2*LED_YELLOW_PIN));  
	GPIOA->MODER |=   1UL<<(2*LED_YELLOW_PIN);      // Output(01)

	// 3. Configure GPIO Output Type to 'Push-Pull': Output push-pull (0), Output open drain (1) 
	GPIOA->OTYPER &= ~(1<<LED_YELLOW_PIN);      // Push-pull
	
	// 4. Configure GPIO Push-Pull to 'No Pull-up or Pull-down': No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOA->PUPDR  &= ~(0b11<<(2*LED_YELLOW_PIN));  // No pull-up, no pull-down
}


//----------------------------------------------YELLOW--------------------------------------------------------------------------------

void configure1_LED_RED_pin(){
  // 1. Enable the clock to GPIO Port A	
	# define RCC_AHB2ENR_GPIOAEN ((uint32_t)0x00000001U)
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;   
		
	// 2. Configure GPIO Mode to 'Output': Input(00), Output(01), AlterFunc(10), Analog(11)
	GPIOA->MODER &= ~(3UL<<(2*LED_RED_PIN));  
	GPIOA->MODER |=   1UL<<(2*LED_RED_PIN);      // Output(01)

	// 3. Configure GPIO Output Type to 'Push-Pull': Output push-pull (0), Output open drain (1) 
	GPIOA->OTYPER &= ~(1<<LED_RED_PIN);      // Push-pull
	
	// 4. Configure GPIO Push-Pull to 'No Pull-up or Pull-down': No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOA->PUPDR  &= ~(0b11<<(2*LED_RED_PIN));  // No pull-up, no pull-down
}

//-----------------------------------------------------------RED---------------------------------------------------------------------------
// Modular function to turn on the LD2 LED.
void turn1_off_LED_GREEN(){
	GPIOA->ODR |= 1 << LED_GREEN_PIN  ;
	//counter ++;
}

// Modular function to turn off the LD2 LED.
void turn1_on_LED_GREEN(){
	GPIOA->ODR &= ~(1 << LED_GREEN_PIN);
}

// Modular function to toggle the LD2 LED.
void toggle1_LED_GREEN(){
	GPIOA->ODR ^= (1 << LED_GREEN_PIN);
}

//----------------GREEN-----------------------------





// Modular function to turn on the LD2 LED.
void turn1_off_LED_YELLOW(){
	GPIOA->ODR |= 1 << LED_YELLOW_PIN;
	//counter ++;
}

// Modular function to turn off the LD2 LED.
void turn1_on_LED_YELLOW(){
	GPIOA->ODR &= ~(1 << LED_YELLOW_PIN);
}

// Modular function to toggle the LD2 LED.
void toggle1_LED_YELLOW(){
	GPIOA->ODR ^= (1 << LED_YELLOW_PIN);
}

//-----------YELLOW-----------------------------

// Modular function to turn on the LD2 LED.
void turn1_off_LED_RED(){
	GPIOA->ODR |= 1 << LED_RED_PIN;
	//counter ++;
}

// Modular function to turn off the LD2 LED.
void turn1_on_LED_RED(){
	GPIOA->ODR &= ~(1 << LED_RED_PIN);
}

// Modular function to toggle the LD2 LED.
void toggle1_LED_RED(){
	GPIOA->ODR ^= (1 << LED_RED_PIN);
}

//-----------RED----------------------------