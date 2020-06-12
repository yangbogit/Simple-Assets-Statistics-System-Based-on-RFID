#ifndef __BSP_SYSTICK_H__
#define __BSP_SYSTICK_H__


#include "stm32f10x.h"

void SysTick_Init(void);

// nTime: Delay_us( 1 ) 则实现的延时为 1 * 10us = 10us
void Delay_us(__IO u32 nTime);
#define Delay_ms(x)     Delay_us(100*x)

void SysTick_Delay_Us(__IO uint32_t us);
void SysTick_Delay_Ms(__IO uint32_t ms);


#endif /* __BSP_SYSTICK_H__ */


