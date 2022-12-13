#include "Header.h"


//Kör programmet vad som händer i main. 
//Hela detta programmet är för att få hur starkt lampan ska lysa

void run(void)
{
	pwm_get_values(&pwm1, 1000); // Vilken potensumeter du ger infon till och hur lång tid i us
	
	
	// Sätter igång lampan om poståendet är sant
	if (led1_enabled) led_on(&led1_d); 
	if (led2_enabled) led_on(&led2_d);
	if (led3_enabled) led_on(&led3_b);
	if (led4_enabled) led_on(&led4_b);
	if (led5_enabled) led_on(&led5_b);
	delay_us(pwm1.pwm_on_us); // Hur länge lampan ska vara igång
	
	
	//Stänger av lamporna
	led_off(&led1_d);
	led_off(&led2_d);
	led_off(&led3_b);
	led_off(&led4_b);
	led_off(&led5_b);
	delay_us(pwm1.pwm_off_us); // Hur länge lampan ska vara släckt
	
}