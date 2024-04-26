#include "RRCConnectionSetup_encoder.h"
#include "SendReceive.h"

int main()
{
    uint8_t *buffer;
    ssize_t len;
    rx_receive(&buffer, &len, 50301);
    free(buffer);
}