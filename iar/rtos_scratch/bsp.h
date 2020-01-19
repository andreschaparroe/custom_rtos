#ifndef __BSP_H__
#define __BSP_H_


#define SYSTEM_CLOCK    (4000000U)

#define LED1_PIN        (5U)
#define LED2_PIN        (14U)
#define LED1_PORT       (GPIOA)
#define LED2_PORT       (GPIOB)

void BSP_init(void);
void BSP_delay(uint32_t ticks);
uint32_t BSP_getTick(void);
void BSP_ledOneOn(void);
void BSP_ledOneOff(void);
void BSP_ledTwoOn(void);
void BSP_ledTwoOff(void);

void asser_failed(char const * file , int line);

#endif /* __BSP_H__ */
