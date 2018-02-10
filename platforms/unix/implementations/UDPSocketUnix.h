#ifndef UDPSOCKETUNIX_H
#define UDPSOCKETUNIX_H

#include "../../../src/networking/IUDPSocket.h"

const int UDPBUFSIZE = 150;
const uint32_t BROADCASTADDRESS = 0xFFFFFFFF;

class UDPSocketUnix : public IUDPSocket
{
    public: 
        UDPSocketUnix(uint16_t port);
        ~UDPSocketUnix();

        void begin();

        //void handleMsg(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

        void onMessage(MessageEvent msgevent);

        bool sendMessage(std::string txt);
        bool sendMessage(const char* msg, int len);
        bool sendMessage(uint32_t ip, uint16_t port, const char* msg, int len);

        void disconnect(uint8_t id);
        void loop();

    private:
        //WebSocketsServer* inner;
        //WiFiUDP* udp;
        MessageEvent handler=0;
        uint16_t port;
};

#endif