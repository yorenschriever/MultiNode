#ifndef INPUTSOCKET_H
#define INPUTSOCKET_H

#include "Socket.h"

class InputSocket : public Socket {
	public:
		InputSocket();
		InputSocket(Node* parent, std::string Name, SocketDrive drive, SOCKETTYPE defaultValue);
		SOCKETTYPE GetValue() ;
		void SetValue(SOCKETTYPE value);

	private:
		SOCKETTYPE constantValue;
};

#endif