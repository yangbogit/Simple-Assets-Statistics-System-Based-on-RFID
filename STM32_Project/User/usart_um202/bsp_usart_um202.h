#ifndef __BSP_USART_UM202_H__
#define __BSP_USART_UM202_H__

#include "stm32f10x.h"
#include <stdio.h>

// 是否启用串口中断
  
# define USART_UM202_INTERRUPT          ENABLE
//# define USART_UM202_INTERRUPT          DISABLE

// 串口 1- USART 1 for UM202
#define  USART_UM202                    USART1
#define  USART_UM202_CLK                RCC_APB2Periph_USART1
#define  USART_UM202_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  USART_UM202_BAUDRATE           115200

// USART 时钟定义
#define  USART_UM202_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  USART_UM202_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
// USART 引脚定义
#define  USART_UM202_TX_GPIO_PORT       GPIOA   
#define  USART_UM202_TX_GPIO_PIN        GPIO_Pin_9
#define  USART_UM202_RX_GPIO_PORT       GPIOA
#define  USART_UM202_RX_GPIO_PIN        GPIO_Pin_10

// USART 中断定义
#define  USART_UM202_IRQ                USART1_IRQn
#define  USART_UM202_IRQHandler         USART1_IRQHandler

void USART_UM202_Config(void);
void Usart_UM202_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_UM202_Send_8_Bits( USART_TypeDef * pUSARTx, uint8_t data);
void Usart_UM202_Send_16_Bits( USART_TypeDef * pUSARTx, uint16_t data);
void Usart_UM202_Send_32_Bits( USART_TypeDef * pUSARTx, uint32_t data);

#endif /* __BSP_USART_UM202_H__ */
