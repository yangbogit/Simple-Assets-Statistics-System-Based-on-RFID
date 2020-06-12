#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f10x.h"

// R
#define LED_R_GPIO_PORT GPIOB
#define LED_R_GPIO_CLK  RCC_APB2Periph_GPIOB
#define LED_R_GPIO_PIN  GPIO_Pin_5

// G
#define LED_G_GPIO_PORT GPIOB
#define LED_G_GPIO_CLK  RCC_APB2Periph_GPIOB
#define LED_G_GPIO_PIN  GPIO_Pin_0

// B
#define LED_B_GPIO_PORT GPIOB
#define LED_B_GPIO_CLK  RCC_APB2Periph_GPIOB
#define LED_B_GPIO_PIN  GPIO_Pin_1

#define digitalHi(p, i) {p->BSRR = i;}
#define digitalLo(p, i) {p->BRR = i;}
#define digitalToggle(p, i) {p->ODR ^= i;} // 异或

/* 定义控制IO的宏 */
#define LED_R_TOGGLE		   digitalToggle(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LED_R_OFF		   digitalHi(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LED_R_ON			   digitalLo(LED_R_GPIO_PORT,LED_R_GPIO_PIN)

#define LED_G_TOGGLE		   digitalToggle(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LED_G_OFF		   digitalHi(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LED_G_ON			   digitalLo(LED_G_GPIO_PORT,LED_G_GPIO_PIN)

#define LED_B_TOGGLE		   digitalToggle(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LED_B_OFF		   digitalHi(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LED_B_ON			   digitalLo(LED_B_GPIO_PORT,LED_B_GPIO_PIN)

void LED_GPIO_Config(void);

#endif /* __BSP_LED_H__ */
