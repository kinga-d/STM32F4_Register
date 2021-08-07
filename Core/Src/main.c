#include "main.h"
#include "uart.h"
#include <stdio.h>
#include "gpio.h"

int main(void)
{
  //max clock speed 72 MHz
  rcc_HSE_config();
  rcc_sysTick_config(72000); //dzieli 72 000 000 / 72 000 = 1000 sekund
  //UART Configuration
  uart_UART2_GPIO_config();
  uart_UART2_config();
  //LED Config
  gpio_LED_config();
  //Button configuration
  gpio_PB_config();

  printf("Program is starting...\n");
  while(1)
  {

   gpio_LED_writeGreen(gpio_PB_read());
   printf("Hello world\n");
   rcc_msDelay(1000);
  }
}
