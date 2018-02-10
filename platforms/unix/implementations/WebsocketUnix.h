#ifndef WEBSOCKETUNIX_H
#define WEBSOCKETUNIX_H

#include "../../../src/networking/IWebsocket.h"

class WebsocketUnix : public IWebsocket
{
    public: 
        WebsocketUnix(uint16_t port, const char* path);
        ~WebsocketUnix();

        void begin();

        //void handleMsg(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

        void onMessage(MessageEvent msgevent);

        bool sendMessage(std::string txt);
        bool sendMessage(const char* msg, int len);

        void disconnect(uint8_t id);
        void loop();

    private:
        //WebSocketsServer* inner;
        MessageEvent handler=0;
};

#endif