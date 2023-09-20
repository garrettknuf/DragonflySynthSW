/*
 * @file leds.h
 *
 * @author Garrett Knuf
 */ 

#ifndef LEDS_H_
#define LEDS_H_

#include "notes.h"

typedef enum {
	kLedIdSqWave,
	kLedIdSinWave,
	kLedIdTriWave,
	kLedIdSawWave,	
	kLedIdCount
} LedId;

/*
 * @brief Set all LED pins as outputs.
 */
void leds_init(void);

/*
 * @brief Turn off the specified LED.
 *
 * @param led_id - led to turn off
 */
void leds_off(Waveshape shape);

/*
 * @brief Turn on the specified LED.
 *
 * @param led_id - led to turn on
 */
void leds_on(Waveshape shape);

#endif /* LEDS_H_ */