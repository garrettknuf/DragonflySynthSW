/*
 * @file timer.h
 *
 * @author Garrett Knuf
 */ 

#ifndef TIMER_H_
#define TIMER_H_

/*
 * @brief Enable Timer0 to generate compare match interrupts every 1ms.
 *		NOTE: Global interrupts need to be enabled as well.
 */
void timers_1ms_init(void);

/*
 * @brief Enable Timer2 to generate compare match interrupts every 25us.
 *		NOTE: Global interrupts need to be enabled as well.
 */
void timers_25us_init(void);

#endif /* TIMER_H_ */