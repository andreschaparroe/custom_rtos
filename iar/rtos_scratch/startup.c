#include "stm32l4xx.h"
#include "bsp.h"

/* Linker defined variable */
extern int CSTACK$$Limit;

/* Iar Library function */
extern void __iar_program_start(void);

/* Vector table based on STM32L475 MCU datasheet */
void Reset_Handler(void);
void NMI_Handler (void);
void HardFault_Handler (void);
void MemManage_Handler (void);
void BusFault_Handler (void);
void UsageFault_Handler (void);
void SVC_Handler (void);
void DebugMon_Handler (void);
void PendSV_Handler (void);
void SysTick_Handler (void);
void WWDG_IRQHandler (void);
void PVD_PVM_IRQHandler (void);
void TAMP_STAMP_IRQHandler (void);
void RTC_WKUP_IRQHandler (void);
void FLASH_IRQHandler (void);
void RCC_IRQHandler (void);
void EXTI0_IRQHandler (void);
void EXTI1_IRQHandler (void);
void EXTI2_IRQHandler (void);
void EXTI3_IRQHandler (void);
void EXTI4_IRQHandler (void);
void DMA1_Channel1_IRQHandler (void);
void DMA1_Channel2_IRQHandler (void);
void DMA1_Channel3_IRQHandler (void);
void DMA1_Channel4_IRQHandler (void);
void DMA1_Channel5_IRQHandler (void);
void DMA1_Channel6_IRQHandler (void);
void DMA1_Channel7_IRQHandler (void);
void ADC1_2_IRQHandler (void);
void CAN1_TX_IRQHandler (void);
void CAN1_RX0_IRQHandler (void);
void CAN1_RX1_IRQHandler (void);
void CAN1_SCE_IRQHandler (void);
void EXTI9_5_IRQHandler (void);
void TIM1_BRK_TIM15_IRQHandler (void);
void TIM1_UP_TIM16_IRQHandler (void);
void TIM1_TRG_COM_TIM17_IRQHandler (void);
void TIM1_CC_IRQHandler (void);
void TIM2_IRQHandler (void);
void TIM3_IRQHandler (void);
void TIM4_IRQHandler (void);
void I2C1_EV_IRQHandler (void);
void I2C1_ER_IRQHandler (void);
void I2C2_EV_IRQHandler (void);
void I2C2_ER_IRQHandler (void);
void SPI1_IRQHandler (void);
void SPI2_IRQHandler (void);
void USART1_IRQHandler (void);
void USART2_IRQHandler (void);
void USART3_IRQHandler (void);
void EXTI15_10_IRQHandler (void);
void RTC_Alarm_IRQHandler (void);
void DFSDM1_FLT3_IRQHandler (void);
void TIM8_BRK_IRQHandler (void);
void TIM8_UP_IRQHandler (void);
void TIM8_TRG_COM_IRQHandler (void);
void TIM8_CC_IRQHandler (void);
void FMC_IRQHandler (void);
void ADC3_IRQHandler (void);
void SDMMC1_IRQHandler (void);
void TIM5_IRQHandler (void);
void SPI3_IRQHandler (void);
void UART4_IRQHandler (void);
void UART5_IRQHandler (void);
void TIM6_DAC_IRQHandler (void);
void TIM7_IRQHandler (void);
void DMA2_Channel1_IRQHandler (void);
void DMA2_Channel2_IRQHandler (void);
void DMA2_Channel4_IRQHandler (void);
void DMA2_Channel3_IRQHandler (void);
void DMA2_Channel5_IRQHandler (void);
void DFSDM1_FLT0_IRQHandler (void);
void DFSDM1_FLT1_IRQHandler (void);
void DFSDM1_FLT2_IRQHandler (void);
void COMP_IRQHandler (void);
void LPTIM1_IRQHandler (void);
void LPTIM2_IRQHandler (void);
void OTG_FS_IRQHandler (void);
void DMA2_Channel6_IRQHandler (void);
void DMA2_Channel7_IRQHandler (void);
void LPUART1_IRQHandler (void);
void QUADSPI_IRQHandler (void);
void I2C3_EV_IRQHandler (void);
void I2C3_ER_IRQHandler (void);
void SAI1_IRQHandler (void);
void SAI2_IRQHandler (void);
void SWPMI1_IRQHandler (void);
void TSC_IRQHandler (void);
void RNG_IRQHandler (void);
void FPU_IRQHandler (void);

void unused_handler (void);

void (* const __vector_table[])(void) @ ".intvec" =
{
        (void(*)(void))&CSTACK$$Limit,
        Reset_Handler, /* Reset_Handler,*/
        NMI_Handler,
        HardFault_Handler,
        MemManage_Handler,
        BusFault_Handler,
        UsageFault_Handler,
        0,
        0,
        0,
        0,
        SVC_Handler,
        DebugMon_Handler,
        0,
        PendSV_Handler,
        SysTick_Handler,
        WWDG_IRQHandler         ,   /* Window WatchDog */
        PVD_PVM_IRQHandler      ,   /* PVD/PVM1/PVM2/PVM3/PVM4 through EXTI Line detection */
        TAMP_STAMP_IRQHandler   ,   /* Tamper and TimeStamps through the EXTI line */
        RTC_WKUP_IRQHandler     ,   /* RTC Wakeup through the EXTI line */
        FLASH_IRQHandler        ,   /* FLASH */
        RCC_IRQHandler          ,   /* RCC */
        EXTI0_IRQHandler        ,   /* EXTI Line0 */
        EXTI1_IRQHandler        ,   /* EXTI Line1 */
        EXTI2_IRQHandler        ,   /* EXTI Line2 */
        EXTI3_IRQHandler        ,   /* EXTI Line3 */
        EXTI4_IRQHandler        ,   /* EXTI Line4 */
        DMA1_Channel1_IRQHandler,   /* DMA1 Channel 1 */
        DMA1_Channel2_IRQHandler,   /* DMA1 Channel 2 */
        DMA1_Channel3_IRQHandler,   /* DMA1 Channel 3 */
        DMA1_Channel4_IRQHandler,   /* DMA1 Channel 4 */
        DMA1_Channel5_IRQHandler,   /* DMA1 Channel 5 */
        DMA1_Channel6_IRQHandler,   /* DMA1 Channel 6 */
        DMA1_Channel7_IRQHandler,   /* DMA1 Channel 7 */
        ADC1_2_IRQHandler       ,   /* ADC1, ADC2 */
        CAN1_TX_IRQHandler      ,   /* CAN1 TX */
        CAN1_RX0_IRQHandler     ,   /* CAN1 RX0 */
        CAN1_RX1_IRQHandler     ,   /* CAN1 RX1 */
        CAN1_SCE_IRQHandler     ,   /* CAN1 SCE */
        EXTI9_5_IRQHandler      ,   /* External Line[9:5]s */
        TIM1_BRK_TIM15_IRQHandler,   /* TIM1 Break and TIM15 */
        TIM1_UP_TIM16_IRQHandler,   /* TIM1 Update and TIM16 */
        TIM1_TRG_COM_TIM17_IRQHandler,   /* TIM1 Trigger and Commutation and TIM17 */
        TIM1_CC_IRQHandler      ,   /* TIM1 Capture Compare */
        TIM2_IRQHandler         ,   /* TIM2 */
        TIM3_IRQHandler         ,   /* TIM3 */
        TIM4_IRQHandler         ,   /* TIM4 */
        I2C1_EV_IRQHandler      ,   /* I2C1 Event */
        I2C1_ER_IRQHandler      ,   /* I2C1 Error */
        I2C2_EV_IRQHandler      ,   /* I2C2 Event */
        I2C2_ER_IRQHandler      ,   /* I2C2 Error */
        SPI1_IRQHandler         ,   /* SPI1 */
        SPI2_IRQHandler         ,   /* SPI2 */
        USART1_IRQHandler       ,   /* USART1 */
        USART2_IRQHandler       ,   /* USART2 */
        USART3_IRQHandler       ,   /* USART3 */
        EXTI15_10_IRQHandler    ,   /* External Line[15:10] */
        RTC_Alarm_IRQHandler    ,   /* RTC Alarm (A and B) through EXTI Line */
        DFSDM1_FLT3_IRQHandler  ,   /* DFSDM1 Filter 3 global Interrupt */
        TIM8_BRK_IRQHandler     ,   /* TIM8 Break Interrupt */
        TIM8_UP_IRQHandler      ,   /* TIM8 Update Interrupt */
        TIM8_TRG_COM_IRQHandler ,   /* TIM8 Trigger and Commutation Interrupt */
        TIM8_CC_IRQHandler      ,   /* TIM8 Capture Compare Interrupt */
        ADC3_IRQHandler         ,   /* ADC3 global  Interrupt */
        FMC_IRQHandler          ,   /* FMC */
        SDMMC1_IRQHandler       ,   /* SDMMC1 */
        TIM5_IRQHandler         ,   /* TIM5 */
        SPI3_IRQHandler         ,   /* SPI3 */
        UART4_IRQHandler        ,   /* UART4 */
        UART5_IRQHandler        ,   /* UART5 */
        TIM6_DAC_IRQHandler     ,   /* TIM6 and DAC1&2 underrun errors */
        TIM7_IRQHandler         ,   /* TIM7 */
        DMA2_Channel1_IRQHandler,   /* DMA2 Channel 1 */
        DMA2_Channel2_IRQHandler,   /* DMA2 Channel 2 */
        DMA2_Channel3_IRQHandler,   /* DMA2 Channel 3 */
        DMA2_Channel4_IRQHandler,   /* DMA2 Channel 4 */
        DMA2_Channel5_IRQHandler,   /* DMA2 Channel 5 */
        DFSDM1_FLT0_IRQHandler  ,   /* DFSDM1 Filter 0 global Interrupt */
        DFSDM1_FLT1_IRQHandler  ,   /* DFSDM1 Filter 1 global Interrupt */
        DFSDM1_FLT2_IRQHandler  ,   /* DFSDM1 Filter 2 global Interrupt */
        COMP_IRQHandler         ,   /* COMP Interrupt */
        LPTIM1_IRQHandler       ,   /* LP TIM1 interrupt */
        LPTIM2_IRQHandler       ,   /* LP TIM2 interrupt */
        OTG_FS_IRQHandler       ,   /* USB OTG FS */
        DMA2_Channel6_IRQHandler,   /* DMA2 Channel 6 */
        DMA2_Channel7_IRQHandler,   /* DMA2 Channel 7 */
        LPUART1_IRQHandler      ,   /* LP UART 1 interrupt */
        QUADSPI_IRQHandler      ,   /* Quad SPI global interrupt */
        I2C3_EV_IRQHandler      ,   /* I2C3 event */
        I2C3_ER_IRQHandler      ,   /* I2C3 error */
        SAI1_IRQHandler         ,   /* Serial Audio Interface 1 global interrupt */
        SAI2_IRQHandler         ,   /* Serial Audio Interface 2 global interrupt */
        SWPMI1_IRQHandler       ,   /* Serial Wire Interface global interrupt */
        TSC_IRQHandler          ,   /* Touch Sense Controller global interrupt */
        0                       ,   /* Reserved         */
        0                       ,   /* Reserved         */
        RNG_IRQHandler          ,   /* RNG global interrupt */
        FPU_IRQHandler          ,   /* FPU */
};


__stackless void Reset_Handler(void)
{
    __iar_program_start();
}

__stackless void unused_handler (void)
{

    /* error handling*/
    asser_failed("unused_handler", __LINE__);

}

__weak void SysTick_Handler(void)
{

}


__weak void EXTI0_IRQHandler(void)
{
    while(1);
}


//#pragma weak Reset_Handler = __iar_program_start
#pragma weak NMI_Handler = unused_handler
#pragma weak HardFault_Handler = unused_handler
#pragma weak MemManage_Handler = unused_handler
#pragma weak BusFault_Handler = unused_handler
#pragma weak UsageFault_Handler = unused_handler
#pragma weak SVC_Handler = unused_handler
#pragma weak DebugMon_Handler = unused_handler
#pragma weak PendSV_Handler = unused_handler
//#pragma weak SysTick_Handler = unused_handler
#pragma weak WWDG_IRQHandler = unused_handler
#pragma weak PVD_PVM_IRQHandler = unused_handler
#pragma weak TAMP_STAMP_IRQHandler = unused_handler
#pragma weak RTC_WKUP_IRQHandler = unused_handler
#pragma weak FLASH_IRQHandler = unused_handler
#pragma weak RCC_IRQHandler = unused_handler
//#pragma weak EXTI0_IRQHandler = unused_handler
#pragma weak EXTI1_IRQHandler = unused_handler
#pragma weak EXTI2_IRQHandler = unused_handler
#pragma weak EXTI3_IRQHandler = unused_handler
#pragma weak EXTI4_IRQHandler = unused_handler
#pragma weak DMA1_Channel1_IRQHandler = unused_handler
#pragma weak DMA1_Channel2_IRQHandler = unused_handler
#pragma weak DMA1_Channel3_IRQHandler = unused_handler
#pragma weak DMA1_Channel4_IRQHandler = unused_handler
#pragma weak DMA1_Channel5_IRQHandler = unused_handler
#pragma weak DMA1_Channel6_IRQHandler = unused_handler
#pragma weak DMA1_Channel7_IRQHandler = unused_handler
#pragma weak ADC1_2_IRQHandler = unused_handler
#pragma weak CAN1_TX_IRQHandler = unused_handler
#pragma weak CAN1_RX0_IRQHandler = unused_handler
#pragma weak CAN1_RX1_IRQHandler = unused_handler
#pragma weak CAN1_SCE_IRQHandler = unused_handler
#pragma weak EXTI9_5_IRQHandler = unused_handler
#pragma weak TIM1_BRK_TIM15_IRQHandler = unused_handler
#pragma weak TIM1_UP_TIM16_IRQHandler = unused_handler
#pragma weak TIM1_TRG_COM_TIM17_IRQHandler = unused_handler
#pragma weak TIM1_CC_IRQHandler = unused_handler
#pragma weak TIM2_IRQHandler = unused_handler
#pragma weak TIM3_IRQHandler = unused_handler
#pragma weak TIM4_IRQHandler = unused_handler
#pragma weak I2C1_EV_IRQHandler = unused_handler
#pragma weak I2C1_ER_IRQHandler = unused_handler
#pragma weak I2C2_EV_IRQHandler = unused_handler
#pragma weak I2C2_ER_IRQHandler = unused_handler
#pragma weak SPI1_IRQHandler = unused_handler
#pragma weak SPI2_IRQHandler = unused_handler
#pragma weak USART1_IRQHandler = unused_handler
#pragma weak USART2_IRQHandler = unused_handler
#pragma weak USART3_IRQHandler = unused_handler
#pragma weak EXTI15_10_IRQHandler = unused_handler
#pragma weak RTC_Alarm_IRQHandler = unused_handler
#pragma weak DFSDM1_FLT3_IRQHandler = unused_handler
#pragma weak TIM8_BRK_IRQHandler = unused_handler
#pragma weak TIM8_UP_IRQHandler = unused_handler
#pragma weak TIM8_TRG_COM_IRQHandler = unused_handler
#pragma weak TIM8_CC_IRQHandler = unused_handler
#pragma weak FMC_IRQHandler = unused_handler
#pragma weak ADC3_IRQHandler = unused_handler
#pragma weak SDMMC1_IRQHandler = unused_handler
#pragma weak TIM5_IRQHandler = unused_handler
#pragma weak SPI3_IRQHandler = unused_handler
#pragma weak UART4_IRQHandler = unused_handler
#pragma weak UART5_IRQHandler = unused_handler
#pragma weak TIM6_DAC_IRQHandler = unused_handler
#pragma weak TIM7_IRQHandler = unused_handler
#pragma weak DMA2_Channel1_IRQHandler = unused_handler
#pragma weak DMA2_Channel2_IRQHandler = unused_handler
#pragma weak DMA2_Channel4_IRQHandler = unused_handler
#pragma weak DMA2_Channel3_IRQHandler = unused_handler
#pragma weak DMA2_Channel5_IRQHandler = unused_handler
#pragma weak DFSDM1_FLT0_IRQHandler = unused_handler
#pragma weak DFSDM1_FLT1_IRQHandler = unused_handler
#pragma weak DFSDM1_FLT2_IRQHandler = unused_handler
#pragma weak COMP_IRQHandler = unused_handler
#pragma weak LPTIM1_IRQHandler = unused_handler
#pragma weak LPTIM2_IRQHandler = unused_handler
#pragma weak OTG_FS_IRQHandler = unused_handler
#pragma weak DMA2_Channel6_IRQHandler = unused_handler
#pragma weak DMA2_Channel7_IRQHandler = unused_handler
#pragma weak LPUART1_IRQHandler = unused_handler
#pragma weak QUADSPI_IRQHandler = unused_handler
#pragma weak I2C3_EV_IRQHandler = unused_handler
#pragma weak I2C3_ER_IRQHandler = unused_handler
#pragma weak SAI1_IRQHandler = unused_handler
#pragma weak SAI2_IRQHandler = unused_handler
#pragma weak SWPMI1_IRQHandler = unused_handler
#pragma weak TSC_IRQHandler = unused_handler
#pragma weak RNG_IRQHandler = unused_handler
#pragma weak FPU_IRQHandler = unused_handler

