/*
 * parser.h
 *
 *  Created on: 12.06.2013
 *      Author: Daniel
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <oos/types.h>

typedef struct _code_instruction {
    uint32_t virtualAddress;
    uint32_t byteCount;
    uint8_t* bytes;
    struct _code_instruction* next;
} code_instruction_t;


#endif /* PARSER_H_ */
