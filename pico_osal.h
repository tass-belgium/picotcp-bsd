/*
 * pico_osal.h
 *
 *  Created on: December 2013
 *      Author: Maxime Vincent
 * Description: OS Abstraction Layer between PicoTCP and FreeRTOS
 *
 */

#ifndef _PICO_OSAL_H_
#define _PICO_OSAL_H_

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/* Queue implementation API is: */

void * pico_mutex_init(void);
void pico_mutex_deinit(void * mutex);
void pico_mutex_lock(void * mutex);
int pico_mutex_lock_timeout(void * mutex, int timeout);
void pico_mutex_unlock(void * mutex);
void pico_mutex_unlock_ISR(void * mutex);

void * pico_signal_init(void);
void pico_signal_deinit(void * signal);
void pico_signal_wait(void * signal);
int pico_signal_wait_timeout(void * signal, int timeout);
void pico_signal_send(void * signal);
void pico_signal_send_ISR(void * signal);

#endif /* _PICO_OSAL_H_ */

