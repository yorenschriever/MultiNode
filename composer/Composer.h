#ifndef COMPOSER_H
#define COMPOSER_H

#include "../src/nodes/Node.h"
#include <string>
#include <vector>
#include <iterator> 

/***
 * All UI task grouped in one nice entrypoint. Delegates all operations
 * to their corresponding parts in the runtime core.
 * 
 * CAn be used as easy entrypoint when creating other ui's. 
 */

class Composer
{
    public:
        void CreateNode(std::string type);
        void Deletenode(int id);
        void SetName(int id, std::string name);
        void Move(int id, int x, int y);

        void Connect(int ida, std::string inputsocket, int idb, std::string outputsocket);
        void Disconnect(int id, std::string inputsocket);

        Node* GetNode(int id);
        
        //std::iterator<Node*> GetNodeIterator();
        //std::vector<std::string> GetAllNodeTypes();



    

};

#endif