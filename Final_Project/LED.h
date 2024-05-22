#ifndef __STM32L476G_LED_H
#define __STM32L476G_LED_H

#include "stm32l476xx.h"


// Modular function to initialize PA5 as an output pin, interfacing with the LD2 LED.
void configure1_LED_GREEN_pin();
void configure1_LED_YELLOW_pin();
void configure1_LED_RED_pin();
// Modular function to turn on the LD2 LED.
void turn1_on_LED_GREEN();
void turn1_on_LED_YELLOW();
void turn1_on_LED_RED();
// Modular function to turn off the LD2 LED.
void turn1_off_LED_GREEN();
void turn1_off_LED_YELLOW();
void turn1_off_LED_RED()
	;
// Modular function to toggle the LD2 LED.
void toggle1_LED_GREEN();
void toggle1_LED_YELLOW();
void toggle1_LED_RED();




#endif /* __STM32L476G_LED_H */