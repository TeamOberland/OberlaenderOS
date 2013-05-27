/*
 * context.h
 *
 *  Created on: 20.05.2013
 *      Author: Daniel
 */

#ifndef CONTEXT_OMAP3530_H_
#define CONTEXT_OMAP3530_H_

#define PROCESS_STACK_SIZE 128000
#define PROCESS_CONTEXT_SIZE 17
#define DECLARE_PROCESS_CONTEXT(name) void* name[PROCESS_CONTEXT_SIZE];

#endif /* CONTEXT_OMAP3530_H_ */
