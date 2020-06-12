#ifndef __BSP_USART_SCREEN_H__
#define __BSP_USART_SCREEN_H__

#include "stm32f10x.h"
#include <stdio.h>

// 是否启用串口中断
  
//# define USART_Screen_INTERRUPT          ENABLE
# define USART_Screen_INTERRUPT          DISABLE

// 串口 2- USART 2 for Screen
#define  USART_Screen                    USART2
#define  USART_Screen_CLK                RCC_APB1Periph_USART2
#define  USART_Screen_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  USART_Screen_BAUDRATE           115200

// USART 时钟定义
#define  USART_Screen_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  USART_Screen_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
// USART 引脚定义
#define  USART_Screen_TX_GPIO_PORT       GPIOA   
#define  USART_Screen_TX_GPIO_PIN        GPIO_Pin_2
#define  USART_Screen_RX_GPIO_PORT       GPIOA
#define  USART_Screen_RX_GPIO_PIN        GPIO_Pin_3

// USART 中断定义
#define  USART_Screen_IRQ                USART2_IRQn
#define  USART_Screen_IRQHandler         USART2_IRQHandler

void USART_Screen_Config(void);
void Usart_Screen_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_Screen_Send_8_Bits( USART_TypeDef * pUSARTx, uint8_t data);
void Usart_Screen_Send_16_Bits( USART_TypeDef * pUSARTx, uint16_t data);
void Usart_Screen_Send_32_Bits( USART_TypeDef * pUSARTx, uint32_t data);

#endif /* __BSP_USART_SCREEN_H__ */
