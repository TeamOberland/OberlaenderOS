/*
 * gpio.c
 *  omap3530 implementation for gpio
 *  Created on: 21.03.2013
 *      Author: Daniel
 */
#include "../../../types.h"
#include "../../../errno.h"
#include "../../../genarch/gpio/gpio.h"

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

/**
 * Maps a gpio pin to the according gpio port
 * @param gpio the gpio pin to map
 * @return the gpio port responsible for this pin
 */
static uint32_t omap_gpio_to_gpioPort(uint32_t gpio)
{
    /* gpio is in pin count, we need the port of this pin */
    return gpio / GPIO_PIN_COUNT;
}


/**
 * Delivers the gpio base adress for the given gpio port
 * @param gpioPort the gpio port
 */
static uint32_t omap_gpio_get_baseadress(uint32_t gpioPort)
{
    switch(gpioPort)
    {
        case 0: return GPIO1_BASE;
        case 1: return GPIO2_BASE;
        case 2: return GPIO3_BASE;
        case 3: return GPIO4_BASE;
        case 4: return GPIO5_BASE;
        case 5: return GPIO6_BASE;
        default: return 0; /* will never happen because we validate gpio port before */
    }
}

static inline memory_mapped_io_t omap_gpio_get_register(uint32_t gpioPort, uint32_t offset)
{
    return (memory_mapped_io_t)(omap_gpio_get_baseadress(gpioPort) + offset);
}

static void omap_gpio_set_direction(uint32_t gpio, bool_t isInput)
{
    /* get gpio port and calculate the pin on this port */
    uint32_t gpioPort = omap_gpio_to_gpioPort(gpio);
    uint32_t pinOfPort = gpio - (GPIO_PIN_COUNT * gpioPort);

    /* get adress for configuration */
    memory_mapped_io_t reg = omap_gpio_get_register(gpioPort, GPIO_OE);

    /* set the value on register */
    uint32_t value = *(reg);
    if(isInput)
        value |= (1 << pinOfPort);
    else
        value &= ~(1 << pinOfPort);
    *(reg) = value;
}

static bool_t omap_gpio_isinput(uint32_t gpioPort, uint32_t gpio)
{
    /* get adress for configuration */
    memory_mapped_io_t reg = omap_gpio_get_register(gpioPort, GPIO_OE);

    /* set the value on register */
    uint32_t value = *(reg);
    return ((value >> gpio) & 0x01) == 0x01;
}

bool_t __gpio_isvalid(uint32_t gpio)
{
    return gpio < (GPIO_PIN_COUNT * GPIO_PORT_COUNT);
}


int32_t __gpio_direction_input(uint32_t gpio)
{
    omap_gpio_set_direction(gpio, TRUE);
    return E_SUCCESS;
}

int32_t __gpio_direction_output(uint32_t gpio)
{
    omap_gpio_set_direction(gpio, FALSE);
    return E_SUCCESS;
}

/*
 * TODO: Check if port is input or output to get according register
 */

int32_t __gpio_get_value(uint32_t gpio)
{
    /* get gpio port and calculate the pin on this port */
    uint32_t gpioPort = omap_gpio_to_gpioPort(gpio);
    uint32_t pinOfPort = gpio - (GPIO_PIN_COUNT * gpioPort);
    uint32_t offset = omap_gpio_isinput(gpioPort, pinOfPort) ? GPIO_DATAIN : GPIO_DATAOUT;

    /* get adress for configuration */
    memory_mapped_io_t reg = omap_gpio_get_register(gpioPort, offset);

    uint32_t value = *(reg);

    return (value >> pinOfPort) & 0x01;
}

void __gpio_set_value(uint32_t gpio, uint32_t value)
{
    /* get gpio port and calculate the pin on this port */
    uint32_t gpioPort = omap_gpio_to_gpioPort(gpio);
    uint32_t pinOfPort = gpio - (GPIO_PIN_COUNT * gpioPort);
    if(omap_gpio_isinput(gpioPort, pinOfPort))
    {
        return;
    }
    /* get adress for configuration */
    memory_mapped_io_t reg = omap_gpio_get_register(gpioPort, GPIO_DATAOUT);

    uint32_t regValue = *(reg);
    if(value != 0)
        regValue |= (1 << pinOfPort);
    else
        regValue &= ~(1 << pinOfPort);
    *(reg) = regValue;
}
