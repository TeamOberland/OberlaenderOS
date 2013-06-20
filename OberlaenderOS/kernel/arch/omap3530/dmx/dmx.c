/*
 * rs232.c
 *
 *  Created on: 19.06.2013
 *      Author: Manuel
 */


#include "dmx.h"
#include "../uart/uart.h"
#include <oos/uart.h>
#include "../../../genarch/uart/uart.h"
#include <oos/types.h>


void omap_dmx_load_configuration(uint8_t uartPort,uint8_t uart_mode, uart_protocol_format_t *configuration)
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
    //    memory_mapped_io_t fcr_reg = omap_uart_get_register(uartPort,UART_FCR_REG);
    //    SET_BIT(fcr_reg,UART_DMA_MODE);
    //    SET_BIT(fcr_reg,UART_ENABLE_FIFO);

        //6
        omap_uart_switch_to_config_mode_b(uartPort);


        //7
        //not for dmx
    //    memory_mapped_io_t tlr_reg = omap_uart_get_register(uartPort,UART_TLR_REG);
    //    SET_BIT(tlr_reg,4);
    //    SET_BIT(tlr_reg,0) ;



    //    *(tlr_reg)=0;
    //    SET_BIT(fcr_reg,7);
    //    SET_BIT(fcr_reg,6);
    //    SET_BIT(fcr_reg,);

        //8
        memory_mapped_io_t scr_reg = omap_uart_get_register(uartPort,UART_SCR_REG);
        SET_BIT(scr_reg,7);//Enables the granularity of 1 for TRIGGER RX level
        SET_BIT(scr_reg,6);//Enables the granularity of 1 for trigger TX level

        //not for dmx
        //SET_BIT(scr_reg,2);//DMA mode 1 (UARTi_DMA_TX, UARTi_DMA_RX)

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
        //SET_BIT(efr_reg,UART_ENHANCED_EN);

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
        //SET_BIT(efr_reg,1);

        //10
        omap_uart_switch_to_config_mode_b(uartPort);

        //11
        *(efr_reg) |= saved_efr_reg;

        //12
        //operational mode
        CLEAR_BIT(lcr_reg,7);

        /*flow control*/
            registerToSet =omap_uart_get_register(uartPort,UART_EFR_REG);
            /*clear flow control config*/
                *(registerToSet) &= ~0x0F;
                *(registerToSet) = configuration->flowControl;


                /* clear LCR DIV and BREAK field */
                CLEAR_BIT(omap_uart_get_register(uartPort, UART_LCR_REG), UART_LCR_DIV_EN);
                CLEAR_BIT(omap_uart_get_register(uartPort, UART_LCR_REG), UART_LCR_BREAK_EN);


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

bool_t __dmx_init(uint8_t uartPort,uint8_t uartMode, uart_protocol_format_t* config)
{
    omap_uart_software_reset(uartPort);
    omap_dmx_load_configuration(uartPort,uartMode,config);

    return 0;
}
