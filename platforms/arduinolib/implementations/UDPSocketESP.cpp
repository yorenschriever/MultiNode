#include "Arduino.h"
#include "UDPSocketESP.h"

#include "../../../src/networking/IUDPSocket.h"
#include "../../../src/Debug.h"


/*
void UDPWrapperESP32::begin(int listenPort){
	Debug::Info("begin udp");
	udp.begin(listenPort);
}

void UDPWrapperESP32::send(uint32_t ip, int port, char* msg, int size){
	udp.beginPacket(ip,port);
    udp.write((unsigned char* )msg, size);
    udp.endPacket();
}

int UDPWrapperESP32::available(){
	return udp.parsePacket();
}

void UDPWrapperESP32::read(char* buffer, int len){
	udp.read((unsigned char*)buffer, len);
}*/
///////////

UDPSocketESP::UDPSocketESP(uint16_t port)
{
    udp = new WiFiUDP();
    this->port = port;
}

UDPSocketESP::~UDPSocketESP()
{
    delete udp;
}

void UDPSocketESP::begin(){
    udp->begin(port);
}

void UDPSocketESP::onMessage(MessageEvent msgevent)
{
    this->handler = msgevent;
}

bool UDPSocketESP::sendMessage(std::string txt){
    return sendMessage(txt.c_str(), txt.length());
}

//by default send to the same port, on the broadcast address
bool UDPSocketESP::sendMessage(const char* msg, int len){
    return sendMessage(BROADCASTADDRESS, this->port, msg,len);
}

bool UDPSocketESP::sendMessage(uint32_t ip, uint16_t port, const char* msg, int len){
	udp->beginPacket(ip,port);
    udp->write((unsigned char* )msg, len);
    udp->endPacket();
    return true;
}

void UDPSocketESP::loop()
{
    int len = udp->parsePacket();
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
    }
}
