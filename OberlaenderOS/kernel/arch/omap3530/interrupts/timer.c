/*
 * timer.c
 *
 *  Created on: 02.04.2013
 *      Author: Daniel
 */

#include "timer.h"
#include "../../../genarch/interrupts/timer.h"

static int gptimer_baseaddresses[GPTIMER_COUNT] = {
        GPTIMER1_BASE, GPTIMER2_BASE, GPTIMER3_BASE,
        GPTIMER4_BASE, GPTIMER5_BASE, GPTIMER6_BASE,
        GPTIMER7_BASE, GPTIMER8_BASE, GPTIMER9_BASE,
        GPTIMER10_BASE, GPTIMER11_BASE
};

inline uint32_t omap_gptimer_get_baseaddress(uint32 timer)
{
    return gptimer_baseaddresses[timer];
}

inline memory_mapped_io_t omap_gptimer_get_register(uint32_t timer, uint32_t offset)
{
    return (memory_mapped_io_t)(omap_gptimer_get_baseaddress(timer) + offset);
}

bool_t __gptimer_isvalid(uint32_t timer)
{
    return timer < 11;
}

#define TICK_PERIOD 1 /*< increase on each tick */
int __gptimer_init(uint32_t timer, int ticks, int loadTicks)
{
    __gptimer_stop(timer);

    /*
     * Set the registers according to 16.2.6.1 (2630)
     */

    switch(timer)
    {
        /*
         * Those are 1ms Tick Generation Timers, we need to calculate the correct
         * ticks
         */
        case 0: /* GPTIMER1 */
        case 1: /* GPTIMER2 */
        case 9: /* GPTIMER10 */
            /* 1 MS Tick with 32.768Hz Clock - (page 2625) */
            *(omap_gptimer_get_register(timer, GPTIMER_TLDR)) = 0xFFFFFFE0;
            *(omap_gptimer_get_register(timer, GPTIMER_TCRR)) = 0xFFFFFFE0;
            /* Positive increment and negative increment (page 2625)  */
            *(omap_gptimer_get_register(timer, GPTIMER_TPIR)) = ((((int)(CLOCK_FREQUENZE*TICK_PERIOD))+1)*1e6)-(CLOCK_FREQUENZE*TICK_PERIOD*1e6);
            *(omap_gptimer_get_register(timer, GPTIMER_TNIR)) = (((int)(CLOCK_FREQUENZE*TICK_PERIOD))*1e6)-(CLOCK_FREQUENZE*TICK_PERIOD*1e6);

            break;
        default:
            *(omap_gptimer_get_register(timer, GPTIMER_TLDR)) = loadTicks;
            *(omap_gptimer_get_register(timer, GPTIMER_TMAR)) = ticks;
            break;
    }

    /* clear all status bits */
    *(omap_gptimer_get_register(timer, GPTIMER_TISR)) = 0xFFFFFFFF;
    /* set overflow counter to zero */
    *(omap_gptimer_get_register(timer, GPTIMER_TOCR)) = 0;
    /* 10 overflows till interrupt */
    *(omap_gptimer_get_register(timer, GPTIMER_TOWR)) = 10;
    /* Enable Compare, Auto-Reload and trigger on overflow (0000 0000 0000 0000 0000 0110 0010 0001) */
    *(omap_gptimer_get_register(timer, GPTIMER_TCLR)) |= 0x0621;
    /* Disable prescale */
    *(omap_gptimer_get_register(timer, GPTIMER_TCLR)) &= ~(1 << 5);

    /* Set 32 KHz clock on this timer */
    *(PER_CM + CM_CLKSEL) &= ~(1 << CM_CLKSEL_GPT2);
}

int __gptimer_start(uint32_t timer)
{
    *(omap_gptimer_get_register(timer, GPTIMER_TIER)) = 0x01;  /* Enable Overflow Interrupts */
    *(omap_gptimer_get_register(timer, GPTIMER_TCLR)) |= 0x01; /* Start the Timer */
}

int __gptimer_stop(uint32_t timer)
{
    *(omap_gptimer_get_register(timer, GPTIMER_TIER)) &= 0x00;  /* Disable Interrupts */
    *(omap_gptimer_get_register(timer, GPTIMER_TCLR)) &= ~0x01; /* Stop the Timer */
    __gptimer_reset(timer);
}

int __gptimer_reset(uint32_t timer)
{
    *(omap_gptimer_get_register(timer, GPTIMER_TCRR)) = 0;
}
