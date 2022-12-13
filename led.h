/*
 * led.h
 Funktionalitet för diodier och andra digitala utportar
 */ 


#ifndef LED_H_
#define LED_H_

#include "misc.h"

typedef struct
{
	uint8_t pin;       // Lysdioders pin-nummer på aktuell I/O port
	io_port_t io_port; // Porten som lysdioiden är ansluten till
	bool enabled;      // Indikerar om dioden är tänd

} led_t;

void led_init(led_t* self, 
			  const uint8_t pin);
			  
void led_clear(led_t* self);

void led_on(led_t* self);

void led_off(led_t* self);
			  
void led_toggle(led_t* self);
			  
void led_blink(led_t* self, 
			   const uint16_t blink_speed_ms);		
	  


#endif /* LED_H_ */