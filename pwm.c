
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

//Läser av vilka pin som vi använder oss av och sätter pwm på dom
uint16_t pwm_read(pwm_t* self)
{
	ADMUX = (1 << REFS0) | self->pin;
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	while (read(ADCSRA, ADIF) == 0);
	set(ADCSRA,ADIF);
	
	return ADC;	
}

//Värdet som potesnumetern har
double pwm_duty_cycle(pwm_t* self)
{
	return pwm_read(self) / ADC_MAX;
}

// Sätter hur lång varje sekvens är och hur lång på och av tid för att bestämma lysdioden
void pwm_get_values(pwm_t* self,
					const uint16_t period_us)
{
	self->pwm_on_us = (uint16_t)(pwm_duty_cycle(self) * period_us + 0.5);
	self->pwm_off_us = period_us - self->pwm_on_us;	
}
