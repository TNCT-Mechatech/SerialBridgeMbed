#include "mbed.h"
#include "SerialBridge.h"

BufferSerial _serial(USBTX, USBRX,9600,1000);
SerialBridge dev(&_serial);

Vector3 msg0;
Vector3 msg1;


int main()
{
    dev.add_frame(0, &msg1);
    dev.wait_host("TestVect3"); //ホストの応答を待ちます。

    return 0;
}

void loop(){
    while(1){
        if(dev.read() == 0){
            msg0 = msg1;
            dev.write(0, &msg0);
        }
        wait_ms(20);
    }
}