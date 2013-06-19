/*
 * loader.h
 *
 *  Created on: 12.06.2013
 *      Author: Daniel
 */

#ifndef LOADER_H_
#define LOADER_H_

#include "../scheduler/process.h"

void loader_load_intel_from_string(process_t* proc, const char* data);
void loader_load_elf_from_data(process_t* process, uint32_t length, uint8_t* data, uint32_t* entryPoint);
//void loader_load_intel_from_file(process_t* proc, const char* path);

#endif /* LOADER_H_ */
