#include "../../../src/networking/IUDPSocketFactory.h"
#include "../../../src/networking/IUDPSocket.h"

#include "UDPSocketESP.h"
#include <stdint.h>

IUDPSocket* IUDPSocketFactory::GetInstance(uint16_t port)
{
    return new UDPSocketESP(port);
}