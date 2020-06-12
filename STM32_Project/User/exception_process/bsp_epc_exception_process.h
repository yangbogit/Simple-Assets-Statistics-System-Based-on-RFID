#ifndef __BSP_EPC_EXCEPTION_PROCESS_H__
#define __BSP_EPC_EXCEPTION_PROCESS_H__

#include "bsp_cmd_info_process.h"

#define EPC_EXCEPTION_TOLERANCE  500000         // 主函数while循环执行多少次检查一次异常EPC


// 是否启用屏幕蜂鸣器

//#define SCREEN_BUZZER_SWITCH     DISABLE      
#define SCREEN_BUZZER_SWITCH     ENABLE

void Exception_Array_Init(void);
void Exception_Check(void);
void Exception_Copy_To_History_Array(Data_Send_Record_Type Data_Send_Record_LinkList);
void Exception_Copy_To_Current_Array(Data_Send_Record_Type Data_Send_Record_LinkList);

#endif /*__BSP_EPC_EXCEPTION_PROCESS_H__ */
