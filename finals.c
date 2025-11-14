#include "finals.h"
#include "MKL46Z4.h"

volatile uint32_t mstick = 0;

void InitLED()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //(1 << 12); clock gating
	PORTD->PCR[5] = PORT_PCR_MUX(1); // (1 << 8); select GPIO for PTD5
	PTD->PDDR |= (1u<<5);
	PTD->PSOR = (1u<<5);
	
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE->PCR[29] = PORT_PCR_MUX(1);
	PTE->PDDR |= (1u<<29);
	PTE->PSOR = (1u<<29);
}
void InitSW1()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PTC->PDDR &= ~((uint32_t)(1u<<3));;
}
void InitSW3()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PTC->PDDR &= ~((uint32_t)(1u<<12));
}
void InitSysTick(void) 
{
	SysTick_Config(SystemCoreClock / 1000);
}
void SysTick_Handler(void) 
{
	mstick++;
}
void redLED(int on) 
{
	if (on) 
	{
		PTE->PCOR = (1u << 29);
	} 
	else 
	{
		PTE->PSOR = (1u << 29);
	}
}
void greenLED(int on) 
{
	if (on) 
	{
		PTD->PCOR = (1u << 5);
	} 
	else 
	{
		PTD->PSOR = (1u << 5);
	}
}
/*
void button1()
{
	if (PTC->PDIR & (1u<<3)) 
	{
		PTD->PSOR = (1u<<5); 
	}
	else 
	{
		PTD->PCOR = (1u<<5); 
	}
}
void button3()
{
	if (PTC->PDIR & (1u<<12)) 
	{
		PTE->PSOR = (1u<<29); 
	}
	else
	{
		PTE->PCOR = (1u<<29);
	}
}
void BlinkLED1()
{ //This method turns the LED off, then back on using two separate commands.
	uint32_t i = 0; //Create a loop variable
	
	PTE->PDOR |= (1u<<29);//Set PTD5 = 1, turns LED OFF (Cathode connected to PTD5)
	for(i=0; i < 900000; i++){}; //Burn some time
	PTE->PDOR &= ~((uint32_t)(1u<<29)); //Clear PTD5 = 0, turns LED ON
	for(i=0; i < 900000; i++){}; //Burn some time
}
*/
