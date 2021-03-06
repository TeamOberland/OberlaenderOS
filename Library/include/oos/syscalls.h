/*
 * syscalls.h
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#ifndef SYSCALLS_H_
#define SYSCALLS_H_

#include <oos/types.h>

#ifndef SYSCALL_DATA
#define SYSCALL_DATA
typedef struct syscall_data
{
    uint32_t swiNumber;
    uint32_t arg1;
    uint32_t arg2;
    uint32_t arg3;
    uint32_t arg4;
    uint32_t arg5;
} syscall_data_t;
#endif

#define SYSCALL_IPC_REGISTER 101
#define SYSCALL_IPC_UNREGISTER 102
#define SYSCALL_IPC_SEND 103
#define SYSCALL_IPC_RECEIVE 104
#define SYSCALL_IPC_WAIT 105

#define SYSCALL_SCHEDULER_RUN 201

#define SYSCALL_GPIO_EXPORT 301

#define SYSCALL_DEVICE_OPEN 401
#define SYSCALL_DEVICE_CLOSE 402
#define SYSCALL_DEVICE_READ 403
#define SYSCALL_DEVICE_WRITE 404
#define SYSCALL_DEVICE_IOCTL 405

#define SYSCALL_FILE_OPEN 501
#define SYSCALL_FILE_CLOSE 502
#define SYSCALL_FILE_FLUSH 503
#define SYSCALL_FILE_GETC 504
#define SYSCALL_FILE_GETS 505
#define SYSCALL_FILE_PUTC 506
#define SYSCALL_FILE_PUTS 507
#define SYSCALL_FILE_WRITE 508
#define SYSCALL_FILE_READ 509
#define SYSCALL_FILE_SEEK 510
#define SYSCALL_FILE_GETPOS 511
#define SYSCALL_FILE_TELL 512
#define SYSCALL_FILE_EOF 513
#define SYSCALL_FILE_REMOVE 514
#define SYSCALL_FILE_OPENDIR 515
#define SYSCALL_FILE_READDIR 516
#define SYSCALL_FILE_CLOSEDIR 517
#define SYSCALL_FILE_CREATEDIR 518
#define SYSCALL_FILE_ISDIR 519

#define SYSCALL_STDIO_PRINTF 601
#define SYSCALL_STDIO_PRINT_TEST 602


#pragma SWI_ALIAS(syscall, 1)
extern void syscall(syscall_data_t* data);



#endif /* SYSCALLS_H_ */
