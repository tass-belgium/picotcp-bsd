/*
 * pico_osal.h
 *
 *  Created on: December 2013
 *      Author: Maxime Vincent
 * Description: OS Abstraction Layer between PicoTCP and FreeRTOS
 *
 */
/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "portmacro.h"


/* PicoTCP includes */
#include "pico_defines.h"
#include "pico_config.h"
#include "pico_osal.h"

#define osal_dbg(...)
//#define osal_dbg(...) printf(__VA_ARGS__)

/*****************************************************************************
 * Public functions
 ****************************************************************************/

struct osal_mutex {
    void * mutex;
    uint8_t idx; /* only to keep track of the amount/idx, no real function .. */
};
static uint8_t mtx_number = 0;


/* ============= */
/* == SIGNALS == */
/* ============= */

void * pico_signal_init(void)
{
    struct osal_mutex *signal;
    signal = pico_zalloc(sizeof(struct osal_mutex));
    osal_dbg("mi: %p for %p\n", signal, __builtin_return_address(0));
    if (!signal)
        return NULL;
    signal->mutex= xSemaphoreCreateBinary();
    signal->idx = mtx_number++;
    return signal;
}

void pico_signal_deinit(void * signal)
{
    struct osal_mutex * mtx = signal;
    vSemaphoreDelete(mtx->mutex);
    pico_free(signal);
}

void pico_signal_wait(void * signal)
{
    pico_signal_wait_timeout(signal, portMAX_DELAY);
}

int pico_signal_wait_timeout(void * signal, int timeout)
{
    int retval = 0;
	if(signal != NULL)
	{
        struct osal_mutex * mtx = signal;
        if (timeout == portMAX_DELAY) {
            while (xSemaphoreTake(mtx->mutex, portMAX_DELAY) == pdFALSE);
        } else {
            retval = xSemaphoreTake(mtx->mutex, timeout);
        }
	}
    if (retval) {
        return 0; /* Success */
    } else {
        return -1; /* Timeout */
    }
}

void pico_signal_send(void * signal)
{
	if(signal != NULL)
    {
        struct osal_mutex * mtx = signal;
		xSemaphoreGive(mtx->mutex);
    }
}

void pico_signal_send_ISR(void * signal)
{
	if(signal != NULL)
    {
        struct osal_mutex * mtx = signal;
        long task_switch_needed = 0;
		xSemaphoreGiveFromISR(mtx->mutex, &task_switch_needed);
        portYIELD_FROM_ISR(task_switch_needed);
    }
}

/* ============= */
/* == MUTEXES == */
/* ============= */


void *pico_mutex_init(void)
{
    struct osal_mutex *mutex;
    mutex = pico_zalloc(sizeof(struct osal_mutex));
    osal_dbg("mi: %p for %p\n", mutex, __builtin_return_address(0));
    if (!mutex)
        return NULL;
    mutex->mutex = xSemaphoreCreateMutex();
    mutex->idx = mtx_number++;
    return mutex;
}

void pico_mutex_deinit(void * mutex)
{
    pico_signal_deinit(mutex);
}

int pico_mutex_lock_timeout(void * mutex, int timeout)
{
    pico_signal_wait_timeout(mutex, timeout);
}

void pico_mutex_lock(void * mutex)
{
    pico_signal_wait_timeout(mutex, portMAX_DELAY);
}

void pico_mutex_unlock(void * mutex)
{
    pico_signal_send(mutex);
}

void pico_mutex_unlock_ISR(void * mutex)
{
    pico_signal_send_ISR(mutex);
}


/* ============= */
/* == THREADS == */
/* ============= */
/* MVI TODO: Not implemented yet, threads are now created within the app .. */
int pico_thread_create()
{
    return 0;
};


int pico_thread_somethingelse()
{
    return 0;
};

