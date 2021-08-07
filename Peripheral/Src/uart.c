/*
 * uart.c
 *
 *  Created on: 29 lip 2021
 *      Author: kdaniele
 */

#include "uart.h"

/*
 * @brief UART2 GPIO Configuration
 */
void uart_UART2_GPIO_config(void)
{
  //PA2 TX PA3 RX
  //Enable GPIOA Clock
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  //Mode to af (UART1)
  GPIOA->MODER |= (2<<4); //PA2 to AF
  GPIOA->MODER |= (2<<6); //PA3 to AF
  //Output max 10 MHz
  GPIOA->OSPEEDR |= (3<<4) | (3<<6);
  //Map PA2, PA3 mapped to UART2
  GPIOA->AFR[0] |=  (7<<8);
  GPIOA->AFR[0] |=  (7<<12);
}

/*
 * @brief UART2 Peripheral Configuration
 */
void uart_UART2_config(void)
{
  //Enable UART1 Clock
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
  //Enable Transmit
  USART2->CR1 |= USART_CR1_TE;
  //Parity to Even
  USART2->CR1 &= ~(USART_CR1_PS);
  //Parity Control Disabled
  USART2->CR1 &= ~(USART_CR1_PCE);
  //Word length to 8-bits
  USART2->CR1 &= ~(USART_CR1_M1);
  //Stop bits to 1
  USART2->CR2 &= ~(USART_CR2_STOP);
  //Disable HW Flow Control
  USART2->CR3 &= ~(USART_CR3_CTSE);
  USART2->CR3 &= ~(USART_CR3_RTSE);
  //Set baud rate to 115200
  USART2->CR1 &= ~(USART_CR1_OVER8);
  USART2->BRR |= 0x138;
  //Clear some flag and enable
  USART2->CR2 &= ~(USART_CR2_LINEN |USART_CR2_CLKEN); //nie chcemy zegara bo jestesmy w modzie asynchronicznym
  USART2->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);
  //Enable UART
  USART2->CR1 |= USART_CR1_UE;
}

/*
 * @brief UART2 Transmit
 */

bool uart_UART2_trasmit(uint8_t *data, uint8_t len, uint32_t timeout){
  //Wait on TXE to start trasmit
  //Write to DR as TXE flag is HIGH (Tx buffer empty)
  uint8_t dataIdx  = 0;
  uint32_t startTick= rcc_msGetTicks();
  while(dataIdx<len)
  {
    if(USART2->ISR & USART_ISR_TXE)
    {
      USART2->TDR = data[dataIdx];
      dataIdx++;
    }
    else //Manage timeout
    {
      if((rcc_msGetTicks()-startTick)>=timeout) return false;
    }
  }
  //wait for busy flag
  while(USART2->ISR & USART_ISR_TC)
  {
    if((rcc_msGetTicks() - startTick)>= timeout) return false;
  }
  return true;
}


