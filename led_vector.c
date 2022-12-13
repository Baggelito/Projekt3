#include "led_vector.h"

//Hur stor arrayn ska vara och hur många lsydioder det är
void led_vector_init(led_vector_t* self)
{
	self->leds = 0;
	self->size = 0;
}


void led_vector_clear(led_vector_t* self)
{
	free(self->leds);
	led_vector_init(self);
}


//Alla lampor ska vara på
void led_vector_on(led_vector_t* self)
{
	for (size_t i = 0; i < self-> size; i++)
	{
		led_on(&self->leds[i]);
	}
}

//Alla lampor ska vara av
void led_vector_off(led_vector_t* self)
{
	for (size_t i = 0; i < self-> size; i++)
	{
		led_off(&self->leds[i]);
	}
}

// Lägger till en lysdiod i arrayen
int led_vector_push(led_vector_t* self, const led_t* new_led)
{
	led_t* copy = (led_t*)realloc(self->leds, sizeof(led_t) * (self->size + 1));
	if(!copy) return 1;
	copy[self->size++] = *new_led;
	self->leds = copy;
	
	return 0;
}


//Tar bort en diod från arrayen
int led_vector_pop(led_vector_t* self)
{
	if(self->size <=1) // om size är 1 eller mindre så clearar den arrayen istället för att minska den.
	{
		led_vector_clear(self);
	}
	else
	{
		led_t* copy = (led_t*)realloc(self->leds, sizeof(led_t) * (self->size - 1));
		if (!copy) return 1;
		self->leds = copy;
		self->size--;
	}
	return 0;
}

void led_vector_toogle(led_vector_t* self)
{
	for (size_t i = 0; i < self->size; ++i)
	{
		led_toggle(&self->leds[i]);
	}
	
	/*
	for (led_t* i = self->leds; i < self->leds + self->size; ++i)
	{
		led_toggle(i);
	}
	*/
	return;
	
}

// Lamporna blinkar tillsammans samtdigit 

void led_vector_blink_collectivaly(led_vector_t* self, const uint16_t blink_speed_ms)
{
	led_vector_on(self);
	delay_ms(blink_speed_ms);
	led_vector_off(self);
	delay_ms(blink_speed_ms);
}

//Julgran effekt

void led_vector_blink_sequentially(led_vector_t* self, const uint16_t blink_speed_ms)
{
	led_vector_off(self);
	
	for(size_t i = 0; i < self->size; i++)
	{
		led_on(&self->leds[i]);
		delay_ms(blink_speed_ms);
		led_off(&self->leds[i]);	
	}
}
