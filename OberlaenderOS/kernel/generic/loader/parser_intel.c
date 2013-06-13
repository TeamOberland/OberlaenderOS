/*
 * parser_intel.c
 *
 *  Created on: 12.06.2013
 *      Author: Daniel
 */

#include "parser_intel.h"
#include "../../../lib/types.h"
#include <string.h>
#include <stdlib.h>

static uint32_t parse_hex(const char* data, uint32_t* index, uint32_t size)
{
    uint32_t i, digit;
    uint32_t result = 0;

    for(i = 0; i < size; i++)
    {
        switch(data[*index])
        {
            case '0':  digit = 0; break;
            case '1':  digit = 1; break;
            case '2':  digit = 2; break;
            case '3':  digit = 3; break;
            case '4':  digit = 4; break;
            case '5':  digit = 5; break;
            case '6':  digit = 6; break;
            case '7':  digit = 7; break;
            case '8':  digit = 8; break;
            case '9':  digit = 9; break;
            case 'A': case 'a':  digit = 10; break;
            case 'B': case 'b':  digit = 11; break;
            case 'C': case 'c':  digit = 12; break;
            case 'D': case 'd':  digit = 13; break;
            case 'E': case 'e':  digit = 14; break;
            case 'F': case 'f':  digit = 15; break;
            default: digit = 0; break;
        }

        result += (digit << ((size - 1) * 4));
        *index += 1;
    }

    return result;
}

code_instruction_t* parser_intel_parse_string(const char* data)
{
    uint32_t index, length, i;
    index = 0;
    length = strlen(data);

    code_instruction_t* root = NULL;
    code_instruction_t* current = NULL;
    code_instruction_t* newinstruction = NULL;
    uint8_t recordType;
    uint32_t addressOffset = 0;

    while (index < length)
    {
        // ignore whitespaces
        if (data[index] == ' ' || data[index] == '\t' || data[index] == '\n' || data[index] == '\r')
        {
            index++;
        }
        else if (data[index] == ':')
        {
            newinstruction = malloc(sizeof(code_instruction_t));
            index++;

            newinstruction->byteCount = parse_hex(data, &index, 2);
            newinstruction->virtualAddress = parse_hex(data, &index, 4) + addressOffset;

            recordType = parse_hex(data, &index, 2);
            if (recordType == INTEL_RECORD_TYPE_DATA)
            {
                newinstruction->bytes = malloc(newinstruction->byteCount);
                for (i = 0; i < newinstruction->byteCount; i++)
                {
                    newinstruction->bytes[i] = parse_hex(data, &index, 2);
                }

                if (root == NULL)
                {
                    root = newinstruction;
                    current = root;
                }
                else
                {
                    current->next = newinstruction;
                    current = current->next;
                }
            }
            else if (recordType == INTEL_RECORD_TYPE_EOF)
            {
                free(newinstruction);
                break;
            }
            else if (recordType == INTEL_RECORD_TYPE_EXT_LIN_ADDR)
            {
                addressOffset = parse_hex(data, &index, 2) << 16;
                free(newinstruction);
            }
            else
            {
                printf("Unsupported record type! found 0x%x at position %i\n", recordType, index);
                free(newinstruction);
                break;
            }
        }
        else
        {
            printf("Invalid Intel Hex format! found 0x%x at position %i\n", data[index], index);
            break;
        }

    }
    return NULL;
}
