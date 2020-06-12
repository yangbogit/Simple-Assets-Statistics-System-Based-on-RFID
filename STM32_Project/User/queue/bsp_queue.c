#include "bsp_queue.h"
#include "bsp_cmd_info_process.h"

/*
***************************************************************************
*	函 数 名: Cmd_Queue_Init
*	功能说明: 初始化EPC接收队列Cmd_Queue_Init
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
void Cmd_Queue_Init(Cmd_Queue_Type *Cmd_Queue)
{
    Cmd_Queue->Head = 0;
    Cmd_Queue->Tail = 0;
    Cmd_Queue->Current = 0;
}

// 入队列
/*
***************************************************************************
*	函 数 名: Cmd_Queue_Push
*	功能说明: 元素入队列
*	参    数: Cmd_Queue_Type *, ElemType *
*	返 回 值: 无
***************************************************************************
*/
void Cmd_Queue_Push(Cmd_Queue_Type *Cmd_Queue, ElemType *data)
{
    if((Cmd_Queue->Tail - Cmd_Queue->Head + 1) == CMD_QUEUE_MAX_SIZE)
    {
        Cmd_Queue->Tail = 0;
    }
    Cmd_Queue->Data[Cmd_Queue->Tail] = *data;    
    Cmd_Queue->Tail++;
}

// 出队列
/*
***************************************************************************
*	函 数 名: Cmd_Queue_Pop
*	功能说明: 元素出队列
*	参    数: Cmd_Queue_Type *, ElemType *
*	返 回 值: 无
***************************************************************************
*/
void Cmd_Queue_Pop(Cmd_Queue_Type *Cmd_Queue, ElemType *data)
{
    if((Cmd_Queue->Current +1) == CMD_QUEUE_MAX_SIZE)
    {
        Cmd_Queue->Current = 0;
    }
    *data = Cmd_Queue->Data[Cmd_Queue->Current];
    Cmd_Queue->Current++;

}

/* 返回一条 EPC 信息并检测数据是否正确 */
// EPC信息前缀
char *EPC_INFO_PREFIX_1 = "222016333210018000";
char *EPC_INFO_PREFIX_2 = "222016333210019000";
char *EPC_INFO_PREFIX_3 = "222016333210020000";

// 一个较大的值，能够装下较长的EPC信息 此处为64字节
#define  STRING_TEMP_LENGTH  64

/*
***************************************************************************
*	函 数 名: Cmd_Queue_Return_And_Check_String
*	功能说明: EPC信息查重
*	参    数: Cmd_Queue_Type *Cmd_Queue, char *data_string
*	返 回 值: uint8_t
***************************************************************************
*/
uint8_t Cmd_Queue_Return_And_Check_String(Cmd_Queue_Type *Cmd_Queue, char *data_string)
{
    uint8_t i = 0;
    uint8_t temp;
    char string_temp[STRING_TEMP_LENGTH];

    // 取出一条命令
    while(1)
    {
        Cmd_Queue_Pop(Cmd_Queue, &temp);
        string_temp[i] = temp;
        i++;
        if(temp == '\n')
        {
            break;
        }
    }
    
    // 比较字符串前缀
    if((strncmp(string_temp, EPC_INFO_PREFIX_1, strlen(EPC_INFO_PREFIX_1)) == 0) || 
       (strncmp(string_temp, EPC_INFO_PREFIX_2, strlen(EPC_INFO_PREFIX_2)) == 0) ||
       (strncmp(string_temp, EPC_INFO_PREFIX_3, strlen(EPC_INFO_PREFIX_3)) == 0))
    {
        strncpy(data_string, string_temp, DATA_BYTE_LENGTH);
        return 1;
    }
    else
    {
        return 0;
    }
}


