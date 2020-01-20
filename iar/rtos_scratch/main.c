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

/* background code: sequential with blocking version */
int main (void)
{

    BSP_init();
    OS_init();

    OSThread_start(&blink_1,
                   &main_blink_1,
                   stack_blink_1, sizeof(stack_blink_1));

    OSThread_start(&blink_2,
                   &main_blink_2,
                   stack_blink_2, sizeof(stack_blink_2));

    while(1)
    {

    }
//    return 0;
}

void main_blink_1(void)
{
    while(1)
    {
        BSP_ledOneOn();
        BSP_delay(2);
        BSP_ledOneOff();
        BSP_delay(2);
    }
}

void main_blink_2(void)
{
    while(1)
    {
        BSP_ledTwoOn();
        BSP_delay(2);
        BSP_ledTwoOff();
        BSP_delay(2);
    }
}


