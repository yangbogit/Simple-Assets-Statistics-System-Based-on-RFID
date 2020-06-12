#include "bsp_led.h"
#include "bsp_queue.h"
#include "bsp_systick.h"
#include "bsp_usart_um202.h"
#include "bsp_usart_screen.h"
#include "bsp_usart_zigbee.h"
#include "bsp_cmd_info_process.h"
#include "bsp_epc_exception_process.h"

uint8_t ROW_COUNT = 0;                              // 数据记录表行数
uint32_t while_count = 0;                           // 主函数 while 计数器
uint8_t INTERRUPT_END = 0;                          // 串口 1 接收中断标志位
uint8_t SCREEN_MODIFY_ROW = 0;                      // 更改屏幕数据记录行
char data_string[DATA_BYTE_LENGTH];                 // 当前 EPC 信息缓存

Cmd_Queue_Type Cmd_Queue;                           // 命令队列变量并初始化
uint8_t *Exception_History_Array;                   // 查询离线设备历史记录
uint8_t *Exception_Current_Array;                   // 查询离线设备当前记录
Data_Send_Record_Type exist_node;                   // 存放查重信息 数据发送记录表初始化
Data_Send_Record_Type Data_Send_Record_LinkList;    // 数据发送记录链表

void Device_Init(void);
void EPC_Check_And_Send_To_Screen(void);
void EPC_Check_Exception_And_Send_To_Screen(void);

/*
***************************************************************************
*	函 数 名: main
*	功能说明: 主函数
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
int main(void)
{   
    Device_Init();    
    while(1)
    {
        if(INTERRUPT_END)
        {            
            EPC_Check_And_Send_To_Screen();             
            INTERRUPT_END = 0;                                                            // 清除中断标志
        }
        EPC_Check_Exception_And_Send_To_Screen();
    }
}




/* 命令队列,SysTick,LED,USART1,USART2
   USART3,Screen,异常EPC查询初始化
*/

/*
***************************************************************************
*	函 数 名: Device_Init
*	功能说明: 初始化变量、系统硬件
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
void Device_Init(void)
{
    Cmd_Queue_Init(&Cmd_Queue);  
    exist_node = Create_Data_Send_Record_Node();  
    Data_Send_Record_LinkList = Create_Data_Send_Record_LinkList();    

    LED_GPIO_Config();
    USART_UM202_Config();
    USART_Screen_Config();
    USART_Zigbee_Config();
    
    //SysTick_Init();
    Screen_Init();
    Exception_Array_Init();
}

/* 返回一条 EPC 信息 
   检查并输出到屏幕
*/
/*
***************************************************************************
*	函 数 名: EPC_Check_And_Send_To_Screen
*	功能说明: EPC信息查重和发送显示
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
void EPC_Check_And_Send_To_Screen()
{
    if(Cmd_Queue_Return_And_Check_String(&Cmd_Queue, data_string))
    {
        LED_G_ON;                                                                   // 中断发生且EPC信息合法绿灯亮   
        
        exist_node = EPC_Info_Is_Exist(data_string, Data_Send_Record_LinkList);     // 查询这条EPC信息是否已经输出过
        if (exist_node)
        {                    
            Screen_Data_Modify(data_string, exist_node);                            // 修改一条数据记录
            SCREEN_MODIFY_ROW = 0; 
            // 修改行数重新置0
        }
        else
        {                    
            Screen_Data_Add(data_string, Data_Send_Record_LinkList);                // 增加一条数据记录                    
            Send_Total_EPC_Num();                                                   // 更新在线EPC设备数
            SCREEN_MODIFY_ROW = 0;                                                  // 修改行数重新置0
            
            // 新数据发给 ZIGBEE                                                    // 如果需要将数据发送到外部设备启用 USART3
            // Send_EPC_To_Zigbee(data_string);   
                         
        }
        LED_G_OFF;  
                 
    }           
}

/* 检查丢失的EPC */
/*
***************************************************************************
*	函 数 名: EPC_Check_Exception_And_Send_To_Screen
*	功能说明: 检查离线的RFID EPC,并报警
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
void EPC_Check_Exception_And_Send_To_Screen(void)
{
       Exception_Copy_To_Current_Array(Data_Send_Record_LinkList);
       if(while_count % EPC_EXCEPTION_TOLERANCE == 0)
       {
           Exception_Check();
           Exception_Copy_To_History_Array(Data_Send_Record_LinkList);
       } 
       while_count++;
}
