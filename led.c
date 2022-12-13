
//innehåller funktioner för led
#include "led.h"


// Definerar vilka pin och vilken port de till hör
void led_init(led_t* self,
			  const uint8_t pin)
{
	if (pin >= 0 && pin <= 7)
	{
		self->io_port = IO_PORTD;
		self->pin = pin;
		DDRD |= (1 << self->pin);
	}
	else if (pin >= 8 && pin <= 13)
	{
		self->io_port = IO_PORTB;
		self->pin = pin -8;
		DDRB |= (1 << self->pin);
	}

	else
	{
		
		self->io_port = IO_PORT_NONE;
		self->pin = 0;	
	}
	
	self->enabled = false;
	
	
}

//Får dioden att lysa 
void led_on(led_t* self)
{
	if(self->io_port == IO_PORTB)
	{
		PORTB |= (1 << self->pin);
	}
	else if(self->io_port == IO_PORTD)
	{
		PORTD |= (1 << self->pin);
	}
	self->enabled = true;
	
	return;
}

//Släcker dioden
void led_off(led_t* self)
{
	if(self->io_port == IO_PORTB)
	{
		PORTB &= ~(1 << self->pin);
	}
	else if(self->io_port == IO_PORTD)
	{
		PORTD &= ~(1 << self->pin);
	}
	self->enabled = true;
	
	return;
}


//Är för en push funktion som gör att när du tar bort dioden ska den släckas
void led_clear(led_t* self)
{
	led_off(self);
	
	if(self->io_port == IO_PORTB)
	{
		DDRB &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		DDRD &= ~(1 << self->pin);
	}
	
	self->pin = 0;
	self->io_port = IO_PORT_NONE;
	self->enabled = false;
	return;
}

//Toggle funktion 
void led_toggle(led_t* self)
{
	if(self->enabled)
	{
		led_off(self);
	}
	else
	{
		led_on(self); 
	}
	
	return;
}


//Hur snabbat dioden ska blinka
void led_blink(led_t* self,const uint16_t blink_speed_ms)
{
	led_toggle(self);
	delay_ms(blink_speed_ms);
	return;
}

