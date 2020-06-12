#ifndef __BSP_CMD_INFO_PROCESS_H__
#define __BSP_CMD_INFO_PROCESS_H__

#include <stdlib.h>
#include <string.h>
#include "stm32f10x.h"
#include "bsp_usart_screen.h"
#include "bsp_usart_zigbee.h"

// 最大计数值(查询次数) uint8_t max = 255
#define EPC_String_Count_Max     255

#define DATA_BYTE_LENGTH          22        // UM202 发过来数据共有22个字节
#define EPC_INFO_LENGTH           20        // EPC 数据有效信息长度
#define FRAME_TAIL_LENGTH         2         // 帧尾长度

/* 各类命令 */
#define SCREEN_HEAD              0xEE        // 屏幕帧头
#define SCREEN_TAIL              0xFFFCFFFF  // 屏幕帧尾
#define SCREEN_SWITCH            0xB100      // 屏幕切换到数据记录页面命令
#define SCREEN_DATA_ADD          0xB152      // 增加数据记录命令
#define SCREEN_DATA_CLEAR        0xB153      // 清除历史数据记录命令
#define SCREEN_WRITE_TEXT        0xB110      // 写文本命令
#define SCREEN_DATA_MODIFY       0xB157      // 修改数据记录命令
#define SCREEN_DATA_SPLIT        0x3B        // 数据记录之间的分号
#define SCREEN_FRAME_ID          0x0001      // 画面 ID
#define SCREEN_WIDGET_1_ID       0x0001      // 数据记录控件 ID
#define SCREEN_WIDGET_2_ID       0x0002      // 数据记录控件 ID
#define SCREEN_TEXT_TOTAL_ID     0x0003      // 文本控件 ID 3
#define SCREEN_TEXT_Online_ID    0x0004      // 文本控件 ID 4
#define SCREEN_TEXT_Offline_ID   0x0005      // 文本控件 ID 5
#define SCREEN_BUZZER            0x610E      // 屏幕蜂鸣器 EE【 61 Time 】FF FC FF FF 参数说明： Time (1 个字节): 蜂鸣器讯响的时间，单位 10ms

#define Send_Head()              Usart_Screen_Send_8_Bits(USART_Screen, SCREEN_HEAD)
#define Send_Tail()              Usart_Screen_Send_32_Bits(USART_Screen, SCREEN_TAIL)
#define Send_Data_Clear()        Usart_Screen_Send_16_Bits(USART_Screen, SCREEN_DATA_CLEAR)
#define Send_Write_Text()        Usart_Screen_Send_16_Bits(USART_Screen, SCREEN_WRITE_TEXT)
#define Send_Screen_Switch()     Usart_Screen_Send_16_Bits(USART_Screen, SCREEN_SWITCH)
#define Send_Text_Total_ID()     Usart_Screen_Send_16_Bits(USART_Screen, SCREEN_TEXT_TOTAL_ID)
#define Send_Text_Online_ID()    Usart_Screen_Send_16_Bits(USART_Screen, SCREEN_TEXT_Online_ID)
#define Send_Text_Offline_ID()   Usart_Screen_Send_16_Bits(USART_Screen, SCREEN_TEXT_Offline_ID)
#define Send_Data_Add()          Usart_Screen_Send_16_Bits(USART_Screen, SCREEN_DATA_ADD)
#define Send_Data_Modify()       Usart_Screen_Send_16_Bits(USART_Screen, SCREEN_DATA_MODIFY)
#define Send_Frame_ID()          Usart_Screen_Send_16_Bits(USART_Screen, SCREEN_FRAME_ID)
#define Send_Widget_1_ID()       Usart_Screen_Send_16_Bits(USART_Screen, SCREEN_WIDGET_1_ID )
#define Send_Widget_2_ID()       Usart_Screen_Send_16_Bits(USART_Screen, SCREEN_WIDGET_2_ID )
#define Send_Data_Split()        Usart_Screen_Send_8_Bits(USART_Screen, SCREEN_DATA_SPLIT)
#define Send_Screen_Buzzer()     Usart_Screen_Send_16_Bits(USART_Screen, SCREEN_BUZZER)

typedef struct EPC_Node{
    uint8_t  EPC_String_Count;                 // 相同 EPC 信息的发送次数  
    char     EPC_String[DATA_BYTE_LENGTH];     // 数据发送记录
    struct   EPC_Node *next;
}EPC_Node, *Data_Send_Record_Type;

Data_Send_Record_Type Create_Data_Send_Record_LinkList(void);
Data_Send_Record_Type Create_Data_Send_Record_Node(void);
Data_Send_Record_Type EPC_Info_Is_Exist(char *data_string, Data_Send_Record_Type Data_Send_Record_LinkList);

void Screen_Init(void);
void Send_Total_EPC_Num(void);
void Send_Number(uint8_t temp);
void Send_Online_EPC_Num(uint8_t count);
void Send_Offline_EPC_Num(uint8_t count);

void Screen_Data_Add(char *data_string, Data_Send_Record_Type Data_Send_Record_LinkList);
void Screen_Data_Modify(char* data_string, Data_Send_Record_Type exist_node);

void Send_EPC_To_Zigbee(char *data_string);

#endif /* __BSP_CMD_INFO_PROCESS_H__ */
