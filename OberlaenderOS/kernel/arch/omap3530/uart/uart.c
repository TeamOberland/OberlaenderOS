/*
 * uart.c
 *
 *  Created on: 29.05.2013
 *      Author: Manuel
 */

#include "uart.h"
#include <oos/uart.h>
#include "../../../genarch/uart/uart.h"


void omap_uart_load_configuration(uint8_t uartPort,uint8_t uart_mode, uart_protocol_format_t *configuration)
{
    uint32_t saved_lcr_reg,saved_efr_reg,saved_tcr_reg,saved_tlr_reg,saved_tcr_TLR;
        //17.5.1.1.1 UART Software Reset Site: 2734

        //1
        saved_lcr_reg= omap_uart_switch_to_config_mode_b(uartPort);

        //2
        memory_mapped_io_t efr_reg = omap_uart_get_register(uartPort,UART_EFR_REG);
        saved_efr_reg = READ_BIT(efr_reg,4);
        SET_BIT(efr_reg,UART_ENHANCED_EN);

        //3
        omap_uart_switch_to_config_mode_a(uartPort);

        //4
        memory_mapped_io_t mcr_reg = omap_uart_get_register(uartPort,UART_MCR_REG);
        saved_tcr_TLR = READ_BIT(mcr_reg,6);
        SET_BIT(mcr_reg,UART_TCR_TLR);

        //5
        //not for dmx
        memory_mapped_io_t fcr_reg = omap_uart_get_register(uartPort,UART_FCR_REG);
        SET_BIT(fcr_reg,UART_DMA_MODE);
        CLEAR_BIT(fcr_reg,UART_ENABLE_FIFO);

        //6
        omap_uart_switch_to_config_mode_b(uartPort);


//        //7
//        //not for dmx
        memory_mapped_io_t tlr_reg = omap_uart_get_register(uartPort,UART_TLR_REG);
        SET_BIT(tlr_reg,4);
        SET_BIT(tlr_reg,0) ;
//        //fifo queue size
//        *(tlr_reg)=0;
//        CLEAR_BIT(fcr_reg,7);
//        CLEAR_BIT(fcr_reg,6);

        //testing old commit
           // memory_mapped_io_t tlr_reg = omap_uart_get_register(uartPort,UART_TLR_REG);
            *(tlr_reg)=0;
            SET_BIT(fcr_reg,7);
            SET_BIT(fcr_reg,6);
         //testing old commit

        //8
        memory_mapped_io_t scr_reg = omap_uart_get_register(uartPort,UART_SCR_REG);
        SET_BIT(scr_reg,7);//Enables the granularity of 1 for TRIGGER RX level
        SET_BIT(scr_reg,6);//Enables the granularity of 1 for trigger TX level
        SET_BIT(scr_reg,2);//DMA mode 1 (UARTi_DMA_TX, UARTi_DMA_RX)

        //9
        *(efr_reg)|=saved_efr_reg;//restore the ENHANCED_EN BIT


        //10
        omap_uart_switch_to_config_mode_a(uartPort);

        //11
        *(mcr_reg)|= (saved_tcr_TLR);

        //12
        memory_mapped_io_t lcr_reg = omap_uart_get_register(uartPort,UART_LCR_REG);
        *(lcr_reg)=saved_lcr_reg;


        //17.5.1.1.3 Protocol, Baud Rate, and Interrupt Settings SITE 2734

        //1
        omap_uart_disable(uartPort);

        //2
        omap_uart_switch_to_config_mode_b(uartPort);

        //3
        saved_efr_reg = READ_BIT(efr_reg,UART_ENHANCED_EN);
        //not for dmx
        SET_BIT(efr_reg,UART_ENHANCED_EN);

        //4
        *(lcr_reg)=0;

        //5
        memory_mapped_io_t ier_reg =omap_uart_get_register(uartPort,UART_IER_REG);
        *(ier_reg)=0;

        //6
        omap_uart_switch_to_config_mode_b(uartPort);

        //7
        /*baudrate*/    /*pdf 2746*/
        memory_mapped_io_t registerToSet =omap_uart_get_register(uartPort,UART_DLL_REG);
        /* only use the first 2 bytes the other bytes are saved in dlh register (we dont use this ;-) )*/
        *(registerToSet) = (configuration->baudrate & 0xFF);
        registerToSet =omap_uart_get_register(uartPort,UART_DLH_REG);
        *(registerToSet) = (configuration->baudrate >> 8) & 0x3F;

        //8
        *(lcr_reg)=0;

        //9 disable interrupts
        //not for dmx
        SET_BIT(efr_reg,1);

        //10
        omap_uart_switch_to_config_mode_b(uartPort);

        //11
        *(efr_reg) |= saved_efr_reg;

        //12
        //operational mode
        CLEAR_BIT(lcr_reg,UART_LCR_DIV_EN);

        /*flow control*/
            registerToSet =omap_uart_get_register(uartPort,UART_EFR_REG);
            /*clear flow control config*/
                *(registerToSet) &= ~0x0F;
                *(registerToSet) = configuration->flowControl;


                /* clear LCR DIV and BREAK field */
                CLEAR_BIT(lcr_reg, UART_LCR_DIV_EN);
                CLEAR_BIT(lcr_reg, UART_LCR_BREAK_EN);


                registerToSet = omap_uart_get_register(uartPort, UART_LCR_REG);
                /* clear the len bits in LCR register */
                *(registerToSet) &= ~0x03;
                /* set new len bits in LCR register */
                *(registerToSet) |= configuration->datalength;


                switch (configuration->stopbit) {
                   case UART_PROTOCOL_NB_STOP_1:
                     CLEAR_BIT(registerToSet, UART_LCR_NB_STOP);
                     break;
                   case UART_PROTOCOL_NB_STOP_2:
                       SET_BIT(registerToSet, UART_LCR_NB_STOP);
                       break;
                   default:
                     SET_BIT(registerToSet, UART_LCR_NB_STOP);
                     break;
                 }

                switch (configuration->parity) {
                  case UART_PROTOCOL_PARITY_NONE:
                      CLEAR_BIT(registerToSet, UART_LCR_PARITY_EN);
                      break;
                  default:
                    CLEAR_BIT(registerToSet, UART_LCR_PARITY_EN);
                    break;
                }

                //special dmx stuff
                //force parity bit to be 1
    //            SET_BIT(registerToSet, UART_LCR_PARITY_EN);
    //            SET_BIT(registerToSet, 5);
    //            CLEAR_BIT(registerToSet, 4);
                //


                //13
                omap_uart_set_mode(uartPort,uart_mode );
}

memory_mapped_io_t omap_uart_get_register(uint8_t uartPort, uint32_t offset)
{
    return (memory_mapped_io_t)(omap_uart_get_baseadress(uartPort) + offset);
}

void omap_uart_disable(uint8_t uartPort)
{
    omap_uart_set_mode(uartPort,UART_MDR1_MODE_SELECT_DISABLE);
}

void omap_uart_set_mode(uint8_t uartPort,uint32_t mode)
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

uint32_t omap_uart_switch_to_config_mode_b(uint8_t uartPort)
{
    memory_mapped_io_t configRegister =omap_uart_get_register(uartPort, UART_LCR_REG);
    uint32_t lcr_reg_value = *configRegister;
    /* set the value on register */
    *(configRegister) = UART_LCR_MODE_CONFIG_B;

    return lcr_reg_value;
}

uint32_t omap_uart_switch_to_config_mode_a(uint8_t uartPort)
{
    memory_mapped_io_t configRegister =omap_uart_get_register(uartPort, UART_LCR_REG);
    uint32_t lcr_lcr_value = *configRegister;
    /* set the value on register */
    *(configRegister) = UART_LCR_MODE_CONFIG_A;

    return lcr_lcr_value;
}


void omap_uart_software_reset(uint8_t uartPort)
{
    memory_mapped_io_t resetRegisterAdress =omap_uart_get_register(uartPort,UART_SYSC_REG);

    /* set the value on register */
    uint32_t value = *(resetRegisterAdress);
    *(resetRegisterAdress) = value|(1<<1);

    omap_uart_waitfor_resetdone(uartPort);
}

 void omap_uart_waitfor_resetdone(uint8_t uartPort)
{
    memory_mapped_io_t resetDoneRegisterAdress =omap_uart_get_register(uartPort,UART_SYSS_REG);

    /*wait until the reset bit is set*/
    while(*(resetDoneRegisterAdress)&(1<<0)!=1);
}

/**
 * Delivers the uart base adress for the given uart port
 * @param uartPort the uart port
 */
 uint32_t omap_uart_get_baseadress(uint8_t uartPort)
{
    switch(uartPort)
    {
        case 1: return UART1;
        case 2: return UART2;
        case 3: return UART3;
        default: return 0; /* will never happen because we validate gpio port before */
    }
}

/*
 * Returns 1 if uart read fifo queue is empty.
 * If the Queue has at least one character the result will be 1.
 */
bool_t __uart_is_empty_read_queue(uint8_t uartPort) {
  memory_mapped_io_t uart_base_addr =omap_uart_get_register(uartPort,UART_LSR_REG);
  uint32_t status = (uint32_t) READ_BIT(uart_base_addr,UART_LSR_RX_FIFO_E);
  return (status == 0);
}


bool_t __uart_is_valid_port(uint8_t uartPort) {
    return omap_uart_get_baseadress(uartPort)!=0;
}

bool_t __uart_init(uint8_t uartPort,uint8_t uartMode, uart_protocol_format_t* config)
{
    omap_uart_software_reset(uartPort);
    omap_uart_load_configuration(uartPort,uartMode,config);

    return 0;
}

bool_t __uart_disable(uint8_t uartPort)
{
    omap_uart_disable(uartPort);
    return 0;
}


/*
 * Returns 1 if uart transmission fifo queue is empty.
 * If the Queue has at least one character the result will be 1.
 */
bool_t __uart_is_empty_write_queue(uint8_t uartPort) {
    memory_mapped_io_t uart_base_addr =omap_uart_get_register(uartPort,UART_LSR_REG);
    uint32_t status = READ_BIT(uart_base_addr,  UART_LSR_TX_FIFO_E);
  return (status != 0);
}

/* writes one character to the UART device */
uint32_t __uart_write(uint8_t uartPort, uint8_t* buffer) {
    memory_mapped_io_t uart_base_addr =omap_uart_get_register(uartPort,UART_THR_REG);
  *(uart_base_addr) = *buffer;

  return 0;
}

/* reads one character from the UART device */
uint32_t __uart_read(uint8_t uartPort, uint8_t* buffer) {
    memory_mapped_io_t uart_base_addr =omap_uart_get_register(uartPort,UART_RHR_REG);
  *buffer = *uart_base_addr;
  return 0;
}

