/*
 * levitum_init.c
 *
 *  Created on: Jun 30, 2024
 *      Author: lukaslindner
 */

#include "levitum_init.h"

extern TIM_HandleTypeDef htim16;
extern UART_HandleTypeDef huart1;

char uart_buf[50];
int uart_buf_len;
uint16_t timer_val;


void levitum_init(){


	// Print to COM Port
	uart_buf_len = sprintf(uart_buf, "Hello Levitum\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t*)uart_buf, uart_buf_len, 100);

	// Start timer
	HAL_TIM_Base_Start(&htim16);

}
