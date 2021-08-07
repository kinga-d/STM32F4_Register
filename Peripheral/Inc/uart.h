/*
 * uart.h
 *
 *  Created on: 29 lip 2021
 *      Author: kdaniele
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

/*
 * @brief UART2 GPIO Configuration
 */
void uart_UART2_GPIO_config(void);

/*
 * @brief UART2 Peripheral Configuration
 */
void uart_UART2_config(void);

/*
 * @brief UART2 Transmit
 */
bool uart_UART2_trasmit(uint8_t *data, uint8_t len, uint32_t timeout);

#endif /* INC_UART_H_ */
