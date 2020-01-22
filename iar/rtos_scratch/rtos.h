#ifndef __RTOS_H__
#define __RTOS_H__

/* Tread Control Block (TCB) */
typedef struct
{
    void *sp;           /* stack pointer*/
    uint32_t timeout;   /* timeout delay down-counter */

    /* other attributes associated with a thread */
}OSThread;

typedef void (*OSThreadHandler)();

void OS_init(void *stkSto, uint32_t stkSize);

/* callback to handle the idle condition */
void OS_onIdle(void);

/* this function must be called with interrupts DISABLED */
void OS_sched(void);

/* transfer control to the RTOS to run the threads */
void OS_run(void);

/* blocking delay */
void OS_delay(uint32_t ticks);

/* process all timeouts */
void OS_tick(void);

/* callback to configure and start interrupts */
void OS_onStartup(void);

void OSThread_start(
    OSThread *me,
    OSThreadHandler threadHandler,
    void *stkSto, uint32_t stkSize);

#endif /* __RTOS_H__ */