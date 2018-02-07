#ifndef SOCKET_H
#define SOCKET_H

#include <map>
#include <string>
#include "../types.h"
#include "../nodes/Node.h"

#ifndef SOCKETTYPE
	#define SOCKETTYPE float
	#define SOCKETTYPETOSTR "%f"
	#define SOCKETTYPEPARSE atof
#endif

class Node; //forward declaration to avoid circular include

class Socket
{
	public:
		Socket();
		Socket(Node* parent, std::string Name, SocketDrive drive);
		std::string Name="";
		void Disconnect();
		void Connect(Socket* other);
		Node* GetNode();
		virtual SOCKETTYPE GetValue() =0;
		virtual void SetValue(SOCKETTYPE value) =0;
		SocketDrive GetDrive();
		Socket* GetConnectedSocket();

	protected:
		Node* node=0;
		Socket* connectedSocket=0;
		SocketDrive drive;
};

#endif