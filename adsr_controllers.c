/*
 * adsr_controllers.c
 *
 * Created: 9/19/2023 7:42:11 PM
 *  Author: garrett
 */ 

#include <stdint.h>
#include <avr/io.h>

typedef enum {
	kAdsrStageAttack,
	kAdsrStageDecay,
	kAdsrStageSustain,
	kAdsrStageRelease,
	kAdsrStageComplete,
} AdsrStage;

typedef struct {
	AdsrStage stage;
	uint16_t counter;
} adsr_controller_t;

adsr_controller_t adsr1 = {kAdsrStageAttack,0};

static uint8_t get_level_helper(uint16_t counter, uint16_t compare_value);

static uint16_t attack, decay, sustain, release;

void adsr_controllers_init(void) {
	attack = 500;
	decay = 500;
	sustain = 500;
	release = 500;
	
	adsr1.stage = kAdsrStageAttack;
	adsr1.counter = 0;
}

void adsr_controllers_set_attack(uint16_t attack_time) {
	attack = attack_time;
}

void adsr_controllers_set_decay(uint16_t decay_time) {
	decay = decay_time;
}

void adsr_controllers_set_sustain(uint16_t sustain_time) {
	sustain = sustain_time;
}

void adsr_controllers_set_release(uint16_t release_time) {
	release = release_time;
}

void adsr_controllers_update(void) {
	adsr1.counter++;
	
	uint16_t compare_value = 0;
	
	switch (adsr1.stage) {
		case kAdsrStageAttack:
			compare_value = attack;
			break;
		case kAdsrStageDecay:
			compare_value = decay;
			break;
		case kAdsrStageSustain:
			compare_value = sustain;
			break;
		case kAdsrStageRelease:
			compare_value = release;
			break;
		default:
			return;
	}
	
	if (adsr1.counter == compare_value) {
		adsr1.stage++;
		adsr1.counter = 0;
	}
}

void adsr_controllers_reset(void) {
	adsr1.stage = kAdsrStageAttack;
	adsr1.counter = 0;
}

// level is 0-8
uint8_t adsr_controllers_get_level(void) {
	uint16_t compare_value;
	
	switch (adsr1.stage) {
		case kAdsrStageAttack:
			compare_value = attack;
			return get_level_helper(adsr1.counter, compare_value);
		case kAdsrStageDecay:
			compare_value = decay;
			return 8 - (get_level_helper(adsr1.counter, compare_value) >> 1);
		case kAdsrStageSustain:
			// half volume
			return 4;
		case kAdsrStageRelease:
			compare_value = release;
			return 4 - (get_level_helper(adsr1.counter, compare_value) >> 1);
		default:
			return 0;
	}
	
	
}

static uint8_t get_level_helper(uint16_t counter, uint16_t compare_value) {	
	if (counter < (compare_value >> 3)) {
		// 1/8 volume
		return 1;
	} else if (counter < (compare_value >> 2)) {
		// 1/4 volume
		return 2;
	} else if (counter < (compare_value >> 3) + (compare_value >> 2)) {
		// 3/8 volume
		return 3;
	} else if (counter < (compare_value >> 1)) {
		// 1/2 volume
		return 4;
	} else if (counter < (compare_value >> 1) + (compare_value >> 3)) {
		// 5/8 volume
		return 5;
	} else if (counter < (compare_value >> 1) + (compare_value >> 2)) {
		// 3/4 volume
		return 6;
	} else if (counter < (compare_value >> 1) + (compare_value >> 2) + (compare_value >> 3)) {
		// 7/8 volume
		return 7;
	} else {
		// full volume
		return 8;
	}
}
