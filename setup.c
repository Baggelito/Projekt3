
#include "Header.h"

// Definerar vilka lampor/kanppar/pwm

led_t led1_d, led2_d, led3_b, led4_b, led5_b;
button_t button1_d, button2_d, button3_b, button4_b ,button5_b;
pwm_t pwm1;
led_vector_t v1, v2, v3, v4, v5;

volatile bool led1_enabled = false;
volatile bool led2_enabled = false;
volatile bool led3_enabled = false;
volatile bool led4_enabled = false;
volatile bool led5_enabled = false;

void setup(void)
{
	led_init(&led1_d, 6);
	led_init(&led2_d, 7);
	led_init(&led3_b, 8);
	led_init(&led4_b, 9);
	led_init(&led5_b, 10);
	
	
	button_init(&button1_d, 2);
	button_init(&button2_d, 3);
	button_init(&button3_b, 11);
	button_init(&button4_b, 12);
	button_init(&button5_b, 13);
	
	pwm_init(&pwm1, A0);
	
	led_vector_init(&v1);
	led_vector_init(&v2);
	led_vector_init(&v3);
	led_vector_init(&v4);
	led_vector_init(&v5);
	
	button_enable_interrupt(&button1_d);
	button_enable_interrupt(&button2_d);
	button_enable_interrupt(&button3_b);
	button_enable_interrupt(&button4_b);
	button_enable_interrupt(&button5_b);
}