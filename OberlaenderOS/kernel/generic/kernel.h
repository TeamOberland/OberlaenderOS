/*
 * kernel.h
 *
 *  Created on: 27.03.2013
 *      Author: Daniel
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include "../genarch/arch.h"

void setup_kernel();
void kernel_sleep(uint32_t ms);


inline void switch_to_user_mode()
{
    __switch_to_user_mode();
}


#endif /* KERNEL_H_ */
