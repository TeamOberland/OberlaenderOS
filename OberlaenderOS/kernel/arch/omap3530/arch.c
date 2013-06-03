/*
 * arch.c
 *
 *  Created on: 27.03.2013
 *      Author: Daniel
 */

#include "../../genarch/arch.h"

#include "interrupts/timer.h"
#include "../../../lib/types.h"
#include "../../genarch/uart/uart.h"

void setup_arch()
{
    memory_mapped_io_t reg;
    /* Enable Functional Clock of GPIO1 */
    reg = (memory_mapped_io_t)(WKUP_CM + CM_FCLKEN);
    *(reg) = (*(reg)) | (0x01 << 3);

    /* Enable Interface Clock */
    reg = (memory_mapped_io_t)(WKUP_CM + CM_ICLKEN);
    *(reg) = (*(reg)) | (0x01 << 3);





    /* set mode to 4 (GPIO) see p. ~787 of omap35x.pdf */
    uint32_t* CONTROL_PADCONF_UART2_CTS = (uint32_t*)0x48002174; /* GPIO144 15:0 GPIO145 16:31 */
    uint32_t* CONTROL_PADCONF_UART2_TX = (uint32_t*)0x48002178; /* GPIO146 15:0 */

    /* 2 ports are on the same register they sharing the 32 bit enable gpio*/
    *(CONTROL_PADCONF_UART2_CTS) = (4 << 16) | 4;
    /* clear the first 3 bits */
    *(CONTROL_PADCONF_UART2_TX) &= ~7;
    /* enable gpio */
    *(CONTROL_PADCONF_UART2_TX) |= 4;

    /* turn off rgb led on dmx interface
     *  GPIO 144, 146, 145 --> GPIO 5 */
    uint32_t*  GPIO5_OE = (uint32_t*)0x49056034;
    uint32_t* GPIO5_DATAOUT = (uint32_t*)0x4905603C;
    uint32_t rgb = (1 << (144 % 32)) | (1 << (146 % 32)) | (1 << (145 % 32));
    *(GPIO5_OE) &= ~rgb;
    *(GPIO5_DATAOUT) &= ~rgb;
}


