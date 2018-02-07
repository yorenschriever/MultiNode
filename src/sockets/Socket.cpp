#include "Socket.h"
#include "../debug.h"

Node* Socket::GetNode()
{
	return node;
}

Socket::Socket()
{
}

Socket::Socket(Node* parent, std::string Name, SocketDrive drive)
{
	this->node = parent;
	this->Name = Name;
	this->drive = drive;
}

void Socket::Connect(Socket* other){
	//TODO: niet toestaan als inpush met outpull is verbonden

    //Debug::Info(String("Connecting ") + String(node->Title.c_str()) + "." + String(Name.c_str()) + " to " + String(other->node->Title.c_str()) + "." + String(other->Name.c_str()) );
	Debug::Info("Connecting " + node->Title + "." + Name + " to " + other->node->Title + "." + other->Name);

	if (other==0){
		Debug::Error("connecting socket failed");
		return;
	}
	
	connectedSocket = other;
	other->connectedSocket = this;

}

SocketDrive Socket::GetDrive(){
	return drive;
}

void Socket::Disconnect(){
	if (connectedSocket==0)
		return;
	connectedSocket->connectedSocket = 0;
	connectedSocket = 0;
}

Socket* Socket::GetConnectedSocket()
{
	return connectedSocket;
}