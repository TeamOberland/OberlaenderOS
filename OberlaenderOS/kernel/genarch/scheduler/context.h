/*
 * context.h
 *
 *  Created on: 20.05.2013
 *      Author: Daniel
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include "../../generic/scheduler/process.h"

void __context_save();
void __context_load();
void __context_init(process_t* process);

#endif /* CONTEXT_H_ */
