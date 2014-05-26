/* Pthread osal implementation, for testing purposes */
#include <pthread.h>
#include "pico_defines.h"
#include "pico_stack.h"
#include <semaphore.h>


void * pico_mutex_init(void) {
    pthread_mutex_t *mutex = pico_zalloc(sizeof(pthread_mutex_t));
    if (!mutex)
        return NULL;
    if (pthread_mutex_init(mutex, NULL) == 0 )
        return mutex;
    pico_free(mutex);
    return NULL;
}
void pico_mutex_deinit(void * mutex)
{
    pthread_mutex_destroy((pthread_mutex_t *)mutex);
    pico_free(mutex);
}

void pico_mutex_lock(void * mutex)
{
    pthread_mutex_lock((pthread_mutex_t *)mutex);
}
void pico_mutex_unlock(void * mutex)
{
    pthread_mutex_unlock((pthread_mutex_t *)mutex);
}


void * pico_signal_init(void)
{
    sem_t *sem = pico_zalloc(sizeof(pthread_mutex_t));
    if (!sem)
        return NULL;
    if (sem_init(sem, 0, 1) == 0)
        return sem;
    pico_free(sem);
    return NULL; 
}
void pico_signal_deinit(void * signal)
{
    sem_destroy((sem_t *) signal);
}
void pico_signal_wait(void * signal)
{
    sem_wait((sem_t *) signal);
}
void pico_signal_send(void * signal)
{
    sem_post((sem_t *) signal);
}

