#include "mbed.h"
#include "SerialBridge.h"

#include <Vector3.h>

#define TX {YOUR_TX_PIN}
#define RX {YOUR_RX_PIN}

BufferSerial _serial(TX, RX,9600,1000);
SerialBridge dev(&_serial);

Serial pc(USBTX,USBRX);

Vector3 msg0;

int main()
{
    dev.add_frame(0, &msg0);

    //dev.wait_host("TestVect3"); // マイコン間通信のため不要

    while(1) {
        int value = dev.read();
        if(value == 0){
            float x = msg0.data.data.x;
            float y = msg0.data.data.y;
            float z = msg0.data.data.z;
            pc.printf("x:%f y:%f z:%f \n\r",x,y,z);
        }else{
            pc.printf("error:%d\n\r",value);
        }
        wait_ms(50);    //  エラーが発生する場合は遅延を調整してください
    }
    return 0;
}