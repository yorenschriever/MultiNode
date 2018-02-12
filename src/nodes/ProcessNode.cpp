
#include "ProcessNode.h"
#include "../sockets/OutputSocket.h"
#include "../NodeManager.h"
#include "../Debug.h"
#include <string>
#include <iostream>

OutputSocket* ProcessNode::GetOutputSocket(std::string name){
	//TODO: optimize, i think its going to look up twice.
	//also better error handling?
	if (OutputSockets.count(name)==0)
	{
		//Debug::Error(String("Output socket not found: ") + String(name.c_str()));
		//Debug::Error(String("Output socket count: ") + String(OutputSockets.size()));
		Debug::Error("Output socket not found: " + name);
		return 0;
	}

	return OutputSockets[name];
}

OutputSocket* ProcessNode::CreateOutputSocket(std::string name, SocketDrive drive)
{
	OutputSocket* sock = new OutputSocket(this,name,drive);
	OutputSockets[name] = sock;

	Debug::Info("Create outputsocket: " + name);
	//Debug::Error(String("Output socket count: ") + String(OutputSockets.size()));
	return sock;
}

void ProcessNode::DeleteOutputSocket(std::string name)
{
	delete OutputSockets[name];
	OutputSockets.erase(name);
}

void ProcessNode::setOutput(std::string name, SOCKETTYPE value)
{
	setOutput(name, value, false);
}

void ProcessNode::setOutput(std::string name, SOCKETTYPE value, bool force)
{
	OutputSocket* sock = GetOutputSocket(name);
	if (sock==0)
		return ; //TODO

	sock->SetValue(value, force);
}


std::map<std::string, OutputSocket*>* ProcessNode::GetOutputSockets()
{
	return &OutputSockets;
}
