/*
 * levitum_init.h
 *
 *  Created on: Jun 30, 2024
 *      Author: lukaslindner
 */

#ifndef INC_LEVITUM_INIT_H_
#define INC_LEVITUM_INIT_H_

#include "main.h"
#include <stdio.h>



extern char uart_buf[50];
extern int uart_buf_len;
extern uint16_t timer_val;

void levitum_init();



#endif /* INC_LEVITUM_INIT_H_ */
