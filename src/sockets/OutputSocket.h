#ifndef OUTPUTSOCKET_H
#define OUTPUTSOCKET_H

#include <string>
#include "Socket.h"

class OutputSocket : public Socket {
	public:
		OutputSocket();
		OutputSocket(Node* parent, std::string Name, SocketDrive drive);
		SOCKETTYPE GetValue() ;
		void SetValue(SOCKETTYPE value);
		void SetValue(SOCKETTYPE value, bool force);
	
	private:
		SOCKETTYPE value;
};

#endif