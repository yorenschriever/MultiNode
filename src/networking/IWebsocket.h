#ifndef IWEBSOCKET_H
#define IWEBSOCKET_H

#include <string>
#include <functional>
#include "ICommunication.h"
//the actual implementation will be platform dependent, and therefore in the platforms folder.

class IWebsocket : public ICommunication
{
    public:
        virtual void disconnect(uint8_t id)=0;
};

#endif