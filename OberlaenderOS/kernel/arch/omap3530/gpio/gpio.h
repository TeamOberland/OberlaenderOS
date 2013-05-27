/*
 * gpio.h
 *
 *  Created on: 27.03.2013
 *      Author: Daniel
 */

#ifndef GPIO_OMAP3530_H_
#define GPIO_OMAP3530_H_

#include "../../../../lib/types.h"

/*
 * GPIO Base adresses according to Technical Reference Manual (page 3400)
 */
#define GPIO_PORT_COUNT 6
#define GPIO_PIN_COUNT 32
#define GPIO1_BASE 0x48310000 /**< The base adress of the GPIO1 module */
#define GPIO2_BASE 0x49050000 /**< The base adress of the GPIO2 module */
#define GPIO3_BASE 0x49052000 /**< The base adress of the GPIO3 module */
#define GPIO4_BASE 0x49054000 /**< The base adress of the GPIO4 module */
#define GPIO5_BASE 0x49056000 /**< The base adress of the GPIO5 module */
#define GPIO6_BASE 0x49058000 /**< The base adress of the GPIO6 module */

/*
 * GPIO Register gpioPorts according to Technical Reference Manual (page 3400ff)
 */
#define GPIO_REVISION          0x0000 /**< This register contains the IP revision code. (32bit, R ) */
#define GPIO_SYSCONFIG         0x0010 /**< This register controls the various parameters of the L4 interconnect. (32bit, RW) */
#define GPIO_SYSSTATUS         0x0014 /**< This register provides status information about the module, excluding the interrupt status information. (32bit, R ) */
#define GPIO_IRQSTATUS1        0x0018 /**< This register provides IRQ 1 status information. (32bit, RW) */
#define GPIO_IRQENABLE1        0x001c /**< This register provides IRQ 1 enable information. (32bit, RW) */
#define GPIO_WAKEUPENABLE      0x0020 /**< This register provides wake-up enable information. (32bit, RW) */
#define GPIO_IRQSTATUS2        0x0028 /**< This register provides IRQ 2 status information. (32bit, RW) */
#define GPIO_IRQENABLE2        0x002c /**< This register provides IRQ 2 enable information. (32bit, RW) */
#define GPIO_CTRL              0x0030 /**< This register controls the clock gating functionality. (32bit, RW) */
#define GPIO_OE                0x0034 /**< This register is used to enable the pins output capabilities. Its only function is to carry the pads configuration.(32bit, RW) */
#define GPIO_DATAIN            0x0038 /**< This register is used to register the data that is read from the GPIO pins. (32bit, R ) */
#define GPIO_DATAOUT           0x003c /**< This register is used for setting the value of the GPIO output pins. (32bit, RW) */
#define GPIO_LEVELDETECT0      0x0040 /**< This register is used to enable/disable for each input lines the low-level (0) detection to be used for the interrupt request generation. (32bit, RW) */
#define GPIO_LEVELDETECT1      0x0044 /**< This register is used to enable/disable for each input lines the high-level (1) detection to be used for the interrupt request generation.(32bit, RW) */
#define GPIO_RISINGDETECT      0x0048 /**< This register is used to enable/disable for each input lines the rising-edge (transition 0=>1) detection to be used for the interrupt request and the wake-up generation. (32bit, RW) */
#define GPIO_FALLINGDETECT     0x004c /**< This register is used to enable/disable for each input lines the falling-edge (transition 1=>0) detection to be used for the interrupt request and the wake-up generation. (32bit, RW) */
#define GPIO_DEBOUNCENABLE     0x0050 /**< This register is used to enable/disable the debouncing feature for each input line. (32bit, RW) */
#define GPIO_DEBOUNCETIME      0x0054 /**< This register controls debouncing time (the value is global for all ports). (32bit, RW) */
#define GPIO_CLEARIRQENABLE1   0x0060 /**< Clear to 0 the corresponding bits in the GPIO_IRQENABLE1 register (32bit, RW) */
#define GPIO_SETIRQENABLE1     0x0064 /**< Set to 1 the corresponding bits in the GPIO_IRQENABLE1 register (32bit, RW) */
#define GPIO_CLEARIRQENABLE2   0x0070 /**< Clear to 0 the corresponding bits in the GPIO_IRQENABLE2 register (32bit, RW) */
#define GPIO_SETIRQENABLE2     0x0074 /**< Set to 1 the corresponding bits in the GPIO_IRQENABLE2 register (32bit, RW) */
#define GPIO_CLEARWKUENA       0x0080 /**< Clear to 0 the corresponding bits in the GPIO_WAKEUPENABLE register (32bit, RW) */
#define GPIO_SETWKUENA         0x0084 /**< Set to 1 the corresponding bits in the GPIO_WAKEUPENABLE register (32bit, RW) */
#define GPIO_CLEARDATAOUT      0x0090 /**< Clear to 0 the corresponding bits in the GPIO_DATAOUT register (32bit, RW) */
#define GPIO_SETDATAOUT        0x0094 /**< Set to 1 the corresponding bits in the GPIO_DATAOUT register (32bit, RW) */


uint32_t omap_gpio_to_gpioPort(uint32_t gpio);

/**
 * Delivers the gpio base adress for the given gpio port
 * @param gpioPort the gpio port
 */
uint32_t omap_gpio_get_baseadress(uint32_t gpioPort);

inline memory_mapped_io_t omap_gpio_get_register(uint32_t gpioPort, uint32_t offset)
{
    return (memory_mapped_io_t)(omap_gpio_get_baseadress(gpioPort) + offset);
}


void omap_gpio_set_direction(uint32_t gpio, bool_t isInput);

bool_t omap_gpio_isinput(uint32_t gpioPort, uint32_t gpio);

#endif /* GPIO_H_ */
