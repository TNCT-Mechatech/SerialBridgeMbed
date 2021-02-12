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
        msg0.data.data.x = 0.123;
        msg0.data.data.y = 0.456;
        msg0.data.data.z = 0.321;

        dev.write(0, &msg0);

        wait_ms(20);
    }
}