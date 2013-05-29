/*
 * uart.c
 *
 *  Created on: 29.05.2013
 *      Author: Manuel
 */


#include "uart.h"

#define SET_BIT(addr, offset) *addr |= (1 << offset);
#define CLEAR_BIT(addr, offset) *addr &= ~(1 << offset);
#define TOGGLE_BIT(addr, offset) *(addr) ^= (1 << offset);
#define READ_BIT(addr, offset) (*(addr) & (1 << offset));

inline memory_mapped_io_t omap_uart_get_register(uint8_t uartPort, uint32_t offset)
{
    return (memory_mapped_io_t)(omap_uart_get_baseadress(uartPort) + offset);
}

void omap_uart_disable(uint8_t uartPort)
{
    omap_uart_set_mode(uartPort,UART_MDR1_MODE_SELECT_DISABLE);
}

inline void omap_uart_set_mode(uint8_t uartPort,uint32_t mode)
{
    memory_mapped_io_t disableRegister =omap_uart_get_register(uartPort,UART_MDR1_REG);
    /* set the value on register */
    uint32_t value = *(disableRegister);
    /* clear first 3 bits -> MODE_SELECT OMAP35x 2762 */
    value &= ~7;
    /* set mode */
    value |= mode;
    *(disableRegister) &= value;
}

void omap_uart_switch_to_config_mode(uint8_t uartPort)
{
    memory_mapped_io_t configRegister =omap_uart_get_register(uartPort, UART_LCR_REG);
    /* set the value on register */
    *(configRegister) &= UART_LCR_MODE_CONFIG;
}

void omap_uart_load_configuration(uint8_t uartPort,uint8_t uart_mode, uart_protocol_format_t configuration)
{
    /*baudrate*/
    memory_mapped_io_t registerToSet =omap_uart_get_register(uartPort,UART_DLL_REG);
    /* only use the first 2 bytes the other bytes are saved in dlh register (we dont use this ;-) )*/
    *(registerToSet) = configuration.baudrate & 0xFF;

    /*baudrate*/
    /*pdf 2746*/
    registerToSet =omap_uart_get_register(uartPort,UART_EFR_REG);
        *(registerToSet) = configuration.baudrate   >> 8;/*todo read docu this value is just copied!*/

    /*flow control*/
        registerToSet =omap_uart_get_register(uartPort,UART_DLH_REG);
        /*clear flow control config*/
            *(registerToSet) &= ~0x0F;
            *(registerToSet) = configuration.flowControl;




            /* clear LCR DIV and BREAK field */
            CLEAR_BIT(omap_uart_get_register(uartPort, UART_LCR_REG), UART_LCR_DIV_EN);
            CLEAR_BIT(omap_uart_get_register(uartPort, UART_LCR_REG), UART_LCR_BREAK_EN);


            registerToSet = omap_uart_get_register(uartPort, UART_LCR_REG);
            /* clear the len bits in LCR register */
            *(registerToSet) &= ~(configuration.datalength);
            /* set new len bits in LCR register */
            *(registerToSet) |= configuration.datalength;


             switch (configuration.stopbit) {
              case UART_PROTOCOL_NB_STOP_1:
                CLEAR_BIT(registerToSet, UART_LCR_NB_STOP);
                break;
              case UART_PROTOCOL_NB_STOP_2:
              default:
                SET_BIT(registerToSet, UART_LCR_NB_STOP);
                break;
            }

            switch (configuration.parity) {
              case UART_PROTOCOL_PARITY_NONE:
              default:
                CLEAR_BIT(registerToSet, UART_LCR_PARITY_EN);
                break;
            }

            omap_uart_set_mode(uartPort,uart_mode );
}


void omap_uart_software_reset(uint8_t uartPort)
{
    memory_mapped_io_t resetRegisterAdress =omap_uart_get_register(omap_uart_get_baseadress(uartPort),UART_SYSC_REG);

    /* set the value on register */
    uint32_t value = *(resetRegisterAdress);
    *(resetRegisterAdress) = value|(1<<1);

    omap_uart_waitfor_resetdone(uartPort);
}

inline void omap_uart_waitfor_resetdone(uint8_t uartPort)
{
    return;
    memory_mapped_io_t resetDoneRegisterAdress =omap_uart_get_register(omap_uart_get_baseadress(uartPort),UART_SYSS_REG);

    /*wait until the reset bit is set*/
    while(*(resetDoneRegisterAdress)&(1<<0)==1);
}

/**
 * Delivers the uart base adress for the given uart port
 * @param uartPort the uart port
 */
inline uint32_t omap_uart_get_baseadress(uint8_t uartPort)
{
    switch(uartPort)
    {
        case 0: return UART1;
        case 1: return UART2;
        case 2: return UART3;
        default: return 0; /* will never happen because we validate gpio port before */
    }
}

void uart_terminal_init(uint8_t uartPort,uint8_t uartMode, uart_protocol_format_t config)
{
    omap_uart_software_reset(uartPort);

    omap_uart_switch_to_config_mode(uartPort);

    omap_uart_load_configuration(uartPort,uartMode,config);

}
