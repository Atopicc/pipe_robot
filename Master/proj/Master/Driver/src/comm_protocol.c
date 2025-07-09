#include "comm_protocol.h"
#include <string.h>
#include <stdlib.h>
#include "debug.h"
#include "motor.h"
#include "pwm.h"

int8_t current_angle_forward = 0;
int8_t current_angle_back = 0;

//------------------- 解析器实现 -------------------
void ParseCommunicationFrame(CommHandler *handler)
{
    static enum {
        STATE_HEADER,
        STATE_DEV_ID,
        STATE_CMD_ID,
        STATE_DATA_LEN,
        STATE_PAYLOAD,
        STATE_FOOTER
    } parser_state = STATE_HEADER;

    if(parser_state == STATE_HEADER)
    {
        if(handler->rx_buffer[0] == FRAME_HEADER)
        {
            memset(&handler->current_frame, 0, sizeof(FrameStruct));
            handler->current_frame.header = handler->rx_buffer[0];
            parser_state = STATE_DEV_ID;
        }
    }else return;

    if(parser_state == STATE_DEV_ID)
    {
        handler->current_frame.dev_id = handler->rx_buffer[1];
        parser_state = STATE_CMD_ID;
    }else {
        return;
        parser_state = STATE_HEADER;
    }

    if(parser_state == STATE_CMD_ID)
    {
        handler->current_frame.cmd_id = handler->rx_buffer[2];
        parser_state = STATE_DATA_LEN;
    }else {
        return;
        parser_state = STATE_HEADER;
    }

    if(parser_state == STATE_DATA_LEN)
    {
        handler->current_frame.data_len = handler->rx_buffer[3];
        if(handler->rx_buffer[3] > 0)
        {
            handler->current_frame.data = malloc(handler->rx_buffer[3]);
            if (handler->current_frame.data == NULL) {
                // 内存分配失败处理
                parser_state = STATE_HEADER;
                return;
            }
            parser_state = STATE_PAYLOAD;
        }else {
            parser_state = STATE_FOOTER;
        }
    }else
    {
        return;
        parser_state = STATE_HEADER;
    }

    if(parser_state == STATE_PAYLOAD)
    {
        if (handler->current_frame.data) {
            for(int i = 0;i < handler->current_frame.data_len;i++)
            {
                handler->current_frame.data[i] = handler->rx_buffer[4+i];
            }
            parser_state = STATE_FOOTER;
        }
    }else
    {
        free(handler->current_frame.data);
        handler->current_frame.data = NULL;
        parser_state = STATE_HEADER;
        return;
    }

    if(parser_state == STATE_FOOTER)
    {
        if(handler->rx_buffer[4+handler->current_frame.data_len] == FRAME_TAIL)
        {
            handler->current_frame.footer = handler->rx_buffer[4+handler->current_frame.data_len];
            ProcessCompleteFrame(handler); // 处理解析出来的完整帧
            parser_state = STATE_HEADER;
        }else
        {
            free(handler->current_frame.data);
            handler->current_frame.data = NULL;
            parser_state = STATE_HEADER;
            return;
        }
    }

    free(handler->current_frame.data);
    handler->current_frame.data = NULL;
}

//------------------- 帧处理逻辑 -------------------
void ProcessCompleteFrame(CommHandler *handler)
{
    // GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    // USART1_Printf("frame complete");
    FrameStruct *frame = &handler->current_frame;
    switch (frame->dev_id) {
        case DEV_MASTER:
            ExecuteLocalCommand(frame->cmd_id, frame->data, frame->data_len);
            break;
        case DEV_CAM:
            USART1_Printf("Forward to Cam\r\n");
            ForwardToDevice(handler->huart_cam, frame);
            break;
        case DEV_EXTENSION:
            USART1_Printf("Forward to EXtern\r\n");
            // GPIO_ResetBits(GPIOB,GPIO_Pin_12);
            ForwardToDevice(handler->huart_ext, frame);
            break;
        default:
            // GPIO_ResetBits(GPIOB,GPIO_Pin_12);
            break;
    }

    // 释放内存
    if (frame->data) {
        free(frame->data);
        frame->data = NULL;
    }
}

void ExecuteLocalCommand(uint8_t cmd_id, uint8_t* data, uint8_t len)
{
    for (int i = 0; i < sizeof(cmd_handlers)/sizeof(CmdHandlerMap); i++) {
        if (cmd_handlers[i].cmd_id == cmd_id) {
            cmd_handlers[i].handler(data, len);
            return;
        }
    }
}

//------------------- 数据转发函数 -------------------
void ForwardToDevice(void *huart, FrameStruct *frame)
{
    USART_TypeDef* uart = (USART_TypeDef*)huart;
    uint8_t tx_buffer[256];
    uint8_t *ptr = tx_buffer;
    
    *ptr++ = frame->header;
    *ptr++ = frame->dev_id;
    *ptr++ = frame->cmd_id;
    *ptr++ = frame->data_len;
    if (frame->data_len > 0 && frame->data != NULL) {
        memcpy(ptr, frame->data, frame->data_len);
        ptr += frame->data_len;
    }
    *ptr++ = frame->footer;
    unsigned char *a = tx_buffer;

    USART1_SendString_Len((char*)a,ptr-a);
    
    for (uint8_t *p = tx_buffer; p < ptr; p++) {
        USART_SendData(uart, *p);
        while (USART_GetFlagStatus(uart, USART_FLAG_TXE) == RESET);
    }
}

// 命令处理函数

// 手柄遥控
void HandleExtColCommand(uint8_t* data, uint8_t len)
{
    // UART4_SendString_Len((char*)data,len);
    // UART4_SendByte(0xFF);UART4_SendByte(0xFF);
    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    if (len == 6) {
        
        if(data[0] == 0x01)
        {
            Motor_Advanced();
            // UART4_Printf("Advance\r\n");
        }
        else if(data[1] == 0x01)
        {
            Motor_Back();
            // UART4_Printf("Back\r\n");
        }
        //前展开
        if(data[2] == 0x01)
        {
            if(current_angle_forward < 70)
            {
                current_angle_forward += 2;
                SetServerAngle(SERVER6,current_angle_forward);
                SetServerAngle(SERVER8,-current_angle_forward);
                SetServerAngle(SERVER9,current_angle_forward);
                SetServerAngle(SERVER11,-current_angle_forward);
            }
            // UART4_Printf("Forward Expand\r\n");
        }
        //前缩起
        else if(data[3] == 0x01)
        {
            if(current_angle_forward > 0)
            {
                current_angle_forward -= 2;
                SetServerAngle(SERVER6,current_angle_forward);
                SetServerAngle(SERVER8,-current_angle_forward);
                SetServerAngle(SERVER9,current_angle_forward);
                SetServerAngle(SERVER11,-current_angle_forward);
            }
            // UART4_Printf("Forward Shirnk\r\n");
        }
        //后展开
        if(data[4] == 0x01)
        {
            if(current_angle_back < 90)
            {
                current_angle_back += 2;
                SetServerAngle(SERVER7,-current_angle_back);
                SetServerAngle(SERVER10,-current_angle_back);
            }
            // UART4_Printf("Side Expand\r\n");
        }
        //后缩起
        else if(data[5] == 0x01)
        {
            if(current_angle_back > 0)
            {
                current_angle_back -= 2;
                SetServerAngle(SERVER7,-current_angle_back);
                SetServerAngle(SERVER10,-current_angle_back);
            }
            // UART4_Printf("Side Shirnk\r\n");
        }
        // else
        // {
        //     Motor_Stop();
        // }
    }
}

// 拓展板发给主控 停止
void HandleExtStopCommand(uint8_t* data, uint8_t len)
{
    if (len == 1) {
        if(data[0] == 0x01)
        {
            Motor_Stop();
        }
    }
}

void HandleExtMochaCommand(uint8_t* data, uint8_t len)
{
    if (len == 1) {
        if(data[0] == 0x00)
        {

        }
    }
}

void HandleEspSpocolCommand(uint8_t* data, uint8_t len)
{
    if (len == 6) {

        if(data[0] == 0x01)
        {
            Motor_Advanced();
            USART1_Printf("ESP advance\r\n");
        }else if(data[1] == 0x01)
        {
            Motor_Back();
            USART1_Printf("ESP back\r\n");
        }

        //前展开
        if(data[2] == 0x01)
        {
            if(current_angle_forward < 70)
            {
                current_angle_forward += 2;
                SetServerAngle(SERVER6,current_angle_forward);
                SetServerAngle(SERVER8,-current_angle_forward);
                SetServerAngle(SERVER9,current_angle_forward);
                SetServerAngle(SERVER11,-current_angle_forward);
            }
            // USART1_Printf("ESP For Expand\r\n");
        }
        //前缩起
        else if(data[3] == 0x01)
        {
            if(current_angle_forward > 0)
            {
                current_angle_forward -= 2;
                SetServerAngle(SERVER6,current_angle_forward);
                SetServerAngle(SERVER8,-current_angle_forward);
                SetServerAngle(SERVER9,current_angle_forward);
                SetServerAngle(SERVER11,-current_angle_forward);
            }
            // USART1_Printf("ESP For Shink\r\n");
        }
        //后展开
        if(data[4] == 0x01)
        {
            if(current_angle_back < 90)
            {
                current_angle_back += 2;
                SetServerAngle(SERVER7,-current_angle_back);
                SetServerAngle(SERVER10,-current_angle_back);
            }
            // UART4_Printf("Side Expand\r\n");
        }
        //后缩起
        else if(data[5] == 0x01)
        {
            if(current_angle_back > 0)
            {
                current_angle_back -= 2;
                SetServerAngle(SERVER7,-current_angle_back);
                SetServerAngle(SERVER10,-current_angle_back);
            }
            // UART4_Printf("Side Shirnk\r\n");
        }
    }
}

void HandleEspStopCommand(uint8_t* data, uint8_t len)
{
    if (len == 1) {
        if(*data == 0x00)
        {
            Motor_Stop();
            USART1_Printf("ESP Stop\r\n");
        }
    }
}

void HandleEspMochaCommand(uint8_t* data, uint8_t len)
{
    if (len == 4) {
    
    }
}