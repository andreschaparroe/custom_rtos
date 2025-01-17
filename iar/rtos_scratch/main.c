#include <stdint.h>
#include "stm32l4xx.h"
#include "bsp.h"
#include "rtos.h"

void main_blink_1(void);
void main_blink_2(void);

uint32_t stack_blink_1[40];
OSThread blink_1;

uint32_t stack_blink_2[40];
OSThread blink_2;

uint32_t stack_idleThread[40];

/* background code: sequential with blocking version */
int main (void)
{

    OS_init(stack_idleThread, sizeof(stack_idleThread));

    OSThread_start(&blink_1,
                   5U, /* thread priority*/
                   &main_blink_1,
                   stack_blink_1, sizeof(stack_blink_1));

    OSThread_start(&blink_2,
                   2U, /* thread priority*/
                   &main_blink_2,
                   stack_blink_2, sizeof(stack_blink_2));

    OS_run();
//    return 0;
}

void main_blink_1(void)
{
    while(1)
    {
        BSP_ledOneOn();
        OS_delay(1);
        BSP_ledOneOff();
        OS_delay(1);
    }
}

void main_blink_2(void)
{
    while(1)
    {
        BSP_ledTwoOn();
        OS_delay(1);
        BSP_ledTwoOff();
        OS_delay(1);
    }
}


