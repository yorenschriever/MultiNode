#ifndef NODESERVICE_H
#define NODESERVICE_H

#include "../nodes/Node.h"

class NodeService
{
	
	public:
		static void MoveNode(int id, int x, int y);
		static Node* CreateNode(std::string type);
		static void DeleteNode(int id);

		static void Connect(int id1, std::string socket1, int id2, std::string socket2);
		static void Disconnect();

		static void GetAllNodes();

		static void XMLIn(char* pointer);
		//TODO function pointer for return messages
};

#endif