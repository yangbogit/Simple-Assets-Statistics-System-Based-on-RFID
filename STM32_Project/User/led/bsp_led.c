#include "bsp_led.h"
/*
***************************************************************************
*	函 数 名: LED_GPIO_Config
*	功能说明: LED灯引脚配置
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
void LED_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(LED_R_GPIO_CLK | LED_G_GPIO_CLK | LED_B_GPIO_CLK, ENABLE);
    
    // R
    GPIO_InitStructure.GPIO_Pin = LED_R_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStructure);
    
    // G
    GPIO_InitStructure.GPIO_Pin = LED_G_GPIO_PIN;
    GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStructure);

    // B
    GPIO_InitStructure.GPIO_Pin = LED_B_GPIO_PIN;
    GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStructure);
    
    // Close LED
    GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);
    GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
    GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
}

