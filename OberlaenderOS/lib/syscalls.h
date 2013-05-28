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

#define SYSCALL_SCHEDULER_RUN 6

#define SYSCALL_GPIO_EXPORT 7

#define SYSCALL_DEVICE_OPEN 8
#define SYSCALL_DEVICE_CLOSE 9
#define SYSCALL_DEVICE_READ 10
#define SYSCALL_DEVICE_WRITE 11

#pragma SWI_ALIAS(syscall, 1)
extern void syscall(uint32_t swiNumber, uint32_t arg1, uint32_t arg2, uint32_t arg3);

#endif /* SYSCALLS_H_ */
