#include "button.h"
#include "Systick_timer.h"
#include "LED.h"
#include "ADC.h"

#define SW1_PIN   2

extern uint8_t adcConversionComplete;
extern int counter;
//volatile uint32_t adc_result;
void delay1(uint32_t delay1) {
    // Implement a simple software delay function
    volatile uint32_t j;
    for (j = 0; j < delay1; ++j) {
        // Do nothing
    }
}
void configure_Button_pin(){
    // 1. Enable the clock to GPIO Port A	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;   
		
	// 2. Configure GPIO Mode to 'Input': Input(00), Output(01), AlterFunc(10), Analog(11)
	GPIOC->MODER &= ~(3UL<<(2*SW1_PIN));  	// Input (00)
	
	// 3. Configure GPIO Push-Pull to 'No Pull-up or Pull-down': No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOC->PUPDR  &= ~(3<<(2*SW1_PIN));  // No pull-up, no pull-down
	
}

void config_EXTI(){

	//----
	NVIC_EnableIRQ(EXTI2_IRQn);

	//----

RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	//----
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2;
	SYSCFG->EXTICR[0] |=  SYSCFG_EXTICR1_EXTI2_PC;
	//----
	
	
	// 3. Enable (unmask) the EXTI13 interrupt by setting its corresponding bit in the EXTI's IMR.
	EXTI->IMR1 |= (1<<13);     //Interrupt Mask Register (IMR): 0 = marked, 1 = not masked (i.e., enabled)
	
	//4. Enable interrupt trigger for both rising (button release) and falling (button press) edges.
	EXTI->RTSR1 |= (1<<13);  //Rising trigger selection register (RTSR):0 = disabled, 1 = enabled
	EXTI->FTSR1 &= ~(1<<13);  //Falling trigger selection register (FTSR): 0 = disabled, 1 = enabled
	
	
	//----
	EXTI->IMR1  |= (1 << SW1_PIN);
	EXTI->RTSR1 |= (1 << SW1_PIN);
	
}


int button(){
	

	if((GPIOC->IDR & GPIO_IDR_ID13) == GPIO_IDR_ID13){
		return 1;
	}
	return 0;
}




//----
void EXTI2_IRQHandler(void){

	if((EXTI->PR1 & (1 << SW1_PIN)) !=0){
	  	EXTI->PR1 |= (1 << SW1_PIN);

		turn1_off_LED_GREEN();
		turn1_off_LED_RED();
		turn1_on_LED_YELLOW();
		

	}
	delay1(500000);
	turn1_on_LED_GREEN();
	turn1_off_LED_RED();
	turn1_off_LED_YELLOW();
	ADC1_2_IRQHandler();
	delay1(adc_result);

}



