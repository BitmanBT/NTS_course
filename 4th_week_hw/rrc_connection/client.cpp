#include "RRCConnectionRequest_encoder.h"
#include "RRCConnectionSetupComplete_encoder.h"
#include "SendReceive.h"

int main()
{
    uint8_t *buffer;
    ssize_t len;
    usleep(100);
    RRCConnectionRequest_encoder(&buffer, &len);
    tx_send(&buffer, &len, 50301);
    free(buffer);
}