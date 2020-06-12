#include "bsp_cmd_info_process.h"
#include "bsp_epc_exception_process.h"

extern uint8_t ROW_COUNT;
extern uint8_t *Exception_History_Array;
extern uint8_t *Exception_Current_Array;

// 用来记录 Exception_History_Array 数组的长度
uint16_t History_Array_Element_Count = 1;

// 初始化：分配初始空间
/*
***************************************************************************
*	函 数 名: Exception_Array_Init
*	功能说明: 离线设备记录数组初始化
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
void Exception_Array_Init(void)
{
    Exception_History_Array = (uint8_t *)malloc(sizeof(uint8_t) * 1);
    Exception_Current_Array = (uint8_t *)malloc(sizeof(uint8_t) * 1);
    *Exception_Current_Array = (uint8_t)1;
    *Exception_History_Array = (uint8_t)0;
}

// 复制数据记录表内容到当前异常查询数组
/*
***************************************************************************
*	函 数 名: Exception_Copy_To_Current_Array
*	功能说明: 将当前数据记录表查询次数复制到当前异常查询数组
*	参    数: Data_Send_Record_Type
*	返 回 值: 无
***************************************************************************
*/
void Exception_Copy_To_Current_Array(Data_Send_Record_Type Data_Send_Record_LinkList)
{
    uint8_t *current_pointer;
    Data_Send_Record_Type p = Data_Send_Record_LinkList->next;
    
    Exception_Current_Array = (uint8_t *)realloc(Exception_Current_Array, sizeof(uint8_t) * ROW_COUNT);
    current_pointer = Exception_Current_Array;
    
    while(p)
    {
        *current_pointer = p->EPC_String_Count;
        current_pointer++;  
        p = p->next;
    }
}

// 复制数据记录表内容到历史异常查询数组
/*
***************************************************************************
*	函 数 名: Exception_Copy_To_Current_Array
*	功能说明: 将当前数据记录表查询次数复制到历史异常查询数组
*	参    数: Data_Send_Record_Type
*	返 回 值: 无
***************************************************************************
*/
void Exception_Copy_To_History_Array(Data_Send_Record_Type Data_Send_Record_LinkList)
{
    uint8_t *history_pointer;
    Data_Send_Record_Type p = Data_Send_Record_LinkList->next;
    
    Exception_History_Array = (uint8_t *)realloc(Exception_History_Array, sizeof(uint8_t) * ROW_COUNT);
    history_pointer = Exception_History_Array;
    
    while(p)
    {
        *history_pointer = p->EPC_String_Count;
        History_Array_Element_Count++;
        history_pointer++;  
        p = p->next;
    }
}

// 清除异常设备数据记录
/*
***************************************************************************
*	函 数 名: Screen_Exception_Data_Clear
*	功能说明: 清除屏幕异常设备记录
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
void Screen_Exception_Data_Clear(void)
{
    Send_Head();
    Send_Data_Clear();
    Send_Frame_ID();
    Send_Widget_2_ID();
    Send_Tail();
}

// 发送异常设备数据记录信息
/*
***************************************************************************
*	函 数 名: Screen_Exception_Data_Add
*	功能说明: 向屏幕发送异常设备数据记录信息
*	参    数: uint8_t
*	返 回 值: 无
***************************************************************************
*/
void Screen_Exception_Data_Add(uint8_t data)
{
    Send_Head();
    Send_Data_Add();
    Send_Frame_ID();
    Send_Widget_2_ID();
    Send_Number(data);
    Send_Data_Split();
    Send_Tail();
}

// 屏幕蜂鸣器
/*
***************************************************************************
*	函 数 名: Screen_Buzzer
*	功能说明: 屏幕蜂鸣器鸣响
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
void Screen_Buzzer(void)
{
    Send_Head();
    Send_Screen_Buzzer();
    Send_Tail();
}

// 查询设备是否发生离线异常
/*
***************************************************************************
*	函 数 名: Exception_Check
*	功能说明: 将离线的RFID 信息显示到屏幕并报警
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
void Exception_Check(void)
{
    uint8_t i = 0;
    uint8_t offline_count = 0;
    uint8_t *history_pointer = Exception_History_Array;
    uint8_t *current_pointer = Exception_Current_Array;
    
    // 每检查一次要清除一次异常设备表
    Screen_Exception_Data_Clear();
    
    // 发送数据
    for(i = 0; i < History_Array_Element_Count; i++)
    {
        if(*history_pointer == *current_pointer)
        {
            Screen_Exception_Data_Add(i);
            offline_count++;
        }
        history_pointer++;
        current_pointer++;
    }
    
    // 发送到屏幕
    Send_Online_EPC_Num(ROW_COUNT - offline_count);
    Send_Offline_EPC_Num(offline_count);
    
    // 蜂鸣报警
    if(offline_count > 0 && SCREEN_BUZZER_SWITCH)
    {
       Screen_Buzzer();
    }
    
    // Exception_History_Array 数组的长度重新置零
    History_Array_Element_Count = 0;
}

