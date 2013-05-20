/*
 * arch.h
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#ifndef ARCH_OMAP3530_H_
#define ARCH_OMAP3530_H_

#include "gpio/gpio.h"
#include "interrupts/interrupts.h"
#include "interrupts/timer.h"
#include "scheduler/context.h"

inline void __switch_to_user_mode()
{
    asm("\t CPS 0x10");
}

#endif /* ARCH_H_ */
