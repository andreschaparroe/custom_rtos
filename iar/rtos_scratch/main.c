#include <stdint.h>
#include "stm32l4xx.h"
#include "bsp.h"

void main_blink_1(void);
void main_blink_2(void);

uint32_t stack_blink_1[40];
uint32_t *sp_blink_1 = &stack_blink_1[40];

uint32_t stack_blink_2[40];
uint32_t *sp_blink_2 = &stack_blink_2[40];

/* background code: sequential with blocking version */
int main (void)
{

    BSP_init();

    /* fabricate Cortex-m ISR stack frame for blink_1 */

    *(--sp_blink_1) = (1U << 24); /* xPSR set Thumb bit*/
    *(--sp_blink_1) = (uint32_t)&main_blink_1; /* PC */
    *(--sp_blink_1) = 0x14; /* LR  */
    *(--sp_blink_1) = 0x12; /* R12 */
    *(--sp_blink_1) = 0x03; /* R3  */
    *(--sp_blink_1) = 0x02; /* R2  */
    *(--sp_blink_1) = 0x01; /* R1  */
    *(--sp_blink_1) = 0x00; /* R0  */

    /* fabricate Cortex-m ISR stack frame for blink_2 */

    *(--sp_blink_2) = (1U << 24); /* xPSR set Thumb bit*/
    *(--sp_blink_2) = (uint32_t)&main_blink_2; /* PC */
    *(--sp_blink_2) = 0x14; /* LR  */
    *(--sp_blink_2) = 0x12; /* R12 */
    *(--sp_blink_2) = 0x03; /* R3  */
    *(--sp_blink_2) = 0x02; /* R2  */
    *(--sp_blink_2) = 0x01; /* R1  */
    *(--sp_blink_2) = 0x00; /* R0  */


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


