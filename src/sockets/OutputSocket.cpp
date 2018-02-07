#include "OutputSocket.h"
#include "../debug.h"

OutputSocket::OutputSocket(Node* parent, std::string Name, SocketDrive drive) : Socket(parent, Name, drive) { }
OutputSocket::OutputSocket() : Socket() { }

SOCKETTYPE OutputSocket::GetValue()
{
	//Debug::Info("outputsocket getvalue");
	if (drive==Pull)	
		GetNode()->Process(this);
	return value;
}

void OutputSocket::SetValue(SOCKETTYPE value)
{
	SetValue(value, false);
}

void OutputSocket::SetValue(SOCKETTYPE value, bool force)
{
	//Debug::Info("outputsocket setvalue");
	//we do not want to keep pushing unchanged data. if nothing has changed, there is no way
	//it will affect following nodes
    if (this->value == value && !force)
    	return;

	this->value=value;

	if (drive == Push && connectedSocket != 0)
	{
		//TODO: it is nowhere ensured that othersocket in an inputsocket. we should  check this,
		//and also make it forbidden to join to output socke
		this->connectedSocket->SetValue(value);
	}
}