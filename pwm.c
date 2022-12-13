
#include "pwm.h"

#define ADC_MAX 1023.0

// Vilka pins som kan ha pwm
void pwm_init(pwm_t* self, const uint8_t pin)
{
	if(pin >= 0 && pin <=5)
	{
		self->pin = pin;
	}
	else if(pin >= 14 && pin <= 19)
	{
		self->pin = pin-14;
	}

	return;
}

//L�ser av vilka pin som vi anv�nder oss av och s�tter pwm p� dom
uint16_t pwm_read(pwm_t* self)
{
	ADMUX = (1 << REFS0) | self->pin;
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	while (read(ADCSRA, ADIF) == 0);
	set(ADCSRA,ADIF);
	
	return ADC;	
}

//V�rdet som potesnumetern har
double pwm_duty_cycle(pwm_t* self)
{
	return pwm_read(self) / ADC_MAX;
}

// S�tter hur l�ng varje sekvens �r och hur l�ng p� och av tid f�r att best�mma lysdioden
void pwm_get_values(pwm_t* self,
					const uint16_t period_us)
{
	self->pwm_on_us = (uint16_t)(pwm_duty_cycle(self) * period_us + 0.5);
	self->pwm_off_us = period_us - self->pwm_on_us;	
}
