/*
 * notes.h
 *
 * Created: 9/10/2023 8:10:36 PM
 *  Author: garrett
 */ 


#ifndef NOTES_H_
#define NOTES_H_

#include <stdint.h>

typedef enum {
	kWaveshapeSquare ,
	kWaveshapeSine,
	kWaveshapeTriangle,
	kWaveshapeSawtooth,
	kWaveshapeCount,
} Waveshape;

void notes_init(void);

void notes_set_freq(uint16_t frequency);

void notes_set_waveshape(Waveshape shape);

void notes_update(void);

Waveshape notes_get_waveshape(void);

uint8_t notes_get_output(void);

#endif /* NOTES_H_ */