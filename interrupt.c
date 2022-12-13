
#include "Header.h"

//Interrupter för både de olika port raderna = Just nu är det bara för B och D portarna.  


ISR(PCINT0_vect)
{
	if(button_is_pressed(&button3_b))
	{
		led3_enabled = !led3_enabled;
	}
	else if (button_is_pressed(&button4_b))
	{
		led4_enabled = !led4_enabled;
	}
	else if (button_is_pressed(&button5_b))
	{
		led5_enabled = !led5_enabled;
	}
  
  return;
}

ISR(PCINT2_vect)
{
	if(button_is_pressed(&button1_d))
	{
		led1_enabled = !led1_enabled;
	}
	else if(button_is_pressed(&button2_d))
	{
		led2_enabled = !led2_enabled;
	}
   
   return;
}
