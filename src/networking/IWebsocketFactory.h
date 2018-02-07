#ifndef IWEBSOCKETFACTORY_H
#define IWEBSOCKETFACTORY_H

#include "IWebsocket.h"
#include <stdint.h>
//the actual implementation will be platform dependent, and therefore in the platforms folder.

class IWebsocketFactory 
{
    public:
        static IWebsocket* GetInstance(uint16_t port);
};

#endif