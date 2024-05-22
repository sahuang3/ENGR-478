#include "stm32l476xx.h"
#define LED1_PIN 4
#define LED2_PIN 5
#define SW1_PIN 2
#define SW2_PIN 3
volatile int count = 0;

void configure_LED_pins() {
// Enable the clock to GPIO Port B
RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
// Configure GPIO Mode to 'Output'
GPIOB->MODER &= ~(3UL<<(2*LED1_PIN));
GPIOB->MODER |= 1UL<<(2*LED1_PIN); // Output
GPIOB->MODER &= ~(3UL<<(2*LED2_PIN));
GPIOB->MODER |= 1UL<<(2*LED2_PIN); // Output
// Turn on both LEDs at startup
GPIOB->ODR |= 1 << LED1_PIN;
GPIOB->ODR &= ~(1 << LED2_PIN);
}

void configure_SW_pins() {
// Enable the clock to GPIO Port C
RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
// Configure GPIO Mode to 'Input' for SW1
GPIOC->MODER &= ~(3UL<<(2*SW1_PIN));
// Configure GPIO Mode to 'Input' for SW2
GPIOC->MODER &= ~(3UL<<(2*SW2_PIN));
// Add Pull-up for SW2 (Negative Logic)
GPIOC->PUPDR &= ~(1UL<<(2*SW2_PIN));

//GPIOC->PUPDR &= ~(1UL<<(2*SW1_PIN));

}

void turn_on_LED1() {
GPIOB->ODR |= 1 << LED1_PIN;
}

void turn_off_LED1() {
GPIOB->ODR &= ~(1 << LED1_PIN);
}

void turn_off_LED2() {
GPIOB->ODR |= 1 << LED2_PIN;
}

void turn_on_LED2() {
GPIOB->ODR &= ~(1 << LED2_PIN);
}

void decrease() {
if (count < 0){
  count = 3;
} else {
  count--;
  }
}

void increase(){
if (count > 3){
  count = 0;
} else {
  count++;
  }
}

void display(){
if (count == 1){
  turn_on_LED1();
  turn_off_LED2();
} else if (count == 2){
  turn_on_LED2();
  turn_off_LED1();
} else if (count == 3){
  turn_on_LED1();
  turn_on_LED2();
} else if (count == 0){
  turn_off_LED1();

  turn_off_LED2();
  }
}

void configure_EXTI(void){
// Enable the EXTI2 and EXTI3 interrupts in NVIC
NVIC_EnableIRQ(EXTI2_IRQn);
NVIC_EnableIRQ(EXTI3_IRQn);
  
// Configure the SYSCFG module to link EXTI lines 2 and 3 to GPIO PC2 and PC3
RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
SYSCFG->EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI2 | SYSCFG_EXTICR1_EXTI3);
  
// Clear EXTI2 and EXTI3 bits
SYSCFG->EXTICR[0] |= (SYSCFG_EXTICR1_EXTI2_PC |
SYSCFG_EXTICR1_EXTI3_PC); // Set PC2 and PC3 as EXTI sources
  
// Enable interrupts for both EXTI2 and EXTI3
EXTI->IMR1 |= (1 << SW1_PIN) | (1 << SW2_PIN);
  
// Enable rising edge triggers for EXTI2 (SW1 - Positive Logic)
EXTI->RTSR1 |= (1 << SW1_PIN);
  
// Enable falling edge triggers for EXTI3 (SW2 - Negative Logic)
EXTI->RTSR1 |= (1 << SW2_PIN);
}

void EXTI2_IRQHandler(void) {
// Check if the interrupt is triggered by EXTI2 (SW1)
if ((EXTI->PR1 & (1 << SW1_PIN)) != 0) {
  // Clear the EXTI2 pending bit
  EXTI->PR1 |= (1 << SW1_PIN);
  // increase counter
  increase();
  display();
  }
}

void EXTI3_IRQHandler(void) {
// Check if the interrupt is triggered by EXTI3 (SW2)
if ((EXTI->PR1 & (1 << SW2_PIN)) != 0) {
  // Clear the EXTI3 pending bit
  EXTI->PR1 |= (1 << SW2_PIN);

  // decrease counter
  decrease ();
  display ();
  }
}

int main(void){
configure_LED_pins();
configure_SW_pins();
configure_EXTI();
turn_off_LED1();
turn_off_LED2();
int i;
while(1){
}
}
