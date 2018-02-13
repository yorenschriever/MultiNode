#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>
#include "../types.h"
//#include "../sockets/InputSocket.h"
//#include "../sockets/OutputSocket.h"

class Socket;
class InputSocket;
class OutputSocket;

class Node 
{
	public:
		Node(); //Todo, constructor with title, so the title must be set for each node
		~Node();
		
		std::string Title="";
		int id=0;
		void Process();
		void Process(Socket* caller);

		InputSocket* GetInputSocket(std::string name);
		std::map<std::string, InputSocket*>* GetInputSockets();

		OutputSocket* GetOutputSocket(std::string name);
		std::map<std::string, OutputSocket*>* GetOutputSockets();

		//virtual std::map<std::string, OutputSocket*>* GetOutputSockets(){return 0;} //TODO this is done to the ui can access the outputsockets. fix this is a neat way.

//#ifdef WITHCOMPOSER
		int x,y;
//#endif

	protected:
		virtual void ProcessInternal(Socket* caller)=0; //TODO only processnodes can have this
		SOCKETTYPE getInput(std::string name);
		InputSocket* CreateInputSocket(std::string name, SocketDrive drive, SOCKETTYPE defaultValue);
		void DeleteInputSocket(std::string name);

		void setOutput(std::string name, SOCKETTYPE value);
		void setOutput(std::string name, SOCKETTYPE value, bool force); //if force is set to true, it will still send an update, even if the value has not changed

		OutputSocket* CreateOutputSocket(std::string name, SocketDrive drive);
		void DeleteOutputSocket(std::string name);

	private:
		std::map<std::string, InputSocket*> InputSockets;
		std::map<std::string, OutputSocket*> OutputSockets;
		
		unsigned int frameNumber=-1;
};

#endif
