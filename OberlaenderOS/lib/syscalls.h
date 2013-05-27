/*
 * syscalls.h
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#ifndef SYSCALLS_H_
#define SYSCALLS_H_

#include <stdint.h>

#define SYSCALL_IPC_REGISTER 1
#define SYSCALL_IPC_UNREGISTER 2
#define SYSCALL_IPC_SEND 3
#define SYSCALL_IPC_RECEIVE 4
#define SYSCALL_IPC_WAIT 5

#pragma SWI_ALIAS(syscall, 1)
extern void syscall(uint32_t swiNumber, uint32_t arg1, uint32_t arg2);

#endif /* SYSCALLS_H_ */
