/*
 * levitum_main.c
 *
 *  Created on: Jun 30, 2024
 *      Author: lukaslindner
 */

#include "levitum_main.h"
#include "stm32u5xx_hal_conf.h"
#include "stm32u5xx_it.h"

void levitum_main(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET); // toggles pin C7 on
	HAL_Delay(500); // waits 500 ms
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_Delay(500);
}
