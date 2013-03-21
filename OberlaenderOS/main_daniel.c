/*
 * main_daniel.c
 *
 *  Created on: 21.03.2013
 *      Author: Daniel
 */
#ifdef Daniel

#define ADDRESS     volatile unsigned int*
#define GPIO5_DIR   (ADDRESS) 0x49056094
#define LED0_PIN    (1 << 21)
#define LED1_PIN    (1 << 22)
#define GPIO5_OUT   (ADDRESS) 0x4905603C

void main_daniel(void)
{

    *(GPIO5_DIR) |= (LED0_PIN | LED1_PIN);
    *(GPIO5_OUT) &= ~LED1_PIN;
    int i;

    while(1)
    {
        for(i = 0; i < 300000; i++);

        *(GPIO5_OUT) ^= (LED0_PIN | LED1_PIN);
    }
}
#endif
