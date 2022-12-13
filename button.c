/*
 * button.c
 *
 * Created: 2022-11-18 09:57:09
 *  Author: a2
 */ 
#include "button.h"


//¨Vad som ska hända när man tycker på knappen
bool button_is_pressed(button_t* self)
{
	if(self->io_port == IO_PORTB)
	{
		return (PINB &(1 << self->pin));
	}
	else if (self->io_port == IO_PORTC)
	{
		return (PINC &(1 << self->pin));
	}
	else if (self->io_port == IO_PORTD)
	{
		return (PIND &(1 << self->pin));
	}
	else
	{
		return false;
	}
}

//Sätter vilken pin/port som tillhör knappen
void button_init(button_t* self, const uint8_t pin)
{
	if (pin >= 0 && pin <= 7)
	{
		self->io_port = IO_PORTD;
		self->pin = pin;
		PORTD |= (1 << self->pin);
	}
	else if (pin >= 8 && pin <= 13)
	{
		self->io_port = IO_PORTB;
		self->pin = pin - 8;
		PORTB |= (1 << self->pin);
	}
	else if (pin >= 14 && pin <= 19)
	{
		self->io_port = IO_PORTC;
		self->pin = pin - 14;
		PORTC |= (1 << self->pin);
	}

	self->interrupt_enabled = false;
	return;
}

//Tar bort en knapp från koden t.ex om någon trycker på nödstopp så ska du inte kunna starta igen
void button_clear(button_t* self)
{
	//self->interrupt_disable();
	
	if(self->io_port == IO_PORTB)
	{
		DDRB &= ~(1 << self->pin);
	}
	else if(self->io_port == IO_PORTC)
	{
		DDRC &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		DDRD &= ~(1 << self->pin);
	}
	
	
	self->io_port = IO_PORT_NONE;
	self->pin = 0;

	return;
}


/********************************************************************************
* button_enable_interrupt: Aktiverar PCI-avbrott på angiven tryckknapp så att
*                          event på tryckknappens pin medför avbrott, både på
*                          stigande och fallande flank. Kontroll av flank måste
*                          skötas av användaren, förslagsvis via avläsning i
*                          motsvarande avbrottsrutin.
*
*                          Nedan visas sambandet mellan använd I/O-port samt
*                          avbrottsvektorn för motsvarande avbrottsrutin:
*
*                          I/O-port     pin (Arduino Uno)     Avbrottsvektor
*                             B              8 - 13             PCINT0_vect
*                             C             A0 - A5             PCINT1_vect
*                             D              0 - 7              PCINT2_vect
*
*                          - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska aktiveras på.
********************************************************************************/
void button_enable_interrupt(button_t* self)
{
	asm("SEI");

	if (self->io_port == IO_PORTB)
	{
		PCICR |= (1 << PCIE0);
		PCMSK0 |= (1 << self->pin);
	}
	else if (self->io_port == IO_PORTC)
	{
		PCICR |= (1 << PCIE1);
		PCMSK1 |= (1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		PCICR |= (1 << PCIE2);
		PCMSK2 |= (1 << self->pin);
	}

	self->interrupt_enabled = true;
	return;
}

/********************************************************************************
* button_disable_interrupt: Inaktiverar PCI-avbrott på angiven tryckknapp.
*
*                           - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska inaktiveras på.
********************************************************************************/
void button_disable_interrupt(button_t* self)
{
	if (self->io_port == IO_PORTB)
	{
		PCMSK0 &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTC)
	{
		PCMSK1 &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		PCMSK2 &= ~(1 << self->pin);
	}

	self->interrupt_enabled = false;
	return;
}

/********************************************************************************
* button_togglar_interrupt: Togglar aktivering av PCI-avbrott på angiven
*                           tryckknapp. Om avbrott är aktiverat vid anrop
*                           så sker inaktivering. På samma sätt gäller att om
*                           avbrott är inaktiverat vid anrop så sker aktivering.
*
*                           - self: Pekare till tryckknappen som aktivering av
*                                   PCI-avbrott ska inaktiveras på.
********************************************************************************/
void button_toggle_interrupt(button_t* self)
{
	if (self->interrupt_enabled)
	{
		button_disable_interrupt(self);
	}
	else
	{
		button_enable_interrupt(self);
	}

	return;
}
