#include "mbed.h"
#include "SerialBridge.h"

BufferSerial _serial(USBTX, USBRX,9600,1000);
SerialBridge dev(&_serial);

int main(){

    return 0;
}