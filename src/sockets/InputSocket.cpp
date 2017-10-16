#include "InputSocket.h"
#include "../Debug.h"

InputSocket::InputSocket(Node* parent, std::string Name, SocketDrive drive, SOCKETTYPE defaultValue) : Socket(parent, Name, drive) 
{ 
  this->constantValue = defaultValue;
}

InputSocket::InputSocket() : Socket() { }


SOCKETTYPE InputSocket::GetValue()
{
    //Debug::Info("inputsocket getvalue");

	if (drive == Push)
		return constantValue;

	if (connectedSocket != 0)
	{
		return this->connectedSocket->GetValue();
	}
	else 
	{
		return constantValue;
	} 
}


void InputSocket::SetValue(SOCKETTYPE value){
	//Debug::Info("inputsocket setvalue ");

	this->constantValue=value;
	if (drive==Push)
		GetNode()->Process(this);
}


