#ifndef BUFFER_SERIAL_H
#define BUHHER_SERIAL_H

//  include
#include "mbed.h"

#ifndef SERIAL_RX_BUFFER_SIZE
//  RX Buffer Max Size
#define SERIAL_RX_BUFFER_SIZE 64
#endif

#if  (SERIAL_RX_BUFFER_SIZE>256)
typedef uint16_t rx_buffer_index_t;
#else
typedef uint8_t rx_buffer_index_t;
#endif

class BufferSerial : public RawSerial
{
public:
    //  constructor
    BufferSerial(PinName tx, PinName rx,int baud,int timeout);
    
    //  function of arduino serial
    int available(void);
    //  return number of bytes available to read.
    int read(void);
    //  return first byte of incoming data available (or -1 if no data is available)
    size_t readBytesUntil(char charactor,char *buffer,int length);
    //  return number of bytes placed in the buffer
    
    unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
private:
    //  rx buffer array
    //unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
    //  head index
    volatile rx_buffer_index_t _rx_buffer_head;
    volatile rx_buffer_index_t _rx_buffer_tail;
    int timer_ms;
    //  attach rx
    void serial_rx(void);
    
    int timedRead();
    Timer timer;
    unsigned long _timeout;      // number of milliseconds to wait for the next char before aborting timed read
    unsigned long _startMillis;  // used for timeout measurement
};

#endif

