#ifndef __BSP_USART_ZIGBEE_H__
#define __BSP_USART_ZIGBEE_H__

#include "stm32f10x.h"
#include <stdio.h>

// 是否启用串口中断
  
//# define USART_Zigbee_INTERRUPT          ENABLE   
# define USART_Zigbee_INTERRUPT          DISABLE 

// 串口 3- USART 3 for Zigbee
#define  USART_Zigbee                    USART3
#define  USART_Zigbee_CLK                RCC_APB1Periph_USART3
#define  USART_Zigbee_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  USART_Zigbee_BAUDRATE           115200

// USART 时钟定义
#define  USART_Zigbee_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  USART_Zigbee_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
// USART 引脚定义
#define  USART_Zigbee_TX_GPIO_PORT       GPIOB   
#define  USART_Zigbee_TX_GPIO_PIN        GPIO_Pin_10
#define  USART_Zigbee_RX_GPIO_PORT       GPIOB
#define  USART_Zigbee_RX_GPIO_PIN        GPIO_Pin_11

// USART 中断定义
#define  USART_Zigbee_IRQ                USART3_IRQn
#define  USART_Zigbee_IRQHandler         USART3_IRQHandler

void USART_Zigbee_Config(void);
void Usart_Zigbee_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_Zigbee_Send_8_Bits( USART_TypeDef * pUSARTx, uint8_t data);
void Usart_Zigbee_Send_16_Bits( USART_TypeDef * pUSARTx, uint16_t data);
void Usart_Zigbee_Send_32_Bits( USART_TypeDef * pUSARTx, uint32_t data);

#endif /* __BSP_USART_ZIGBEE_H__ */
