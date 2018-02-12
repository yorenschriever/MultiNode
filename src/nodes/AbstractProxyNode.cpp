#include "ProxyNode.h"
#include "../Debug.h"
#include "../NodeManager.h"

#include "../networking/IUDPSocketFactory.h"
#include "../../lib/gason/gason.h"

AbstractProxyNode::AbstractProxyNode(){
	Title="ProxyNode";
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
	//int actualLen = ChannelSerializer::createMessage(buf, socket->Name, socket->GetValue());
	int actualLen = createMessage(buf, socket->Name, socket->GetValue());

	//udp->send(BROADCASTADDRESS,PROXYPORT,buf,actualLen);
	comm->sendMessage(buf,actualLen);
	Debug::Info(buf);
}

void AbstractProxyNode::handleMsg(uint8_t num, uint8_t * payload, size_t length)
{ 
	Debug::Info("Got: " + std::string((const char*)payload, length));

	char *endptr;
	JsonValue value;
	JsonAllocator allocator;

	int status = jsonParse((char*) payload, &endptr, &value, allocator);
	if (status != JSON_OK) {
		Debug::Error(std::string("Unable to parse JSON: ") + jsonStrError(status)) ;
		return;
	}    


	if (value.getTag() != JSON_OBJECT){
		Debug::Error("message is wrong type");
		return;
	}

	std::string channelName;
	SOCKETTYPE channelValue;
	bool chset =false, valset=false;

	for (auto i : value) 
	{
        if (!strcmp("ch",i->key))	
		{
			channelName = std::string(i->value.toString());
			if (!channelExists(channelName))
			{
				//Debug::Error("channel does not exist");
				return;
			}
			chset = true;
		}
		else if (!strcmp("val",i->key))	
		{
			valset=true;
			channelValue = i->value.toNumber();
		}
    }

	

	if (!chset || !valset)
		return;
		
	//Debug::Info("Setting " + channelName + " to" + std::to_string(channelValue));
	setOutput(channelName,channelValue);

}

int AbstractProxyNode::createMessage(char* buf, std::string socketname, SOCKETTYPE value)
{
	return sprintf(buf, "{\"ch\":\"%s\",\"val\":" SOCKETTYPETOSTR "}", socketname.c_str(), value);
}

inline bool AbstractProxyNode::channelExists(std::string channel)
{
  return GetOutputSocket(channel)!=0;
}
