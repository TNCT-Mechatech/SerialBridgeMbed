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

    while(1) {
        msg0.data.data.x = 0.123;
        msg0.data.data.y = 0.456;
        msg0.data.data.z = 0.321;

        dev.write(0, &msg0);
        dev.read();
        wait_ms(40);    //  遅延を調整することでパフォーマンスが改善します(各環境でチューニングしてください)
    }
    return 0;
}