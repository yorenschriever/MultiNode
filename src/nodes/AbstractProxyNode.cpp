#include "ProxyNode.h"
#include "../Debug.h"
#include "../NodeManager.h"

#include "../networking/IUDPSocketFactory.h"


//#define BROADCASTADDRESS 0xFFFFFFFF



AbstractProxyNode::AbstractProxyNode(){
	Title="ProxyNode";

	//setCommunicationObject(PROXYPORT);
	//comm->onMessage(std::bind(&ProxyNode::handleMsg, this,_1,_2,_3));
	//comm->begin();

	//udp->begin(PROXYPORT);
	ChannelSerializer::init();

	NodeManager::AutoProcessNode(this);
}
AbstractProxyNode::~AbstractProxyNode(){}

void setCommunicationObject(uint16_t port){}

void AbstractProxyNode::CreateReceiver(std::string Name)
{
	CreateOutputSocket(Name,Push);
}

void AbstractProxyNode::CreateTransmitter(std::string Name)
{
	CreateInputSocket(Name,Push,0);
}

void AbstractProxyNode::CreateAndConnectTransmitter(OutputSocket* sock)
{
	std::string name = sock->Name;
	CreateInputSocket(name,Push,0);
	sock->Connect(GetInputSocket(name));
}

void AbstractProxyNode::CreateAndConnectReceiver(InputSocket* sock)
{
	std::string name = sock->Name;
	CreateOutputSocket(name,Push);
	sock->Connect(GetOutputSocket(name));
}

void AbstractProxyNode::CreateAndConnectTransmitter(std::string name,OutputSocket* sock)
{
	CreateInputSocket(name,Push,0);
	sock->Connect(GetInputSocket(name));
}

void AbstractProxyNode::CreateAndConnectReceiver(std::string name,InputSocket* sock)
{
	CreateOutputSocket(name,Push);
	sock->Connect(GetOutputSocket(name));
}

void AbstractProxyNode::DeleteReceiver(std::string Name)
{
	DeleteOutputSocket(Name);
}

void AbstractProxyNode::DeleteTransmitter(std::string Name)
{
	DeleteInputSocket(Name);
}

void AbstractProxyNode::ProcessInternal(Socket* caller)
{
	if (caller==0){
		//no calling socket means we got an autoprocessing call from the nodemanager.
		//this means we are going to look for any packets and distribute them to the 
		//output sockets
		//receiveValues();
		comm->loop();
	} else {
		//if we are processing a call from a socket, this means we have to broadcast this
		//value over the network
		sendValue(caller);
	}
}

void AbstractProxyNode::sendValue(Socket* socket)
{
	char buf[150];
	int actualLen = ChannelSerializer::createMessage(buf, socket->Name, socket->GetValue());

	//udp->send(BROADCASTADDRESS,PROXYPORT,buf,actualLen);
	comm->sendMessage(buf,actualLen);
	Debug::Info(buf);
}

void AbstractProxyNode::handleMsg(uint8_t num, uint8_t * payload, size_t length)
{ 
		Debug::Info("Got: " + std::string((const char*)payload, length));

		if (ChannelSerializer::parseMessage((char*)payload,length,this))
		{
			//Debug::Info("Setting channel/value:");
			//Debug::Info(String(ChannelSerializer::channelName.c_str()));
			//Debug::Info(String(ChannelSerializer::value));
			setOutput(ChannelSerializer::channelName,ChannelSerializer::value);
		}	
}

/*
void ProxyNode::receiveValues()
{
	int msglen = udp->available();
	while (msglen > 0)
	{
		char buf[150];
		udp->read(buf,msglen);

		Debug::Info("Got: " + std::string(buf, msglen));

		if (ChannelSerializer::parseMessage(buf,msglen,this))
		{
			//Debug::Info("Setting channel/value:");
			//Debug::Info(String(ChannelSerializer::channelName.c_str()));
			//Debug::Info(String(ChannelSerializer::value));
			setOutput(ChannelSerializer::channelName,ChannelSerializer::value);
		}

		msglen = udp->available();
	}
}
*/