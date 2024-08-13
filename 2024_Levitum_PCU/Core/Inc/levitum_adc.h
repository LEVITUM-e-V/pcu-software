/*
 * levitum_adc.h
 *
 *  Created on: Aug 13, 2024
 *      Author: lukaslindner
 */

#ifndef INC_LEVITUM_ADC_H_
#define INC_LEVITUM_ADC_H_


#include "main.h"

// Define ADC constants and structures
#define ADC_MAX_NBR 10 // Adjust this value as needed
#define ADC_DELAY 50000

// ADCObject structure definition (assuming it's defined elsewhere)
typedef struct {
    ADC_HandleTypeDef *handler;
    uint32_t channel;
    uint32_t sampletime;
    float gain;
    float offset;
    float compensated_value;
    float value_avg_1s;
    uint64_t last_updated;
} ADCObject;

// Function prototypes
void init_adc(ADCObject *_adc_ptrs[], uint8_t _adc_nbr);
void init_adc_struct(ADCObject *adc, ADC_HandleTypeDef *handler, uint32_t channel, uint32_t sampletime, float gain,
                     float offset);
void adc_driver(void);
uint8_t configure_adc_channel(ADCObject *adc_obj);
uint8_t get_adc_value(ADCObject *adc_obj, uint32_t *data);
void convert_adc_value_to_volt(uint32_t *adc_val, float *adc_value_in_volt);
uint8_t stop_adc(ADCObject *adc_obj);
uint8_t poll_adc_value(ADCObject *adc_obj, uint32_t *adc_value);
uint8_t poll_adc_volt(ADCObject *adc_obj, float *adc_value_in_volt);


#endif /* INC_LEVITUM_ADC_H_ */
