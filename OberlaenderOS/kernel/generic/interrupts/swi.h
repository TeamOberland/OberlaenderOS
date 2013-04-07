/*
 * swi.h
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#ifndef SWI_H_
#define SWI_H_

#include "../../types.h"

/**
 * Handles any notified SWI
 */
#pragma INTERRUPT(swi_handle, SWI)
bool_t swi_handle(uint32_t swiNumber, uint32_t arg1, uint32_t arg2);

#endif /* SWI_H_ */
