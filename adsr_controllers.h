/*
 * adsr_controllers.h
 *
 * Created: 9/19/2023 8:06:25 PM
 *  Author: garrett
 */ 


#ifndef ADSR_CONTROLLERS_H_
#define ADSR_CONTROLLERS_H_

void adsr_controllers_init(void);

void adsr_controllers_update(void);

uint8_t adsr_controllers_get_level(void);

void adsr_controllers_reset(void);

void adsr_controllers_set_attack(uint16_t attack_time);

void adsr_controllers_set_decay(uint16_t decay_time);

void adsr_controllers_set_sustain(uint16_t sustain_time);

void adsr_controllers_set_release(uint16_t release_time);

#endif /* ADSR_CONTROLLERS_H_ */