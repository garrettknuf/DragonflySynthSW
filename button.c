/*
 * @file button.c
 * @brief Push button basic functionality.
 *
 * @author Garrett Knuf
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include "button.h"

static const uint8_t DEBOUNCE_TIME = 20;  // milliseconds

static uint8_t counter;
static bool status;

void button_init(void) {
	counter = 0;
	status = false;
	
	// Set button pin to input
	DDRD &= ~(1<<2);
}

void button_debounce(void) {
	if ((PIND & (1<<2)) == 0) {
		counter++;
		if (counter == DEBOUNCE_TIME) {
			status = true;
		} else if (counter > DEBOUNCE_TIME) {
			// prevent overflow of counter
			counter = DEBOUNCE_TIME;
		}
	} else {
		counter = 0;
	}
}

bool button_get_status(void) {
	// Prevent race condition by disabling interrupts
	cli();
	// Clear status flag
	bool ret_val = status;
	status = false;
	// Re-enable interrupts
	sei();
	return ret_val;
}