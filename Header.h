/*
 * Header.h
 *
 * Created: 2022-12-08 10:19:13
 *  Author: a2
 */ 


#ifndef HEADER_H_
#define HEADER_H_


#include "led.h"
#include "button.h"
#include "led_vector.h"
#include "pwm.h"

//sättere alla värden globala. 

extern led_t led1_d, led2_d, led3_b, led4_b, led5_b;
extern button_t button1_d, button2_d, button3_b, button4_b ,button5_b;
extern pwm_t pwm1;
extern led_vector_t v1, v2, v3, v4, v5;
extern volatile bool led1_enabled;
extern volatile bool led2_enabled;
extern volatile bool led3_enabled;
extern volatile bool led4_enabled;
extern volatile bool led5_enabled;

void setup(void);
void run(void);

#endif /* HEADER_H_ */