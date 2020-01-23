#include <intrinsics.h>
#include <stdint.h>
#include "rtos.h"
#include <assert.h>

#define MAX_THREAD      (32 + 1)
OSThread * volatile OS_curr; /* pointer to the current thread */
OSThread * volatile OS_next; /* pointer to the next thread to execute */

OSThread *OS_thread[32 + 1]; /* array of threads started so far */
uint32_t OS_readySet; /* bitmask of threads that are ready to run */
uint32_t OS_delayedSet; /* bitmask of threads that are delayed */
#define LOG2(x) (32U - __CLZ(x))

OSThread idleThread;

void main_idleThread(void)
{
    while(1)
    {
        OS_onIdle();
    }
}

void OS_init(void *stkSto, uint32_t stkSize)
{
    /* System handler priority register 3 (SHPR3)
     * Address: 0xE000ED20
     * Reset value: 0x00000000
     * Required privilege: Privileged
     *
     * Bits31:24 PRI_15: Priority of system handler 15, SysTickexception
     * Bits23:16 PRI_14: Priority of system handler 14, PendSV
     * Bits15:0 Reserved, must be kept cleared
     */

   /* Set the PendSV interrupt priority to the lowest level */
    *(uint32_t volatile *)0xE000ED20 |= (0xFFU << 16);

    OSThread_start(&idleThread,
                   0U, /* idle thread priority*/
                   &main_idleThread,
                   stkSto, stkSize);
}

void OS_sched(void)
{
    /* OS_next = ... */
    if(OS_readySet == 0U) /* Idle condition? */
    {
        OS_next = OS_thread[0]; /* the idle thread */
    }
    else
    {
        OS_next = OS_thread[LOG2(OS_readySet)];
        assert(OS_next != (OSThread *)0U);
    }

    if(OS_next != OS_curr)
    {
        /* Change PendSV exception state to pending */
        *(uint32_t volatile *)0xE000ED04 = (1U << 28);
    }
}

void OS_run(void)
{
    /* callback to configure and start interrupts */
    OS_onStartup();

    __disable_interrupt();
    OS_sched();
    __enable_interrupt();

    /* the following code should never execute */
    assert(0);
}

void OS_tick(void)
{
    uint32_t workingSet = OS_delayedSet;

    while(workingSet != 0U)
    {
        OSThread *t = OS_thread[LOG2(workingSet)];
        uint32_t bit;
        assert ((t != (OSThread *)0U) && (t->timeout != 0U));

        bit = (1U << (t->prio - 1U));
        --t->timeout;
        if(t->timeout == 0U)
        {
            OS_readySet |= bit; /* insert to set */
            OS_delayedSet &= ~bit; /* remove from set */
        }
        workingSet &= ~bit; /* remove from working set */
    }
}

void OS_delay(uint32_t ticks)
{
    uint32_t bit;
    __disable_interrupt();

    /* never call OS_delay from the idleThread */
    assert(OS_curr != OS_thread[0]);

    OS_curr->timeout = ticks;
    bit = (1U << (OS_curr->prio - 1U));
    OS_readySet &= ~bit;
    OS_delayedSet |= bit;
    OS_sched();
    __enable_interrupt();
}

void OSThread_start(
    OSThread *me,
    uint8_t prio, /* thread priority*/
    OSThreadHandler threadHandler,
    void *stkSto, uint32_t stkSize)
{
     /* Provide top of stack pointer. Round down the stack top to the 8-byte boundary
     * NOTE: Arm Cortex-M stack grows down from hi -> low memory.
     */
    uint32_t *sp = (uint32_t *)((((uint32_t)stkSto + stkSize) / 8)*8);
    uint32_t *stk_limit;

    assert((prio < MAX_THREAD)
           && (OS_thread[prio] == (OSThread *)0U));

    /* fabricate Cortex-m ISR stack frame for blink_1 */
    *(--sp) = (1U << 24); /* xPSR set Thumb bit*/
    *(--sp) = (uint32_t)threadHandler; /* PC */
    *(--sp) = 0x00000014U; /* LR  */
    *(--sp) = 0x00000012U; /* R12 */
    *(--sp) = 0x00000003U; /* R3  */
    *(--sp) = 0x00000002U; /* R2  */
    *(--sp) = 0x00000001U; /* R1  */
    *(--sp) = 0x00000000U; /* R0  */
    /* additionally, fake registers R4-R11 */
    *(--sp) = 0x00000011U; /* R11  */
    *(--sp) = 0x00000010U; /* R10 */
    *(--sp) = 0x00000009U; /* R9  */
    *(--sp) = 0x00000008U; /* R8  */
    *(--sp) = 0x00000007U; /* R7  */
    *(--sp) = 0x00000006U; /* R6  */
    *(--sp) = 0x00000005U; /* R5  */
    *(--sp) = 0x00000004U; /* R4  */

    /* save the top of the stack in the thread's attribute */
    me->sp = sp;

    /* round up the bottom of the stack to the 8-byte boundary */
    stk_limit = (uint32_t *)(((((uint32_t)stkSto - 1U) / 8) + 1U)*8);

    /* pre-fill the unused part of the stack with 0xDEADBEEF */
    for(sp = sp - 1U; sp >= stk_limit; --sp)
    {
        *sp = 0xDEADBEEF;
    }

    /* register the thread with the OS */
    OS_thread[prio] = me;
    me->prio = prio;

    /* make the thread ready to run */
    if(prio > 0)
    {
        OS_readySet |= (1U << (prio - 1U));
    }
}

void PendSV_Handler(void)
{
__asm(
    /* __disable_interrupt(); */
    "CPSID     i\n"

    /*
    if(OS_curr != (OSThread *)0)
    {
    */
    "LDR.N     R2, =OS_curr\n"
    "LDR       R0, [R2]\n"
    "CMP       R0, #0\n"
    "BEQ.N     PendSV_restore\n"
    /*        push R4-R11 registers on the stack */
    "PUSH     {R4-R11}\n"
    /*        OS_curr->sp = sp; */
    "LDR       R0, [R2]\n"
    "STR       sp, [R0]\n"
    /*
    }
    */
"PendSV_restore:\n"
    /* sp = OS_next->sp; */
    "LDR.N     R3,=OS_next\n"
    "LDR       R0, [R3]\n"
    "LDR       sp, [R0]\n"
    /* OS_curr = OS_next; */
    "LDR       R3, [R3]\n"
    "STR       R3, [R2]\n"
    /* Pop registers R4-R11 */
    "POP       {R4-R11}\n"
    /* __enable_interrupt(); */
    "CPSIE     i\n"

    "BX        LR\n");
}

//void PendSV_Handler(void)
//{
//    void *sp; /* fake stack pointer */
//
//    __disable_interrupt();
//    if(OS_curr != (OSThread *)0)
//    {
//        /* push R4-R11 registers on the stack */
//        OS_curr->sp = sp;
//    }
//    sp = OS_next->sp;
//    OS_curr = OS_next;
//
//    /* Pop registers R4-R11 */
//    __enable_interrupt();
//}