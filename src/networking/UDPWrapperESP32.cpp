/*
#include "UDPWrapperESP32.h"

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
}
*/