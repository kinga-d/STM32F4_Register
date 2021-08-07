/*
 * gpio.h
 *
 *  Created on: Aug 4, 2021
 *      Author: kdaniele
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

/**
 *  @brief LEDs GPIO Configuration, PA5
 */
void gpio_LED_config(void);

/**
 * @brief Write/Toggle function
 */
void gpio_LED_writeGreen(bool state);
void gpio_LED_toggleGreen(void);

/**
 * @brief Button configuration (PC13)
 */
void gpio_PB_config(void);

/**
 * @brief Read push-button
 */
bool gpio_PB_read(void);

#endif /* INC_GPIO_H_ */
