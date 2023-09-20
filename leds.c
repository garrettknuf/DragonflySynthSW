/*
 * @file leds.c
 * @brief LED basic functionality.
 *
 * @author Garrett Knuf
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "leds.h"
	
void leds_init(void) {
	// Set led pins to outputs
	DDRB |= (1<<0);
	DDRD |= (1<<5) | (1<<6) | (1<<7);
	
	// Turn leds off
	PORTB &= ~(1<<0);
	PORTD &= ~((1<<5) | (1<<6 | (1<<7)));
}

void leds_off(Waveshape shape) {
	// Turn off led
	switch (shape) {
		case kWaveshapeSquare:
			PORTB &= ~(1<<0);
			break;
		case kWaveshapeSine:
			PORTD &= ~(1<<5);
			break;
		case kWaveshapeTriangle:
			PORTD &= ~(1<<6);
			break;
		case kWaveshapeSawtooth:
			PORTD &= ~(1<<7);
			break;
		default:
			break;
	}
}

void leds_on(Waveshape shape) {
	// Turn on led
	switch (shape) {
		case kWaveshapeSquare:
			PORTB |= (1<<0);
			break;
		case kWaveshapeSine:
			PORTD |= (1<<5);
			break;
		case kWaveshapeTriangle:
			PORTD |= (1<<6);
			break;
		case kWaveshapeSawtooth:
			PORTD |= (1<<7);
			break;
		default:
			break;
	}
}