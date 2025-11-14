#include <stdint.h>

void InitLED(void); // Initialize GPIO
void BlinkLED1(void); // Use GPIO_PDOR
void InitSW1(void);
void InitSW3(void);

void InitSysTick(void);
void RedLED(int on);
void GreenLED(int on);

extern volatile uint32_t mstick;