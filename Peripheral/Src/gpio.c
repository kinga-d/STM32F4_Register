/*
 * gpio.c
 *
 *  Created on: Aug 4, 2021
 *      Author: kdaniele
 */

#include "gpio.h"

/**
 *  @brief LEDs GPIO Configuration, PA5
 */
void gpio_LED_config(void)
{
  //Enable Port A Clock
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  //Mode to output
  GPIOA->MODER |= (1<<10); //PA5 to output mode
  //Speed to max
  GPIOA->OSPEEDR |= (2<<11); //PA5 high speed


}

/**
 * @brief Write/Toggle function
 */
void gpio_LED_writeGreen(bool state)
{
  if(state)
  {
    GPIOA->ODR |= (1<<5);
  }
  else
  {
    GPIOA->ODR &= ~(1<<5);
  }
}
void gpio_LED_toggleGreen(void)
{
    GPIOA->ODR ^= (1<<5);
}


/**
 * @brief Button configuration (PC13)
 */
void gpio_PB_config(void)
{
  //Enable Clock Port C
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  //Input mode
  GPIOC->MODER &= ~(GPIO_MODER_MODER13);
}

/**
 * @brief Read push-button
 */
bool gpio_PB_read(void)
{
  return (bool)(GPIOC->IDR & GPIO_IDR_13);
}
