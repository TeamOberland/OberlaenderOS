/*
 * expansion.c
 *
 *  Created on: 14.06.2013
 *      Author: Manuel
 */

#include "../../../generic/io/expansion.h"
#include <oos/types.h>


uint8_t __set_expansion_pin_mode(uint32_t pinNumber, uint8_t mode)
{
    if(mode>7)
        return -2;

    memory_mapped_io_t add;
    uint8_t reset_mask = 7;

    switch (pinNumber) {
        case 1:
            return -3;
        case 2:
            return -3;
        case 3:
            add = (memory_mapped_io_t)0x48002168;
            mode=mode<<16;
            reset_mask =reset_mask<<16;
            break;
        case 4:
            add =(memory_mapped_io_t) 0x48002174;
            break;
        case 5:
            add = (memory_mapped_io_t)0x48002168;
            break;
        case 6:
            add = (memory_mapped_io_t)0x48002178;
            break;
        case 7:
            add =(memory_mapped_io_t) 0x48002164;
            mode=mode<<16;
            reset_mask =reset_mask<<16;
            break;
        case 8:
            add =(memory_mapped_io_t) 0x48002170;
            mode=mode<<16;
            reset_mask =reset_mask<<16;
            break;
        case 9:
            add =(memory_mapped_io_t) 0x48002164;
            break;
        case 10:
            add =(memory_mapped_io_t) 0x48002174;
            mode=mode<<16;
            reset_mask =reset_mask<<16;
            break;
        case 11:
            add =(memory_mapped_io_t) 0x48002160;
            mode=mode<<16;
            reset_mask =reset_mask<<16;
            break;
        case 12:
            add =(memory_mapped_io_t) 0x48002190;
            break;
        case 13:
            add =(memory_mapped_io_t) 0x48002160;
            break;
        case 14:
            add =(memory_mapped_io_t) 0x48002198;
            break;
        case 15:
            add =(memory_mapped_io_t) 0x4800215C;
            mode=mode<<16;
            reset_mask =reset_mask<<16;
            break;
        case 16:
            add =(memory_mapped_io_t) 0x48002194;
            mode=mode<<16;
            reset_mask =reset_mask<<16;
            break;
        case 17:
            add =(memory_mapped_io_t) 0x4800215C;
            break;
        case 18:
            add =(memory_mapped_io_t) 0x48002190;
            break;
        case 19:
            add =(memory_mapped_io_t) 0x48002158;
            break;
        case 20:
            add = (memory_mapped_io_t)0x4800218C;
            break;
        case 21:
            add = (memory_mapped_io_t)0x48002158;
            break;
        case 22:
            add =(memory_mapped_io_t) 0x4800218C;
            mode=mode<<16;
            reset_mask =reset_mask<<16;
            break;
        case 23:
            add =(memory_mapped_io_t) 0x480021C0;
            mode=mode<<16;
            reset_mask =reset_mask<<16;
            break;
        case 24:
            add =(memory_mapped_io_t) 0x480021BC;
            break;
        case 25:
            return -3;
        case 26:
            return -3;
        case 27:
            return -3;
        case 28:
            return -3;
        default:
            return -3;
    }

    *(add) = ~reset_mask;
    *(add) |= mode;

    return 0;
}

