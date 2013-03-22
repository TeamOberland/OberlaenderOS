/*
 * main.c
 * Test comment to push to ORIGIN.
 */
typedef volatile unsigned int* address;


#define GPIO5_DIR  			(address) 0x49056034
#define LED0_PIN			(1 << 21)
#define LED1_PIN			(1 << 22)
#define GPIO5_OUT			(address) 0x4905603C

void main(void) {

	*(GPIO5_DIR) &= ~(LED0_PIN | LED1_PIN);
	*(GPIO5_OUT) &= ~LED1_PIN;
	int i;

	while(1) {
		for(i = 0; i < 300000; i++);

		*(GPIO5_OUT) ^= (LED0_PIN | LED1_PIN);
	}
}
