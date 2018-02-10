#include "UDPSocketUnix.h"

#include "../../../src/networking/IUDPSocket.h"
#include "../../../src/Debug.h"

//TODO this class needs to be implemented

UDPSocketUnix::UDPSocketUnix(uint16_t port)
{
    //udp = new WiFiUDP();
    this->port = port;
}

UDPSocketUnix::~UDPSocketUnix()
{
    //delete udp;
}

void UDPSocketUnix::begin(){
    //udp->begin(port);
}

void UDPSocketUnix::onMessage(MessageEvent msgevent)
{
    this->handler = msgevent;
}

bool UDPSocketUnix::sendMessage(std::string txt){
    //return sendMessage(txt.c_str(), txt.length());
    return false;
}

//by default send to the same port, on the broadcast address
bool UDPSocketUnix::sendMessage(const char* msg, int len){
    return sendMessage(BROADCASTADDRESS, this->port, msg,len);
}

bool UDPSocketUnix::sendMessage(uint32_t ip, uint16_t port, const char* msg, int len){
	//udp->beginPacket(ip,port);
    //udp->write((unsigned char* )msg, len);
    //udp->endPacket();
    //return true;
    return false;
}

void UDPSocketUnix::loop()
{
    /*int len = udp->parsePacket();
    while(len>0)
    {
        if (len > UDPBUFSIZE){
            Debug::Error("Message too large for UDP buffer");
            len=UDPBUFSIZE;
        }

        unsigned char buf[UDPBUFSIZE];
        udp->read(buf,len);

        if (this->handler !=0 )
            this->handler(0, buf, len);
            
        len = udp->parsePacket();
    }*/
}
