#ifndef IUDPSOCKET_H
#define IUDPSOCKET_H

#include <string>
#include <functional>
#include "ICommunication.h"
//the actual implementation will be platform dependent, and therefore in the platforms folder.

class IUDPSocket : public ICommunication
{
    public: 
        virtual bool sendMessage(uint32_t ip, uint16_t port, const char* msg, int len)=0;
};



#endif