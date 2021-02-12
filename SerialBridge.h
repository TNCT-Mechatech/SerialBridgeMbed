/*
    SerialBridge.h
    
    SerialBridgeの処理をここで定義しています。

    Original repository
    Author: Taiyou Komazawa
    Github: https://github.com/TNCT-Mechatech/SerialBridgeIno
    License: Apache-2.0
    
    This repository
    Author: testusuke
    Github: https://github.com/testusuke/
    Date: 2020/12/8
*/

#ifndef SERIAL_BRIDGE_H_
#define SERIAL_BRIDGE_H_

#include "mbed.h"

#include "stdlib.h"

#include "./BufferSerial/BufferSerial.h"
#include "Message.h"

class SerialBridge
{
public:
    typedef uint8_t frame_id;

    SerialBridge(BufferSerial *dev);

    ~SerialBridge()
    {
        delete[] _str;
    }

    void wait_host(char* device_name);

    void add_frame(frame_id id, sb::_Message *str);
    int read();
    void write(frame_id id, sb::_Message *str);

protected:
    enum
    {
        FRAME_LEN = 4,
        STRUCT_MAX_NUM = 10,
    };

    typedef enum ControlCharType
    {
        HEADER = ':',
        END = '\n',
    } ctrl_char_t;

private:
    sb::_Message *_str[STRUCT_MAX_NUM];
    uint8_t _max_data_size;

    BufferSerial *_dev;

    void _wait_host(char* device_name);
    inline void _write_once(uint8_t c, int *data_sum);
    inline uint8_t _read_once(int *data_sum);
};

#endif