/*
 * @file notes.c
 * @brief
 *
 * @author Garrett Knuf
 */ 

#define POLYPHONY_DEGREE 4

#include <avr/io.h>
#include <math.h>
#include "notes.h"

// Waveform shape for generating samples
static Waveshape waveshape;

typedef struct {
	uint16_t counter;  // counter to be updates
	uint16_t compare_value;  // maximum counter value
	uint8_t output;  // data to be sent to DAC (0 - 255)
} note_t;

static note_t note1;

static void update_square_wave(note_t* note);
static void update_sine_wave(note_t* note);
static void update_triangle_wave(note_t* note);
static void update_sawtooth_wave(note_t* note);


void notes_init(void) {
	waveshape = kWaveshapeSquare;
	
	note1.counter = 0;
	note1.compare_value = 0;
	note1.output = 0;
}

void notes_set_freq(uint16_t frequency) {
	// calculations made on the assumption that sample is updated every 25us
	note1.counter = 0;
	note1.compare_value = (uint16_t)(40000 / frequency);
}

void notes_set_waveshape(Waveshape shape) {
	if (shape != waveshape) {
		waveshape = shape;
		note1.counter = 0;
	}
	
}

void notes_update(void) {
	note1.counter++;
	
	switch (waveshape) {
		case kWaveshapeSquare:
			update_square_wave(&note1);
			break;
		case kWaveshapeSine:
			update_sine_wave(&note1);
			break;
		case kWaveshapeSawtooth:
			update_sawtooth_wave(&note1);
			break;
		case kWaveshapeTriangle:
			update_triangle_wave(&note1);
			break;
		default:
			break;
	}
}

Waveshape notes_get_waveshape(void) {
	return waveshape;
}

uint8_t notes_get_output(void) {
	return note1.output;
}


/* SAMPLING FUNCTIONS */

static void update_square_wave(note_t* note) {
	if (note->counter == (note->compare_value / 2)) {
		note->counter = 0;
		if (note->output == 0) {
			note->output = 0xFF;
			} else {
			note->output = 0x00;
		}
	}
}

static void update_sine_wave(note_t* note) {
	note->counter %= note->compare_value;
	
	// Taylor expansion?
}

static void update_sawtooth_wave(note_t* note) {
	if (note->counter == note->compare_value) {
		note->counter = 0;
	}
	note->output = (uint8_t)(note->counter * 255 / (note->compare_value));
}

static void update_triangle_wave(note_t* note) {
	if (note->counter == note->compare_value) {
		note->counter = 0;
	}
	
	if (note->counter < note->compare_value / 2) {
		note->output = (uint8_t)(note->counter * 255 / (note->compare_value >> 1));
	} else {
		note->output = (uint8_t)((note->compare_value - note->counter) * 255 / (note->compare_value >> 1));
	}
}
