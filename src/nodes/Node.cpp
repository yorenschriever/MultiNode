//#include <stdlib.h>
#include <string>
#include "Node.h"
#include "../Debug.h"
#include "../NodeManager.h"
#include "../sockets/InputSocket.h"

Node::Node(){
  NodeManager::AddNode(this);
}

Node::~Node(){
  NodeManager::RemoveNode(this);
}

//this process method is being called from the nodemanager.autoprocess
void Node::Process()
{
	Process(0);
}

//this process method will be called when a socket updates.
void Node::Process(Socket* caller)
{
	//Debug::Info("Process "+Title);
	
	//TODO should the entirt node be either push or pull, or should we allow mixed used of push and pull within a node?
	if (caller && caller->GetDrive()==Pull && 
	    frameNumber == NodeManager::FrameNumber){
			//Debug::Info("Already processed");
			return;
	}

	//register the framenumber for which we calcualted the value
	frameNumber = NodeManager::FrameNumber;

	//if the caller is the nodemanager, always process
	//if the caller is a push node, always process
	ProcessInternal(caller);

}

InputSocket* Node::GetInputSocket(std::string name){
	//TODO: optimize, i think its going to look up twice.
	//also better error handling?
	if (InputSockets.count(name)==0)
	{
		//Debug::Error(String("Input socket not found") + String(name.c_str()));
		Debug::Error("Input socket not found" + name);
		return 0;
	}

	return InputSockets[name];
}

void Node::CreateInputSocket(std::string name, SocketDrive drive, SOCKETTYPE defaultvalue)
{
	InputSockets[name] = new InputSocket(this,name,drive,defaultvalue);
}

void Node::DeleteInputSocket(std::string name)
{
	delete InputSockets[name];
	InputSockets.erase(name);
}

SOCKETTYPE Node::getInput(std::string name){
	InputSocket* sock = GetInputSocket(name);
	if (sock==0)
		return 0; //TODO

	return sock->GetValue();
}

std::map<std::string, InputSocket*>* Node::GetInputSockets()
{
	return &InputSockets;
}
