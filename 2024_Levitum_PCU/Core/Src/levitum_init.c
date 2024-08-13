/*
 * levitum_init.c
 *
 *  Created on: Jun 30, 2024
 *      Author: lukaslindner
 */

#include "levitum_init.h"
#include "levitum_adc.h"

// External peripherals
extern TIM_HandleTypeDef htim16;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc4;

// Global variables
char uart_buf[50];
int uart_buf_len;
uint16_t timer_val;

// ADC Object array
#define ADC_OBJECT_COUNT 1
ADCObject *adc_objects[ADC_OBJECT_COUNT];

// ADC Object for specific use
ADCObject vsense_50V_1;

void levitum_init(){


	// Print to COM Port
	uart_buf_len = sprintf(uart_buf, "Hello Levitum\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t*)uart_buf, uart_buf_len, 100);

	// Initialize ADC objects
	init_adc_struct(&vsense_50V_1, &hadc4, 15, 2, 2.0, 1.0);
	adc_objects[0] = &vsense_50V_1; // Assign vsense_50V_1 to the array

	init_adc(adc_objects, ADC_OBJECT_COUNT);



	// Start timer
	HAL_TIM_Base_Start(&htim16);

}
