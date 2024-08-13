/*
 * levitum_main.c
 *
 *  Created on: Jun 30, 2024
 *      Author: lukaslindner
 */

#include "levitum_main.h"
#include "stm32u5xx_hal_conf.h"
#include "stm32u5xx_it.h"

extern char uart_buf[50];
extern int uart_buf_len;
extern uint16_t timer_val;
extern TIM_HandleTypeDef htim16;
extern UART_HandleTypeDef huart1;



void levitum_main(){
	timer_val = __HAL_TIM_GET_COUNTER(&htim16);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET); // toggles pin C7 on
	HAL_Delay(500); // waits 500 ms
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_Delay(500);

	uint16_t time_span = (__HAL_TIM_GET_COUNTER(&htim16) - timer_val)/10;
	uart_buf_len = sprintf(uart_buf, "%d ms\r\n", time_span);
	HAL_UART_Transmit(&huart1, (uint8_t*)uart_buf, uart_buf_len, 100);
}
