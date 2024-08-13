/*
 * levitum_adc.c
 *
 *  Created on: Aug 13, 2024
 *      Author: lukaslindner
 */

#include "levitum_adc.h"
//#include "global_counter.h"

#define ADC_DELAY 50000

ADCObject *adc_ptrs[ADC_MAX_NBR];
uint8_t adc_nbr;
uint64_t adc_last_updated_on;

void init_adc(ADCObject *_adc_ptrs[], uint8_t _adc_nbr) {
//    if (_adc_nbr > ADC_MAX_NBR) {
//        HardFault_Handler();
//    }

    for (uint8_t i = 0; i < _adc_nbr; i++) {
        adc_ptrs[i] = _adc_ptrs[i];
//        adc_ptrs[i]->last_updated = get_microsecond_counter();
        adc_ptrs[i]->last_updated = 0;
    }

    adc_nbr = _adc_nbr;
}

void init_adc_struct(ADCObject *adc, ADC_HandleTypeDef *handler, uint32_t channel, uint32_t sampletime, float gain,
                     float offset) {
    adc->handler = handler;
    adc->channel = channel;
    adc->sampletime = sampletime;
    adc->gain = gain;
    adc->offset = offset;
    adc->compensated_value = 0;
    adc->last_updated = 0;
}

void adc_driver() {
//    uint64_t current_time = get_microsecond_counter();
//    if (adc_last_updated_on + ADC_DELAY > current_time)
//        return;
//    adc_last_updated_on = current_time;

    for (uint8_t i = 0; i < adc_nbr; i++) {
        float value_volt = 0;
        poll_adc_volt(adc_ptrs[i], &value_volt);
        adc_ptrs[i]->compensated_value = value_volt * adc_ptrs[i]->gain + adc_ptrs[i]->offset;
//        adc_ptrs[i]->last_updated = get_microsecond_counter();

        adc_ptrs[i]->value_avg_1s =
            ((adc_ptrs[i]->value_avg_1s * ((1000000 / ADC_DELAY) - 1) + adc_ptrs[i]->compensated_value)) /
            (1000000 / ADC_DELAY);
    }
}

uint8_t configure_adc_channel(ADCObject *adc_obj) // TODO, do we need this?
{
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = adc_obj->channel;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = adc_obj->sampletime;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    sConfig.OffsetSignedSaturation = DISABLE;
    HAL_StatusTypeDef ret = HAL_ADC_ConfigChannel(adc_obj->handler, &sConfig);
    if (ret != HAL_OK) {
        return 1;
    }
    return 0;
}

uint8_t get_adc_value(ADCObject *adc_obj, uint32_t *data) {
    HAL_StatusTypeDef ret = HAL_ADC_Start(adc_obj->handler);
    if (ret != HAL_OK) {
        return 1;
    }
    ret = HAL_ADC_PollForConversion(adc_obj->handler, 1000);
    if (ret != HAL_OK) {
        return 1;
    }
    *data = HAL_ADC_GetValue(adc_obj->handler);
    return 0;
}

void convert_adc_value_to_volt(uint32_t *adc_val, float *adc_value_in_volt) {
    *adc_value_in_volt = ((float)*adc_val) * (3.3 / (65536.0 - 1));
}

uint8_t stop_adc(ADCObject *adc_obj) {
    HAL_StatusTypeDef ret = HAL_ADC_Stop(adc_obj->handler);
    if (ret != HAL_OK) {
        return 1;
    }
    return 0;
}

uint8_t poll_adc_value(ADCObject *adc_obj, uint32_t *adc_value) {
    uint8_t ret;
    ret = configure_adc_channel(adc_obj);
    if (ret != 0) {
        return 1;
    }
    ret = get_adc_value(adc_obj, adc_value);
    if (ret != 0) {
        return 1;
    }
    ret = stop_adc(adc_obj);
    if (ret != 0) {
        return 1;
    }
    return 0;
}

uint8_t poll_adc_volt(ADCObject *adc_obj, float *adc_value_in_volt) {
    uint32_t adc_value;
    uint8_t ret = poll_adc_value(adc_obj, &adc_value);
    if (ret != 0) {
        return 1;
    }
    convert_adc_value_to_volt(&adc_value, adc_value_in_volt);
    return 0;
}




