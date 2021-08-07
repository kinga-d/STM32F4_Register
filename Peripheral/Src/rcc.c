/*
 * rcc.c
 *
 *  Created on: Jun 29, 2021
 *      Author: kdaniele
 */

#include "rcc.h"

//ms Tick
static __IO uint32_t msTicks = 0; //dzięki temu static program nie doda do tego żadnej optymalizacji


/*
 * @brief HSE Configuration
 */
void rcc_HSE_config(void)
{
  /*
   *Configuration parameters -> STM32F303RE Clock Tree
   *
   *HSE = 8 Mhz
   *PLL_M = 9
   *AHB Prescaler = 1
   *USB Prescaler = 1
   *Cortex Prescaler = 1
   *  ===> 72 MHz system clock
   *
   *APB1 Prescaler = 2 => 36,72
   *APB2 Prescaler = 1 => 72, 72
   *ADC Prescaler = 1???
   */

  //PLL Configuration
  //PLL_M = 9
  RCC->CFGR |= RCC_CFGR_PLLMUL9;

  /*HSI Oscillator*/
  //Enable HSI Oscillator
  RCC->CR |= RCC_CR_HSION;
  //Wait for it to stabilize
  while(!(RCC->CR & RCC_CR_HSIRDY));

  //Set the power enable clock
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;

  //Configure the FLASH PREFETCH and the LATENCY Related Settings

  FLASH->ACR |= FLASH_ACR_PRFTBE;
  FLASH->ACR |= (1<<2);

  //Peripherals clock setup
  //AHB Prescaler
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
  //APB1 Prescaler
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
  //APB2 Prescaler
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

  //Select PLL Source
  RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_PREDIV;
  //Enable PLL and wait for it to stabilaze
  RCC->CR |= RCC_CR_PLLON;
   while(!(RCC->CR & RCC_CR_PLLRDY));


  //select PLL and main system clock and wait for it to be set
   RCC->CFGR |= RCC_CFGR_SW_PLL;
   while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);


}

/*
 * @brief SysTick Configuration
 */
void rcc_sysTick_config(uint32_t arr)
{
  //Reset Control Register
  SysTick->CTRL = 0;
  //Set the reload value
  SysTick->LOAD = arr-1;
  //Priority SysTick Interrupt (NVIC)
  NVIC_SetPriority(SysTick_IRQn,0);
  //Reset SysTick Value to 0
  SysTick->VAL = 0;
  //Enable Systick from Control register
  SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

/*
 * @brief Increment ms Ticks
 */
void rcc_msIncTicks(void)
{
  msTicks++;
}

/*
 * @brief Get ms Ticks
 */
uint32_t rcc_msGetTicks(void){
  return msTicks;
}

/*
 * @brief ms Delay
 */
void rcc_msDelay(uint32_t ms)
{
  uint32_t startTicks = rcc_msGetTicks();
  while( (rcc_msGetTicks() - startTicks) < ms);
}

/*
 * @brief Systick Interrupt Callback
 */
void SysTick_Handler(void)
{
  NVIC_ClearPendingIRQ(SysTick_IRQn);
  rcc_msIncTicks();
}
