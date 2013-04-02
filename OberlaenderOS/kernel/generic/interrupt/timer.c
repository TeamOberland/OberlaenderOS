/*
 * timer.c
 *
 *  Created on: 02.04.2013
 *      Author: Daniel
 */


#include "timer.h"
#include "../../errno.h"
#include "../../genarch/interrupts/timer.h"

int gptimer_init(uint32_t timer, int ticks, int loadTicks)
{
    if(__gptimer_isvalid(timer))
    {
        return E_FAULT;
    }
    return __gptimer_init(timer, ticks, loadTicks);
}

int gptimer_start(uint32_t timer)
{
    if(__gptimer_isvalid(timer))
    {
        return E_FAULT;
    }
    return gptimer_start(timer);
}

int gptimer_stop(uint32_t timer)
{
    if(__gptimer_isvalid(timer))
    {
        return E_FAULT;
    }
    return gptimer_stop(timer);

}

int gptimer_reset(uint32_t timer)
{
    if(__gptimer_isvalid(timer))
    {
        return E_FAULT;
    }
    return gptimer_reset(timer);

}
