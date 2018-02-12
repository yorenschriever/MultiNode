#ifndef PROCESSNODE_H
#define PROCESSNODE_H

#include "Node.h"
#include "../sockets/OutputSocket.h"
#include <map>

class ProcessNode : public Node
{
	public:
		OutputSocket* GetOutputSocket(std::string name);
		virtual std::map<std::string, OutputSocket*>* GetOutputSockets();

	protected:
		void setOutput(std::string name, SOCKETTYPE value);
		void setOutput(std::string name, SOCKETTYPE value, bool force); //if force is set to true, it will still send an update, even if the value has not changed

		OutputSocket* CreateOutputSocket(std::string name, SocketDrive drive);
		void DeleteOutputSocket(std::string name);

	private:
		std::map<std::string, OutputSocket*> OutputSockets;
};

#endif