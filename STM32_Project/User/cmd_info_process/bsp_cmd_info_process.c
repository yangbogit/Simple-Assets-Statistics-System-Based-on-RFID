#include "bsp_systick.h"
#include "bsp_cmd_info_process.h"

extern uint8_t ROW_COUNT;
extern uint8_t SCREEN_MODIFY_ROW;

/****************************************** 链表操作 **********************************************/
/**************************************************************************************************/
// 创建头节点


/*
***************************************************************************
*	函 数 名: Create_Data_Send_Record_Node
*	功能说明: 创建一个数据记录链表头结点
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
Data_Send_Record_Type Create_Data_Send_Record_LinkList(void)
{
    Data_Send_Record_Type head = (Data_Send_Record_Type)malloc(sizeof(EPC_Node));
    if (head != NULL)
    {
        head->next = NULL;
        head->EPC_String_Count = 0;
    }
    return head;
}

// 创建节点
/*在启动文件 starup_stm32f10x_hd.s 中 更改 
  Heap_Size 为 EQU     0x0000F000 堆空间分
  配不足会导致 malloc 分配空间失败*/

/*
***************************************************************************
*	函 数 名: Create_Data_Send_Record_Node
*	功能说明: 创建一个数据记录链表结点
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
Data_Send_Record_Type Create_Data_Send_Record_Node(void)
{
    Data_Send_Record_Type node = (Data_Send_Record_Type) malloc(sizeof( EPC_Node));
    if (node != NULL)
    {
        node->next = NULL;
        node->EPC_String_Count = 0;
    }
    return node;
}

// 插入节点
void Data_Record_Insert_Node(char *data_string, Data_Send_Record_Type Data_Send_Record_LinkList)
{
    Data_Send_Record_Type p = Data_Send_Record_LinkList;       
    Data_Send_Record_Type Node = Create_Data_Send_Record_Node();        // 创建一个节点 并初始化
           
    Node->EPC_String_Count = 1;                                         // 添加新数据插入链表,Count = 1;
    strncpy(Node->EPC_String, data_string, DATA_BYTE_LENGTH);           // 把字符串赋值给 Node.EPC_String
            
    // 插入节点
    while(p->next != NULL) 
    {
        p=p->next;
    }
    p->next = Node;
}


// 查找此EPC信息在Data_Send_Record.EPC_String是否存在
// 若存在返回存在、记录行号 SCREEN_MODIFY_ROW
Data_Send_Record_Type EPC_Info_Is_Exist(char *data_string, Data_Send_Record_Type Data_Send_Record_LinkList)
{
    // 在发送表查找历史记录
    Data_Send_Record_Type p = Data_Send_Record_LinkList;
    while(p)
    {
        p = p->next;
        if(strcmp(p->EPC_String, data_string) == 0)
        {
            return p;
        }
        SCREEN_MODIFY_ROW ++; // 记录将要修改的行数
    }
    return NULL;
}
/**************************************************************************************************/
/**************************************************************************************************/

/* 发送的数字都以 3位数 显示 */
void Send_Number(uint8_t temp)
{
    if (temp >= 1 && temp < 10)
    {
        Usart_Screen_Send_8_Bits( USART_Screen, 0x30); 
        Usart_Screen_Send_8_Bits( USART_Screen, 0x30); 
        Usart_Screen_Send_8_Bits( USART_Screen, temp % 10 + 0x30); 
    }
    else if (temp >= 10 && temp < 100)
    {
        Usart_Screen_Send_8_Bits( USART_Screen, 0x30); 
        Usart_Screen_Send_8_Bits( USART_Screen, (temp / 10) + 0x30);
        Usart_Screen_Send_8_Bits( USART_Screen, temp % 10 + 0x30); 
    }
    else
    {
        Usart_Screen_Send_8_Bits( USART_Screen, (temp / 100) + 0x30);
        Usart_Screen_Send_8_Bits( USART_Screen, ((temp- (temp / 100)*100) / 10) + 0x30);
        Usart_Screen_Send_8_Bits( USART_Screen, temp % 10 + 0x30); 
    }
}

// 切换画面
void Screen_Switch(void)
{
    Send_Head();
    Send_Screen_Switch();
    Send_Frame_ID();
    Send_Tail();
}

// 清除历史数据
void Screen_Data_Clear(void)
{
    // 清除数据记录表
    Send_Head();
    Send_Data_Clear();
    Send_Frame_ID();
    Send_Widget_1_ID();
    Send_Tail();
    
    // 清除异常设备表
    Send_Head();
    Send_Data_Clear();
    Send_Frame_ID();
    Send_Widget_2_ID();
    Send_Tail();
}

// 发送设备总数文本
/*
***************************************************************************
*	函 数 名: Send_Total_EPC_Num
*	功能说明: 向屏幕发送当前检测到的RFID标签总数
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
void Send_Total_EPC_Num(void)
{
    Send_Head();
    Send_Write_Text();
    Send_Frame_ID();
    Send_Text_Total_ID();
    Send_Number(ROW_COUNT);
    Send_Tail();
}


// 发送在线设备总数文本
/*
***************************************************************************
*	函 数 名: Send_Online_EPC_Num
*	功能说明: 向屏幕发送发送在线设备总数文本
*	参    数: uint8_t
*	返 回 值: 无
***************************************************************************
*/
void Send_Online_EPC_Num(uint8_t count)
{
    Send_Head();
    Send_Write_Text();
    Send_Frame_ID();
    Send_Text_Online_ID();
    Send_Number(count);
    Send_Tail();
}

// 发送离线设备总数文本
/*
***************************************************************************
*	函 数 名: Send_Offline_EPC_Num
*	功能说明: 向屏幕发送发送离线设备总数文本
*	参    数: uint8_t
*	返 回 值: 无
***************************************************************************
*/
void Send_Offline_EPC_Num(uint8_t count)
{
    Send_Head();
    Send_Write_Text();
    Send_Frame_ID();
    Send_Text_Offline_ID();
    Send_Number(count);
    Send_Tail();
}

// 播放音频
// EE 94 33 3A 2F 53 6F 75 6E 64 73 2F 30 2E 77 61 76 FF FC FF FF 
/*
***************************************************************************
*	函 数 名: Screen_Start_Music
*	功能说明: 显示屏播放音频
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
void Screen_Start_Music(void)
{
    Send_Head();      
    Usart_Screen_Send_32_Bits(USART_Screen, 0x94333A2F);
    Usart_Screen_Send_32_Bits(USART_Screen, 0x536F756E);
    Usart_Screen_Send_32_Bits(USART_Screen, 0x64732F30);
    Usart_Screen_Send_32_Bits(USART_Screen, 0x2E776176);
    Send_Tail();
}

// 设备启动进行屏幕的初始化显示
/*
***************************************************************************
*	函 数 名: Screen_Init
*	功能说明: 初始化屏幕、播放启动音乐等
*	参    数: 无
*	返 回 值: 无
***************************************************************************
*/
void Screen_Init(void)
{    
    Screen_Start_Music();       // 屏幕启动音乐播放
    Screen_Switch();            // 切换画面 
    Screen_Data_Clear();        // 清除历史数据
    Send_Total_EPC_Num();       // EPC设备总数发屏幕
    Send_Online_EPC_Num(0);     // EPC在线设备数发屏幕
    Send_Offline_EPC_Num(0);    // EPC离线设备数发屏幕
}

/**************************************************************************************************/

// 用zigbee发送数据
void Send_EPC_To_Zigbee(char *data_string)
{
    uint8_t i = 0;
    for(i = 0; i < (DATA_BYTE_LENGTH - FRAME_TAIL_LENGTH); i++)
    {
        Usart_Zigbee_Send_8_Bits(USART_Zigbee, data_string[i]);
    }
}

/**************************************************************************************************/

// 发序号 新增数据的序号就是 Data_Send_Record.Row_Count
void Send_Number_Add(void)
{
    Send_Number(ROW_COUNT);
}

// 发 EPC
void Send_EPC(char *data_string)
{
    uint8_t i = 0;
    for ( i = 0; i < (DATA_BYTE_LENGTH - FRAME_TAIL_LENGTH); i++)
    {    
        Usart_Screen_Send_8_Bits(USART_Screen, data_string[i]);
    }
}

// 新增数据的统计次数 1
void Send_Count_Add(void)
{
    Send_Number(1);
}
  
// 屏幕修改行数 修改行数是16位的
void Send_Row_Modify()
{
    Usart_Screen_Send_16_Bits( USART_Screen, SCREEN_MODIFY_ROW); 
}

// 发送行数
void Send_Number_Modify(void)
{
    Send_Number(SCREEN_MODIFY_ROW);
}

// 修改数据的统计次数应该从Data_Send_Record中读取
void Send_Count_Modify(EPC_Node *exist_pointer)
{
    exist_pointer->EPC_String_Count++;  
    Send_Number(exist_pointer->EPC_String_Count);
}

// 增加数据记录表信息
/*
***************************************************************************
*	函 数 名: Screen_Data_Add
*	功能说明: 向屏幕增加一条EPC显示数据
*	参    数: char * ,Data_Send_Record_Type
*	返 回 值: 无
***************************************************************************
*/
void Screen_Data_Add(char *data_string, Data_Send_Record_Type Data_Send_Record_LinkList)
{
    Send_Head();                // 发帧头
    Send_Data_Add();            // 发增加数据命令
    Send_Frame_ID();            // 发画面ID
    Send_Widget_1_ID();         // 发控件ID
    
    Send_Number_Add();          // 发序号
    Send_Data_Split();
    Send_EPC(data_string);      // 发 EPC
    Send_Data_Split();
    Send_Count_Add();           // 发检测次数
    Send_Data_Split();
    
    Send_Tail();                // 发帧尾

    ROW_COUNT++;                // 总行数增加 1
    Data_Record_Insert_Node(data_string, Data_Send_Record_LinkList);    // 在Data_Send_Record中增加这条数据的发送次数、EPC_INFO
}

// 修改数据记录表信息
/*
***************************************************************************
*	函 数 名: Screen_Data_Modify
*	功能说明: 修改一条EPC显示数据
*	参    数: char *, EPC_Node*
*	返 回 值: 无
***************************************************************************
*/
void Screen_Data_Modify(char* data_string, EPC_Node* exist_node)
{
    Send_Head();                // 发帧头   
    Send_Data_Modify();         // 发修改数据命令
    Send_Frame_ID();            // 发画面ID
    Send_Widget_1_ID();         // 发控件ID
    Send_Row_Modify();          // 发修改的行数
    
    Send_Number_Modify();       // 发修改的序号
    Send_Data_Split();
    Send_EPC(data_string);      // 发 EPC
    Send_Data_Split();
    Send_Count_Modify(exist_node);  // 发检测次数
    Send_Data_Split();

    Send_Tail();                // 发帧尾
}

/**************************************************************************************************/
