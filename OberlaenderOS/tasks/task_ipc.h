/*
 * task_ipc.h
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */

#ifndef TASK_IPC_H_
#define TASK_IPC_H_


#include "../kernel/generic/io/gpio.h"

#define TASK_IPC_NS "IPC_SRV"
#define GPIO_USERBUTTON 7

void task_ipc_server(void);
void task_ipc_client(void);

#endif /* TASK_IPC_H_ */
