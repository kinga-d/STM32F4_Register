/*
 * rcc.h
 *
 *  Created on: Jun 29, 2021
 *      Author: kdaniele
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "main.h"

/*
 * @brief HSE Configuration
 */
void rcc_HSE_config(void);

/*
 * @brief SysTick Configuration
 */
void rcc_sysTick_config(uint32_t arr);

/*
 * @brief Increment ms Ticks
 */
void rcc_msIncTicks(void);

/*
 * @brief Get ms Ticks
 */
uint32_t rcc_msGetTicks(void);

/*
 * @brief ms Delay
 */
void rcc_msDelay(uint32_t ms);


#endif /* INC_RCC_H_ */
