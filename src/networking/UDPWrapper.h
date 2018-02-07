/*
#ifndef UDPWRAPPER_H
#define UDPWRAPPER_H

//the interface
class UDPWrapper
{
	public:
		//opens a udp port te receive messages
		virtual void begin(int listenPort);

		//send the message to the given port
		virtual void send(uint32_t ip, int port, char* msg, int size);

		//if no udp packet is received: returns 0
		//returns the length of the received packet otherwise
		virtual int available();

		//read the received packet into buffer
		virtual void read(char* buffer, int len);
};

#endif
*/