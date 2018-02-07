#include "../../../src/networking/IWebsocketFactory.h"
#include "../../../src/networking/IWebsocket.h"

#include "WebsocketESP.h"
#include <stdint.h>

IWebsocket* IWebsocketFactory::GetInstance(uint16_t port)
{
    return new WebsocketESP(port, "/");
}