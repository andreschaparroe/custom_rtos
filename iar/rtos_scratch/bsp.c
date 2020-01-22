#include <intrinsics.h>
#include "stm32l4xx.h"
#include "bsp.h"
#include "rtos.h"


void systick_init(void);
void gpio_init(void);
void gpio_set(GPIO_TypeDef * port, uint32_t pin);
void gpio_reset(GPIO_TypeDef * port, uint32_t pin);

static uint32_t volatile l_tickCtr;

void BSP_init(void)
{
    gpio_init();
    systick_init();
}

void BSP_ledOneOn(void)
{
    gpio_set(LED1_PORT,LED1_PIN);
}

void BSP_ledOneOff(void)
{
    gpio_reset(LED1_PORT,LED1_PIN);
}

void BSP_ledTwoOn(void)
{
    gpio_set(LED2_PORT,LED2_PIN);
}

void BSP_ledTwoOff(void)
{
    gpio_reset(LED2_PORT,LED2_PIN);
}

void systick_init(void)
{
    SysTick->LOAD = SYSTEM_CLOCK/2U - 1;
    SysTick->CTRL = (1U << SysTick_CTRL_CLKSOURCE_Pos)
                  | (1U << SysTick_CTRL_ENABLE_Pos)
                  | (1U << SysTick_CTRL_TICKINT_Pos);
    SysTick->VAL = 0U;

    /* Set the sysTick interrupt priority (highest) */
    NVIC_SetPriority(SysTick_IRQn, 0U);
}

void SysTick_Handler(void)
{
    OS_tick();

    __disable_interrupt();
    OS_sched();
    __enable_interrupt();
}

void gpio_init(void)
{
    /* Enable RCC GPIOA and GPIOB clock */
    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN);

    /* Set as outpts */
    GPIOA->MODER &= ~(GPIO_MODER_MODE5_Msk);
    GPIOA->MODER |= GPIO_MODER_MODE5_0;

    GPIOB->MODER &= ~(GPIO_MODER_MODE14_Msk);
    GPIOB->MODER |= GPIO_MODER_MODE14_0;

    /* Set as high speed */
    GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED5_Msk);
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5;
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED14;

    /* Config as pull-down */
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5_Msk);
    GPIOA->PUPDR |= GPIO_PUPDR_PUPD5_1;
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD14_Msk);
    GPIOB->PUPDR |= GPIO_PUPDR_PUPD14_1;

    /* Reset pins */
    gpio_reset(LED1_PORT, LED1_PIN);
    gpio_reset(LED2_PORT, LED2_PIN);

}

void gpio_set(GPIO_TypeDef * port, uint32_t pin)
{
    port->BSRR = (1U << (GPIO_BSRR_BS0_Pos + pin));
}

void gpio_reset(GPIO_TypeDef * port, uint32_t pin)
{
    port->BSRR = (1U << (GPIO_BSRR_BR0_Pos + pin));
}

void OS_onStartup(void)
{
    __asm(" CPSID i"); /*__disable_interrupt();*/
    BSP_init();

//    __asm(" CPSIE i"); /*__enable_interrupt();*/
}

void OS_onIdle(void)
{
    __WFI();
}

/* @brief Error handling
*/
__stackless void asser_failed(char const * file , int line)
{
    NVIC_SystemReset();
}
