/*
 * gpio.c
 *  omap3530 implementation for gpio
 *  Created on: 21.03.2013
 *      Author: Daniel
 */
#include <oos/types.h>

#include "../../../errno.h"
#include "../../../genarch/gpio/gpio.h"
#include "../../../arch/omap3530/gpio/gpio.h"


/**
 * Maps a gpio pin to the according gpio port
 * @param gpio the gpio pin to map
 * @return the gpio port responsible for this pin
 */
uint32_t omap_gpio_to_gpioPort(uint32_t gpio)
{
    /* gpio is in pin count, we need the port of this pin */
    return gpio / GPIO_PIN_COUNT;
}


/**
 * Delivers the gpio base adress for the given gpio port
 * @param gpioPort the gpio port
 */
uint32_t omap_gpio_get_baseadress(uint32_t gpioPort)
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

void omap_gpio_set_direction(uint32_t gpio, bool_t isInput)
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

bool_t omap_gpio_isinput(uint32_t gpioPort, uint32_t gpio)
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

int32_t __gpio_get_value(int32_t gpio)
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

void __gpio_set_value(uint32_t gpio, int32_t value)
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
