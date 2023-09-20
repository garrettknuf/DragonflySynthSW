/*
 * @file button.h
 *
 * @author Garrett Knuf
 */ 

#ifndef BUTTON_H_
#define BUTTON_H_

/*
 * @brief Set button pin as inputs.
 */
void button_init(void);

/*
 * @brief Set status flag of button if button is pressed.
 *		NOTE: Should be called every 1ms.
 */
void button_debounce(void);

/*
 * @brief Get status of button press. Status flag cleared after function call.
 *		Button needs to be released to register a second press. Interrupts are
 *		disabled during function call to prevent race condition.
 *
 * @return true if button press registered, false otherwise
 */
bool button_get_status(void);

#endif /* BUTTON_H_ */