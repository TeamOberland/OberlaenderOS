/*
 * parser_intel.h
 *
 *  Created on: 12.06.2013
 *      Author: Daniel
 */

#ifndef PARSER_INTEL_H_
#define PARSER_INTEL_H_

#include "parser.h"

#define INTEL_RECORD_TYPE_DATA 0x00
#define INTEL_RECORD_TYPE_EOF 0x01
#define INTEL_RECORD_TYPE_EXT_LIN_ADDR 0x4

code_instruction_t* parser_intel_parse_string(const char* data);

#endif /* PARSER_INTEL_H_ */
