#ifndef IUDPSOCKETFACTORY_H
#define IUDPSOCKETFACTORY_H

#include "IUDPSocket.h"
#include <stdint.h>
//the actual implementation will be platform dependent, and therefore in the platforms folder.

class IUDPSocketFactory 
{
    public:
        static IUDPSocket* GetInstance(uint16_t port);
};

#endif