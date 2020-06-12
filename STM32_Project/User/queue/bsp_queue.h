#ifndef __BSP_QUEUE_H__
#define __BSP_QUEUE_H__

#include "stm32f10x.h"

#define  CMD_QUEUE_MAX_SIZE   512       // 队列大小    
typedef  uint8_t              ElemType; // 队列元素类型   
typedef  uint8_t              pointer;  // 指针类型

typedef struct{
    pointer Head;                       // 队列头指针
    pointer Tail;                       // 队列尾指针
    pointer Current;                    // 当前队列数据指针：总指向帧头
    ElemType Data[CMD_QUEUE_MAX_SIZE];  // 队列
}Cmd_Queue_Type;

void Cmd_Queue_Init(Cmd_Queue_Type *Cmd_Queue);
void Cmd_Queue_Push(Cmd_Queue_Type *Queue, ElemType *data);
void Cmd_Queue_Pop(Cmd_Queue_Type *Queue, ElemType *data);
uint8_t Cmd_Queue_Return_And_Check_String(Cmd_Queue_Type *Cmd_Queue, char *data_string);

#endif /* __BSP_QUEUE_H__ */
