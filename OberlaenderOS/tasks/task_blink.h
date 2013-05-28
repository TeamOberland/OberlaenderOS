/*
 * task_blink.h
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */

#ifndef TASK_BLINK_H_
#define TASK_BLINK_H_

#include "../kernel/generic/io/gpio.h"

#define GPIO_USERLED0 149
#define GPIO_USERLED1 150
#define GPIO_MMC1_WP 23
#define GPIO_DVI 170
#define GPIO_USERBUTTON 7

void task_blink_led0(void);
void task_blink_led1(void);

#endif /* TASK_BLINK_H_ */
