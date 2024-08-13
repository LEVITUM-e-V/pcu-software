/*
 * levitum_main.c
 *
 *  Created on: Jun 30, 2024
 *      Author: lukaslindner
 */

#include <stdio.h>
#include <inttypes.h>
#include "levitum_main.h"
#include "stm32u5xx_hal_conf.h"
#include "stm32u5xx_it.h"
#include "levitum_adc.h"

extern char uart_buf[50];
extern int uart_buf_len;
extern uint16_t timer_val;
extern TIM_HandleTypeDef htim16;
extern UART_HandleTypeDef huart1;

extern ADCObject vsense_50V_1;



void levitum_main(){
	// Blinking of LED1
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET); // toggles pin C7 on
	HAL_Delay(500); // waits 500 ms
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_Delay(500);


	// Time Measurement START for ADC Driver
	timer_val = __HAL_TIM_GET_COUNTER(&htim16);

	// Test Code ADC 50V 1
	adc_driver();
	uint32_t voltage_5V_1_mV = (uint32_t)(vsense_50V_1.compensated_value * 1000);

	uart_buf_len = sprintf(uart_buf, "%" PRIu32 " mV\r\n", voltage_5V_1_mV);
	HAL_UART_Transmit(&huart1, (uint8_t*)uart_buf, uart_buf_len, 100);


	// Time Measurement END for ADC Driver
	uint16_t time_span = (__HAL_TIM_GET_COUNTER(&htim16) - timer_val)/10;
	uart_buf_len = sprintf(uart_buf, "%d ms\r\n", time_span);
	HAL_UART_Transmit(&huart1, (uint8_t*)uart_buf, uart_buf_len, 100);
}
