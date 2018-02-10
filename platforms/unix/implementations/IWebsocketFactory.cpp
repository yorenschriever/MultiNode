#include "../../../src/networking/IWebsocketFactory.h"
#include "../../../src/networking/IWebsocket.h"

#include "WebsocketUnix.h"
#include <stdint.h>

IWebsocket* IWebsocketFactory::GetInstance(uint16_t port)
{
    return new WebsocketUnix(port, "/");
}