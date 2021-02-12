#include "BufferSerial.h"

BufferSerial::BufferSerial(PinName tx, PinName rx,int baud,int timeout)
    :RawSerial(tx,rx,baud)
{
    //  initialize functions
    _rx_buffer_head = 0;
    _rx_buffer_tail = 0;
    //  time out
    timer_ms = timeout;
    timer.start();
    //  attach
    RawSerial::attach(callback(this,&BufferSerial::serial_rx), Serial::RxIrq);
}

int BufferSerial::available(void)
{
    return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}

int BufferSerial::read(void)
{
    if (_rx_buffer_head == _rx_buffer_tail) {
        return -1;
    } else {
        unsigned char c = _rx_buffer[_rx_buffer_tail];
        _rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
        return c;
    }
}

size_t BufferSerial::readBytesUntil(char charactor,char* buffer,int length)
{
    size_t index = 0;
    while (index < length) {
        int c = timedRead();
        if (c < 0 || c == charactor){
            break;
        }
        *buffer++ = (char)c;
        index++;
    }
    return index;
}

void BufferSerial::serial_rx(void)
{
    while(RawSerial::readable()) {
        unsigned char c = RawSerial::getc();
        rx_buffer_index_t i = (unsigned int)(_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;
        if (i != _rx_buffer_tail) {
            _rx_buffer[_rx_buffer_head] = c;
            _rx_buffer_head = i;
        }
    }
}

int BufferSerial::timedRead()
{
    int c;
    timer.reset();
    _startMillis = timer.read_ms();
    do {
        c = read();
        if (c >= 0) return c;
    } while(timer.read_ms() - _startMillis < _timeout);
    return -1;     // -1 indicates timeout
}

