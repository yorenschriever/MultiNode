
#include "WebsocketUnix.h"
#include "../../../src/networking/IWebsocket.h"
#include "../../../src/Debug.h"

//using namespace std::placeholders;

WebsocketUnix::WebsocketUnix(uint16_t port, const char* path)
{
    //inner = new WebSocketsServer(port, "/", "MultiNode");
}

WebsocketUnix::~WebsocketUnix()
{
    //delete inner;
}

void WebsocketUnix::begin(){
    //inner->begin();
}

/*
void WebsocketUnix::handleMsg(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
    //Debug::Info("websocketesp handlemsg" + std::to_string(type) + " / "+ std::to_string(WStype_TEXT));

    if (type !=  WStype_TEXT)//TODO also handle error
        return;

    if (this->handler==0)
        Debug::Error("No handler set");

    if (this->handler!=0)
        this->handler(num, payload, length);
}*/

void WebsocketUnix::onMessage(MessageEvent msgevent)
{
    this->handler = msgevent;
    //inner->onEvent(std::bind(&WebsocketESP::handleMsg, this, _1, _2, _3, _4));
}

bool WebsocketUnix::sendMessage(std::string txt){
    //return inner->broadcastTXT(txt.c_str(), txt.length());
    return false;
}

bool WebsocketUnix::sendMessage(const char* msg, int len){
    //return inner->broadcastTXT(msg, len);
    return false;
}

void WebsocketUnix::disconnect(uint8_t id)
{
    //inner->disconnect(id);
}

void WebsocketUnix::loop()
{
    //inner->loop();
}
