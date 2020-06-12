#include "bsp_usart_zigbee.h"

static void USART_Zigbee_NVIC_Configuration(void)
{
    NVIC_InitTypeDef  NVIC_InitStructure;
    
    // 嵌套向量中断控制器组选择组2
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    // 选择中断源 USART
    NVIC_InitStructure.NVIC_IRQChannel = USART_Zigbee_IRQ;
    
    // 抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    
    // 子优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    // 使能中断
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // 初始化配置 NVIC
    NVIC_Init(&NVIC_InitStructure);
    
}

void USART_Zigbee_Config(void)
{
    GPIO_InitTypeDef    GPIO_InitStructure;
    USART_InitTypeDef   USART_InitStructure;

    // 打开对应 GPIO 时钟
    USART_Zigbee_GPIO_APBxClkCmd(USART_Zigbee_GPIO_CLK, ENABLE);
    
    // 打开对应 USART 时钟
    USART_Zigbee_APBxClkCmd(USART_Zigbee_CLK, ENABLE);
    
    // 设置 USART TX 引脚模式
    GPIO_InitStructure.GPIO_Pin = USART_Zigbee_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART_Zigbee_TX_GPIO_PORT, &GPIO_InitStructure);
    
    
    // 设置 USART RX 引脚模式
    GPIO_InitStructure.GPIO_Pin = USART_Zigbee_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART_Zigbee_RX_GPIO_PORT, &GPIO_InitStructure);
    
    // 配置 USART 模式
    // 波特率
    USART_InitStructure.USART_BaudRate = USART_Zigbee_BAUDRATE;
    
    // 数据位长度
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    
    // 一位停止位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    
    // 无奇偶校验
    USART_InitStructure.USART_Parity = USART_Parity_No;
    
    // 无硬件控制流
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    
    // 收发模式
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART_Zigbee, &USART_InitStructure);
    
    // 如果串口要使用中断
    if(USART_Zigbee_INTERRUPT)
    {
        // 串口中断优先级配置
        USART_Zigbee_NVIC_Configuration();
    
        // 使能串口接收中断
        USART_ITConfig(USART_Zigbee, USART_IT_RXNE, ENABLE);
    }
    
    // 使能串口
    USART_Cmd(USART_Zigbee, ENABLE);
}

void Usart_Zigbee_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx,ch);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

void Usart_Zigbee_Send_8_Bits( USART_TypeDef * pUSARTx, uint8_t data)
{
    USART_SendData(pUSARTx, data);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}
void Usart_Zigbee_Send_16_Bits( USART_TypeDef * pUSARTx, uint16_t data)
{
	uint8_t temp_h, temp_l;
	
	temp_h = (data&0XFF00)>>8;
	temp_l = data&0XFF;
	
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

void Usart_Zigbee_Send_32_Bits( USART_TypeDef * pUSARTx, uint32_t data)
{
    uint16_t temp_h16;
    uint16_t temp_l16;
    temp_h16 = data>>16;
    temp_l16 = data&0xFFFF;
    Usart_Zigbee_Send_16_Bits(pUSARTx, temp_h16);
    Usart_Zigbee_Send_16_Bits(pUSARTx, temp_l16);
}


