#ifndef __COMM_PROTOCOL_H__
#define __COMM_PROTOCOL_H__

#include <stdint.h>
#include "usart.h"

// ͨ��Э�鶨��
#define FRAME_HEADER   0xAA
#define FRAME_TAIL     0xFF
#define DEV_MASTER     0xD1
#define DEV_CAM        0xD2
#define DEV_EXTENSION  0xD3

// ���ݱ�ʶ������

//���ط���ESP32
#define CMD_MA_STATE    0xC1  // ״̬���˶�״̬��
#define CMD_MA_BATTERY  0xC2  //��ص�ѹ���ٷֱȣ�

//��չ�巢������
#define CMD_EXT_COL    0xC3  //�ֱ�ң��
#define CMD_EXT_PIC    0xC4  //�ֱ�����
#define CMD_EXT_STOP   0xCC  //ֹͣ
#define CMD_EXT_MOCHA  0xCE  //ģʽ�л�

//��չ�巢��ESP32
#define CMD_EXT_TEMHUM   0xC5  //��ʪ��
#define CMD_EXT_IMU      0xC6  //XYZ
#define CMD_EXT_LEDCOL   0xC7  //�ƹ�
#define CMD_EXT_CLEAN    0xC8  //����

//ESP32��������
#define CMD_ESP_SPOCOL   0xC9  //�˶�����
#define CMD_ESP_STOP     0xCA  //ֹͣ
#define CMD_ESP_MOCHA    0xCD  //ģʽ�л�

//ESP32������չ��
#define CMD_ESP_CLEAN    0xCB  //����

// ���ݽṹ����
typedef struct {
    uint8_t header;
    uint8_t dev_id;
    uint8_t cmd_id;
    uint8_t data_len;
    uint8_t *data;
    uint8_t footer;
} FrameStruct;

// �豸ͨ�ž������
typedef struct {
    void *huart_cam;        // ����CAM�Ĵ���
    void *huart_master;     // �������ذ�Ĵ���
    uint8_t rx_buffer[256];       // ���ջ�����
    uint16_t rx_index;            // ��������
    FrameStruct current_frame;    // ��ǰ����֡
    uint8_t is_finished;
} CommHandler;

// ������ָ�����Ͷ���
typedef void (*CmdHandler)(uint8_t* data, uint8_t len);

// �����ӳ���
typedef struct {
    uint8_t cmd_id;
    CmdHandler handler;
} CmdHandlerMap;

// ��������
void ParseCommunicationFrame(CommHandler *handler);
void ProcessCompleteFrame(CommHandler *handler);
void ExecuteLocalCommand(uint8_t cmd_id, uint8_t* data, uint8_t len);
void ForwardToDevice(void *huart, FrameStruct *frame);

// ʾ�������������
void HandleCleanCommand(uint8_t* data, uint8_t len);

#endif /* __COMM_PROTOCOL_H__ */