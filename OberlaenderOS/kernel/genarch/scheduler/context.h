/*
 * context.h
 *
 *  Created on: 20.05.2013
 *      Author: Daniel
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include "../../generic/scheduler/process.h"

void __context_log(process_t* process);
void __context_save();
void __context_load();
void __context_init(process_t* process);
void __context_init_with_entrypoint(process_t* process, uint32_t address);

#endif /* CONTEXT_H_ */
