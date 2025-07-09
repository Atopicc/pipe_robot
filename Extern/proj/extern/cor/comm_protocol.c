#include "comm_protocol.h"
#include <string.h>
#include <stdlib.h>
#include "debug.h"
#include "Motor.h"


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
            USART1_Printf("head%X\r\n",handler->current_frame.header);
            parser_state = STATE_DEV_ID;
        }
    }else return;

    if(parser_state == STATE_DEV_ID)
    {
        handler->current_frame.dev_id = handler->rx_buffer[1];
        USART1_Printf("dev%X\r\n",handler->current_frame.dev_id);
        parser_state = STATE_CMD_ID;
    }else {
        return;
        parser_state = STATE_HEADER;
    }

    if(parser_state == STATE_CMD_ID)
    {
        handler->current_frame.cmd_id = handler->rx_buffer[2];
        USART1_Printf("cmd%X\r\n",handler->current_frame.cmd_id);
        parser_state = STATE_DATA_LEN;
    }else {
        return;
        parser_state = STATE_HEADER;
    }

    if(parser_state == STATE_DATA_LEN)
    {
        handler->current_frame.data_len = handler->rx_buffer[3];
        USART1_Printf("len%X\r\n",handler->current_frame.data_len);
        if(handler->rx_buffer[3] > 0)
        {
            handler->current_frame.data = malloc(handler->rx_buffer[3]);
            if (handler->current_frame.data == NULL) {
                // 内存分配失败处理
                USART1_Printf("[Warning]内存分配失败！\r\n");
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
        // USART1_Printf("payload:%s\r\n",handler->current_frame.data);
    }else
    {
        free(handler->current_frame.data);
        handler->current_frame.data = NULL;
        parser_state = STATE_HEADER;
        return;
    }

    if(parser_state == STATE_FOOTER)
    {
        USART1_Printf("footer%X\r\n",handler->rx_buffer[4+handler->current_frame.data_len]);
        if(handler->rx_buffer[4+handler->current_frame.data_len] == FRAME_TAIL)
        {
            USART1_Printf("in\r\n");
            handler->current_frame.footer = handler->rx_buffer[3+handler->current_frame.data_len];
            ProcessCompleteFrame(handler);
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
    FrameStruct *frame = &handler->current_frame;
    USART1_Printf("processing!%x\r\n",frame->dev_id);
    switch (frame->dev_id) {
        case DEV_MASTER:
            // ExecuteLocalCommand(frame->cmd_id, frame->data, frame->data_len);
            ForwardToDevice(handler->huart_master, frame);
            break;
        case DEV_CAM:
            ForwardToDevice(handler->huart_master, frame);
            break;
        case DEV_EXTENSION:
            // ForwardToDevice(handler->huart_cam, frame);
            ExecuteLocalCommand(frame->cmd_id, frame->data, frame->data_len);
            break;
        default:
            break;
    }

    // 释放内存
    if (frame->data) {
        free(frame->data);
        frame->data = NULL;
    }
}

//------------------- 本机命令执行 -------------------
static const CmdHandlerMap cmd_handlers[] = {
    {CMD_ESP_CLEAN, HandleCleanCommand},
};

void ExecuteLocalCommand(uint8_t cmd_id, uint8_t* data, uint8_t len)
{
    USART1_Printf("searching %X\r\n",cmd_id);
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
    
    for (uint8_t *p = tx_buffer; p < ptr; p++) {
        USART_SendData(uart, *p);
        while (USART_GetFlagStatus(uart, USART_FLAG_TXE) == RESET);
    }
}

// 示例命令处理函数
void HandleCleanCommand(uint8_t* data, uint8_t len)
{
    if (len == 1)
    {
        if(data[0])
        {
            Motor_Control(ENABLE);
        }
            
        else
        {
            Motor_Control(DISABLE);
        }
            
    }
}