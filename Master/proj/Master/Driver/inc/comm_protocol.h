#ifndef __COMM_PROTOCOL_H__
#define __COMM_PROTOCOL_H__

#include <stdint.h>
#include "usart.h"

// 通信协议定义
#define FRAME_HEADER   0xAA
#define FRAME_TAIL     0xFF
#define DEV_MASTER     0xD1
#define DEV_CAM        0xD2
#define DEV_EXTENSION  0xD3

// 内容标识符定义

//主控发给ESP32
#define CMD_MA_STATE    0xC1  // 状态（运动状态）
#define CMD_MA_BATTERY  0xC2  //电池电压（百分比）

//拓展板发给主控
#define CMD_EXT_COL    0xC3  //手柄遥控
#define CMD_EXT_PIC    0xC4  //手柄拍照
#define CMD_EXT_STOP   0xCC  //停止
#define CMD_EXT_MOCHA  0xCE  //模式切换

//拓展板发给ESP32
#define CMD_EXT_TEMHUM   0xC5  //温湿度
#define CMD_EXT_IMU      0xC6  //XYZ
#define CMD_EXT_LEDCOL   0xC7  //灯光
#define CMD_EXT_CLEAN    0xC8  //清理

//ESP32发给主控
#define CMD_ESP_SPOCOL   0xC9  //运动控制
#define CMD_ESP_STOP     0xCA  //停止
#define CMD_ESP_MOCHA    0xCD  //模式切换

//ESP32发给拓展板
#define CMD_ESP_CLEAN    0xCB  //清理

// 数据结构定义
typedef struct {
    uint8_t header;
    uint8_t dev_id;
    uint8_t cmd_id;
    uint8_t data_len;
    uint8_t *data;
    uint8_t footer;
} FrameStruct;

// 设备通信句柄定义
typedef struct {
    void *huart_cam;     // 连接CAM的串口
    void *huart_ext;     // 连接扩展板的串口
    uint8_t rx_buffer[256];       // 接收缓冲区
    uint16_t rx_index;            // 接收索引
    FrameStruct current_frame;    // 当前解析帧
    uint8_t is_finished;
} CommHandler;

// 处理函数指针类型定义
typedef void (*CmdHandler)(uint8_t* data, uint8_t len);

// 命令处理映射表
typedef struct {
    uint8_t cmd_id;
    CmdHandler handler;
} CmdHandlerMap;

// 函数声明
void ParseCommunicationFrame(CommHandler *handler);
void ProcessCompleteFrame(CommHandler *handler);
void ExecuteLocalCommand(uint8_t cmd_id, uint8_t* data, uint8_t len);
void ForwardToDevice(void *huart, FrameStruct *frame);

// 命令处理函数声明
void HandleExtColCommand(uint8_t* data, uint8_t len);
void HandleExtStopCommand(uint8_t* data, uint8_t len);
void HandleExtMochaCommand(uint8_t* data, uint8_t len);
void HandleEspSpocolCommand(uint8_t* data, uint8_t len);
void HandleEspStopCommand(uint8_t* data, uint8_t len);
void HandleEspMochaCommand(uint8_t* data, uint8_t len);

//----------------- 指令查找集 -------------------
static const CmdHandlerMap cmd_handlers[] = {
    {CMD_EXT_COL, HandleExtColCommand},
    {CMD_EXT_STOP, HandleExtStopCommand},
    {CMD_EXT_MOCHA, HandleExtMochaCommand},
    {CMD_ESP_SPOCOL, HandleEspSpocolCommand},
    {CMD_ESP_STOP, HandleEspStopCommand},
    {CMD_ESP_MOCHA, HandleEspMochaCommand},
    // 添加其他命令处理...
};

#endif /* __COMM_PROTOCOL_H__ */