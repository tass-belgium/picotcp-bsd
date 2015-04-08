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

/* ============= */
/* == MUTEXES == */
/* ============= */

struct osal_mutex {
    void * mutex;
    uint8_t idx; /* only to keep track of the amount/idx, no real function .. */
};

static uint8_t mtx_number = 0;

void * pico_mutex_init(void)
{
    struct osal_mutex * mutex;
    mutex = pico_zalloc(sizeof(struct osal_mutex));
    osal_dbg("mi: %p for %p\n", mutex, __builtin_return_address(0));
    if (!mutex)
        return NULL;
    vSemaphoreCreateBinary(mutex->mutex);
    if (!(mutex->mutex))
    {
        pico_free(mutex);
        return NULL;
    }
    mutex->idx = mtx_number++;
    return mutex;
}

void pico_mutex_deinit(void * mutex)
{
    struct osal_mutex * mtx = mutex;
    vSemaphoreDelete(mtx->mutex);
    pico_free(mutex);
}

int pico_mutex_lock_timeout(void * mutex, int timeout)
{
    int retval = 0;
	if(mutex != NULL)
	{
        struct osal_mutex * mtx = mutex;
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

void pico_mutex_lock(void * mutex)
{
    pico_mutex_lock_timeout(mutex, portMAX_DELAY);
}

void pico_mutex_unlock(void * mutex)
{
	if(mutex != NULL)
    {
        struct osal_mutex * mtx = mutex;
		xSemaphoreGive(mtx->mutex);
    }
}

void pico_mutex_unlock_ISR(void * mutex)
{
	if(mutex != NULL)
    {
        struct osal_mutex * mtx = mutex;
        long task_switch_needed = 0;
		xSemaphoreGiveFromISR(mtx->mutex, &task_switch_needed);
        //if (task_switch_needed)
            portYIELD_FROM_ISR(task_switch_needed);
            //vPortYieldFromISR();
    }
}

/* ============= */
/* == SIGNALS == */
/* ============= */

void * pico_signal_init(void)
{
    void * signal = pico_mutex_init();
    pico_mutex_lock(signal);
    return signal;
}

void pico_signal_deinit(void * signal)
{
    pico_mutex_deinit(signal);
}

void pico_signal_wait(void * signal)
{
    pico_signal_wait_timeout(signal, portMAX_DELAY);
}

int pico_signal_wait_timeout(void * signal, int timeout)
{
    return pico_mutex_lock_timeout(signal, timeout);
}

void pico_signal_send(void * signal)
{
    pico_mutex_unlock(signal);
}

void pico_signal_send_ISR(void * signal)
{
    pico_mutex_unlock_ISR(signal);
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

