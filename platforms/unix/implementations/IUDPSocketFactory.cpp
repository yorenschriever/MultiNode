#include "../../../src/networking/IUDPSocketFactory.h"
#include "../../../src/networking/IUDPSocket.h"

#include "UDPSocketUnix.h"
#include <stdint.h>

IUDPSocket* IUDPSocketFactory::GetInstance(uint16_t port)
{
    return new UDPSocketUnix(port);
}