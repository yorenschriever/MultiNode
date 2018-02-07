/*
#ifndef UDPWRAPPERESP32_H
#define UDPWRAPPERESP32_H

#include "UDPWrapper.h"
#include "Arduino.h"
#include <WiFiUdp.h>

//implementation for ESP32
class UDPWrapperESP32 : public UDPWrapper
{
   	public:
		void begin(int listenPort);
		void send(uint32_t ip, int port, char* msg, int size);
		int available();
		void read(char* buffer, int len);

	protected:
   		WiFiUDP udp;
};

#endif
*/