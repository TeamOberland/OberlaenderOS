/*
 * timer.c
 *
 *  Created on: 02.04.2013
 *      Author: Daniel
 */


#include "timer.h"
#include "irq.h"
#include "../../errno.h"
#include "../../genarch/interrupts/timer.h"

static timer_t registered_timers[TIMER_COUNT];
static int registered_timer_count = 0;


static void timer_irq_handler()
{
    int i;
    gptimer_clear(GPTIMER_TIMER);

    for(i = 0; i < registered_timer_count; i++)
    {
        registered_timers[i].currentTicks += TIMER_TICKS;
        if(registered_timers[i].listener != NULL && registered_timers[i].currentTicks >= registered_timers[i].targetTicks)
        {
            registered_timers[i].listener();
            registered_timers[i].currentTicks = 0;
        }
    }
}

void timer_init()
{
    int i;
    for(i = 0; i < TIMER_COUNT; i++)
    {
        registered_timers[i].currentTicks = -1;
        registered_timers[i].targetTicks = -1;
        registered_timers[i].listener = NULL;
    }

    // we'll use the GPTimer2 for our timer system
    irq_add_listener(GPTIMER2_IRQ, timer_irq_handler);
    gptimer_init(GPTIMER_TIMER, TIMER_TICKS, 0);
    gptimer_start(GPTIMER_TIMER);
}

void timer_add_listener(irq_listener listener, uint32_t ticks)
{
    int i;
    if(registered_timer_count >= TIMER_COUNT) return;

    for(i = 0; i < TIMER_COUNT; i++)
    {
        if(registered_timers[i].listener == NULL)
        {
            registered_timers[i].listener = listener;
            registered_timers[i].currentTicks = ticks;
            registered_timers[i].targetTicks = ticks;
            registered_timer_count++;
            return;
        }
    }
}

void timer_remove_listener(irq_listener listener)
{
    int i;
    for(i = 0; i < TIMER_COUNT; i++)
    {
        if(registered_timers[i].listener == listener)
        {
            registered_timers[i].listener = NULL;
            registered_timers[i].currentTicks = -1;
            registered_timers[i].targetTicks = -1;
            registered_timer_count--;
        }
    }
}

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
    return __gptimer_start(timer);
}

int gptimer_stop(uint32_t timer)
{
    if(__gptimer_isvalid(timer))
    {
        return E_FAULT;
    }
    return __gptimer_stop(timer);

}

int gptimer_reset(uint32_t timer)
{
    if(__gptimer_isvalid(timer))
    {
        return E_FAULT;
    }
    return __gptimer_reset(timer);
}


int gptimer_clear(uint32_t timer)
{
    if(__gptimer_isvalid(timer))
    {
        return E_FAULT;
    }
    return __gptimer_clear(timer);
}
