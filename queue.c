/*
 * @file queue.c
 *
 * @author Garrett Knuf
 */ 

#include "notes.h"

static uint8_t length;


static const uint8_t capacity;

void queue_init(uint8_t capacity) {
	length = 0;
	capacity = capacity;
}

void queue_push(queue_t* queue, note_t* note) {
	
}

note_t queue_pop(queue_t* queue) {
	
}