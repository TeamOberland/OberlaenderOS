/*
 * syscalls.h
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#ifndef SYSCALLS_H_
#define SYSCALLS_H_

#include <stdint.h>

#define SYSCALL_GETTIME 1
#define SYSCALL_FORMATTIME 2

#pragma SWI_ALIAS(syscall, 1)
extern void syscall(uint32_t swiNumber, uint32_t arg1, uint32_t arg2);


#endif /* SYSCALLS_H_ */
