/*
 * @file dac_util.c
 * @brief Utility for SPI transmission to DAC (MPC 4801)
 *
 * The MPC 4801 Digital-to-Analog Converter (DAC) is controlled via SPI.
 * The AVR MCU is the master, and the DAC is the slave. The master communicates
 * with the slave via 16-bit commands. The Atmega 328p has an 8-bit shift
 * register in its SPI hardware, so it can only transmit 8-bits at a time. Each
 * time an 8-bit transmission is complete, an interrupt is raised. This DAC
 * utility file performs a two step transmission process (sends most-significant
 * byte first and then least-significant byte).
 *
 * Attempts to transmit data while SPI is busy will be ignored.
 *
 * @author Garrett Knuf
 */ 

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "dac_util.h"

#define LDAC 1
#define CS 2
#define MOSI 3
#define SCK 5

// Status of SPI transmissions
static bool busy = false;

// 2 bytes to transmit
static uint8_t MSB = 0xFF;
static uint8_t LSB = 0xFF;

// Remaining bytes left to transmit until transmission is complete
static uint8_t bytes_left = 0;

/*
 * Config bits for MSB of DAC transmission:
 * |write control|N/A|gain select|shutdown control|N/A|N/A|N/A|N/A|
*/
static const char config_bits = 0x10;

void dac_init(void) {
	// Set MOSI, SCK, SS, and LDAC to output
	DDRB = (1<<MOSI) | (1<<SCK) | (1<<CS) | (1<<LDAC);
	
	// Enable SPI, enable interrupts, master, set clock f_osc/16
	SPCR = (1<<SPIE) | (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}

void dac_set_output(uint8_t data) {
	if (!busy) {
		busy = true;
		bytes_left = 2;
	
		// First byte to write: |4 config bits|4 most-significant data bits|
		MSB = config_bits | (data>>4);
		// Second byte to write: |4 least-significant data bits|4 N/A bits|
		LSB = (data<<4);
	
		// Set data SPI data register
		SPDR = MSB;
		// Pull CS low
		PORTB &= ~(1<<CS);
	}
}

ISR(SPI_STC_vect) {
	bytes_left--;
	
	if (bytes_left == 1) {
		// Transmit next byte
		SPDR = LSB;
	} else {
		// Pull CS high
		PORTB |= (1<<CS);
		// Transmission complete
		busy = false;
		// Refresh LDAC
		PORTB &= ~(1<<LDAC);
		PORTB |= (1<<LDAC);
	}
}
