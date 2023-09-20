/*
 * @file timer.c
 * @brief Setup timers that trigger compare match interrupts.
 *
 * @author Garrett Knuf
 */ 

#include <avr/io.h>
#include "timers.h"

void timers_1ms_init(void){
	// f = cpu_clock / (prescaler * (1 + TOP))
	//   = 16000000 / (64 * (1 + 249))
	//   = 1000 Hz
	TCCR0A = (1 << WGM01); // CTC mode
	TCCR0B = (1 << CS01) | (1 << CS00); // 64 prescaler
	OCR0A = 249; // TOP
	TIMSK0 = (1 << OCIE0A); // enable OCR0A compare match interrupts
}

void timers_25us_init(void){
	// f = cpu_clock / (prescaler * (1 + TOP))
	//   = 16000000 / (8 * (1 + 49))
	//   = 40000 Hz = 40 kHz
	TCCR2A = (1<<WGM21); // CTC mode
	TCCR2B = (1<<CS21); // 64 prescaler
	OCR2A = 49; // TOP
	TIMSK2 = (1 << OCIE2A); // enable OCR0A compare match interrupts
}