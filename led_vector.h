/*
 * led_vector.h
 *
 * Created: 2022-11-24 11:12:09
 *  Author: a2
 */ 


#ifndef LED_VECTOR_H_
#define LED_VECTOR_H_

#include "misc.h"
#include "led.h"

typedef struct
{
	led_t* leds;
	size_t size;
	
}led_vector_t;

void led_vector_init(led_vector_t* self);
void led_vector_clear(led_vector_t* self);
void led_vector_on(led_vector_t* self);
void led_vector_off(led_vector_t* self);
int led_vector_push(led_vector_t* self, const led_t* leds);
int led_vector_pop(led_vector_t* self);
void led_vector_toogle(led_vector_t* self);
void led_vector_blink_collectivaly(led_vector_t* self, const uint16_t blink_speed_ms);
void led_vector_blink_sequentially(led_vector_t* self, const uint16_t blink_speed_ms);


#endif /* LED_VECTOR_H_ */