/*
 * timer.c
 *
 *  Created on: 02.04.2013
 *      Author: Daniel
 */

#include "timer.h"
#include "../../../errno.h"
#include "../../../genarch/interrupts/timer.h"

static int gptimer_baseaddresses[GPTIMER_COUNT] = {
        GPTIMER1_BASE, GPTIMER2_BASE, GPTIMER3_BASE,
        GPTIMER4_BASE, GPTIMER5_BASE, GPTIMER6_BASE,
        GPTIMER7_BASE, GPTIMER8_BASE, GPTIMER9_BASE,
        GPTIMER10_BASE, GPTIMER11_BASE
};

inline uint32_t omap_gptimer_get_baseaddress(uint32_t timer)
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


#define MS_TICK_PERIOD 1
int __gptimer_init(uint32_t timer, int ticks)
{
    /* TRM p.2625 */
    int posInc = ((((int)(GPTIMER_FREQUENCY*MS_TICK_PERIOD))+1)*1e6)-(GPTIMER_FREQUENCY*MS_TICK_PERIOD*1e6);
    int negInc = (( (int)(GPTIMER_FREQUENCY*MS_TICK_PERIOD))   *1e6)-(GPTIMER_FREQUENCY*MS_TICK_PERIOD*1e6);

    __gptimer_stop(timer);
    __gptimer_clear(timer);

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
            /* Set increment registers to use (1ms increment) */
            *(omap_gptimer_get_register(timer, GPTIMER_TPIR)) = posInc;
            *(omap_gptimer_get_register(timer, GPTIMER_TNIR)) = negInc;

            /* Recommended Initialization for 1ms timer */
            *(omap_gptimer_get_register(timer, GPTIMER_TLDR)) = 0xFFFFFFE0;
            *(omap_gptimer_get_register(timer, GPTIMER_TTGR)) = 0x01;

            *(omap_gptimer_get_register(timer, GPTIMER_TOCR)) = 0;
            *(omap_gptimer_get_register(timer, GPTIMER_TOWR)) = ticks;
            *((memory_mapped_io_t)(PER_CM + CM_CLKSEL)) &= ~(1 << (timer-1));
            break;
        default:
            /* we are using overflow mode so we start at overflow - ticks to reach the overflow after ticks */
            *(omap_gptimer_get_register(timer, GPTIMER_TLDR)) = 0xFFFFFFFF - ticks;
            *(omap_gptimer_get_register(timer, GPTIMER_TTGR)) = 0x01;
            break;
    }

    /* Enable Compare, Auto-Reload and trigger on overflow  */
    *(omap_gptimer_get_register(timer, GPTIMER_TCLR)) |= (1 << 11) | (1 << 10) | (1 << 6) | (1 << 1);

    /* Enable Interrupts */
    *(omap_gptimer_get_register(timer, GPTIMER_TIER)) = (1 << 1);

    return E_SUCCESS;
}

int __gptimer_start(uint32_t timer)
{
    *(omap_gptimer_get_register(timer, GPTIMER_TCLR)) |= 0x01; /* Start the Timer */
    return E_SUCCESS;
}

int __gptimer_stop(uint32_t timer)
{
    *(omap_gptimer_get_register(timer, GPTIMER_TIER)) &= 0x00;  /* Disable Interrupts */
    *(omap_gptimer_get_register(timer, GPTIMER_TCLR)) &= ~0x01; /* Stop the Timer */
    __gptimer_reset(timer);
    return E_SUCCESS;
}

int __gptimer_reset(uint32_t timer)
{
    /* reset counter */
    *(omap_gptimer_get_register(timer, GPTIMER_TCRR)) = 0;
    return E_SUCCESS;
}


int __gptimer_clear(uint32_t timer)
{
    /* Clear all timer interrupts */
    *(omap_gptimer_get_register(timer, GPTIMER_TISR)) = ~0;

    return E_SUCCESS;
}

int __gptimer_getcounter(uint32_t timer)
{
    return *(omap_gptimer_get_register(timer, GPTIMER_TCRR));
}
