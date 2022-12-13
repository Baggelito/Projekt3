
#ifndef PWM_H_
#define PWM_H_

#include "misc.h"

typedef struct
{
   uint8_t pin;
   uint16_t pwm_on_us;
   uint16_t pwm_off_us;
} pwm_t;

void pwm_init(pwm_t* self, const uint8_t pin);
double pwm_duty_cycle(pwm_t* self);
uint16_t pwm_read(pwm_t* self);
void pwm_get_values(pwm_t* self,
					const uint16_t period_us);

#endif /* ADC_H_ */