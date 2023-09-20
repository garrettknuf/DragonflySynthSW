/*
 * @file dac_util.h
 *
 * @author Garrett Knuf
 */ 

#ifndef DAC_UTIL_H_
#define DAC_UTIL_H_

/*
 * @brief Configure SPI settings to communicate with DAC.
 *		NOTE: Global interrupts need to enabled as well.
 */
void dac_init(void);

/*
 * @brief Begin 2 bytes transmission sequence to DAC via SPI.
 *		Calls to this function while SPI interface is busy will
 *		be ignored.
 *
 * @param data - output of DAC (0-255)
 */
void dac_set_output(uint8_t data);

#endif /* DAC_UTIL_H_ */