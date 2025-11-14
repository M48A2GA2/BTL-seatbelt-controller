#include "finals.h"
#include "MKL46Z4.h"

typedef enum {
	no_person,
	person_sitting_delay,
	person_sitting_warning,
	person_belted
} seatbelt_state;

int main(void)
{
	seatbelt_state state_current = no_person;
	uint32_t timer_start = 0;
	int red_status = 0;
	
	InitLED();
	InitSW1();
	InitSW3();
	InitSysTick();
	__enable_irq();
	
	while (1)
	{
		int person_present = !(PTC->PDIR & (1u << 3));
		int belt_fastened  = !(PTC->PDIR & (1u << 12));
		uint32_t time_current = mstick;

		switch (state_current)
		{
			case no_person:
				greenLED(0);
				redLED(0);
				if (person_present)
				{
					state_current = person_sitting_delay;
					timer_start = time_current;
				}
				break;
			
			case person_sitting_delay:
				greenLED(0);
				redLED(0);
				if (!person_present) 
				{
					state_current = no_person;
				}
				else if (belt_fastened)
				{
					state_current = person_belted;
				}
				else if ((time_current - timer_start) >= 2000)
				{
					state_current = person_sitting_warning;
					timer_start = time_current;
					red_status = 1;
				}
				break;
				
			case person_sitting_warning:
				greenLED(0);
				
				if ((time_current - timer_start) >= 500) 
				{
					red_status = !red_status;
					timer_start = time_current;
				}
				redLED(red_status);
				
				if (!person_present)
				{
					state_current = no_person;
				}
				else if (belt_fastened)
				{
					state_current = person_belted;
				}
				break;
				
			case person_belted:
				greenLED(1);
				redLED(0);
			
				if (!person_present) 
				{
					state_current = no_person;
				}
				else if (!belt_fastened) 
				{
					state_current = person_sitting_delay;
					timer_start = time_current;
				}
				break; 
		}
	}
}