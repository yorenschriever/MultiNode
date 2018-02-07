#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include "nodes/Node.h"
#include <vector>
#include <map>

class NodeManager
{
  protected:
    static std::map<int, Node*> allNodes ;
    static std::vector<Node*> autoProcessNodes;

  private:
    static int maxid;
	  static std::map<int, Node*>::iterator iterator; 

  public: 		
		//execute the autoprocessing. 
  	static void AutoProcess(); //TODO MISNOMER

  	// adds an instance of a node to the patch.
  	// it will also set the node id to a unique number, it it was not set.
  	// Nodes will register themselves in their constructor. No need to add them manually.
  	static void AddNode(Node* node); 

  	//Register a node for auto processing
  	static void AutoProcessNode(Node* node); 

  	// Nodes will remove themselves in their destructor. No need to remove them manually.
  	static void RemoveNode(Node* node);

  	//get all nodes
    //static std::vector<Node*> GetNodes();

		static void ResetIterator();
		static Node* GetNextNode();

    //get node by id
    static Node* GetNode(int id);

		//the framenumber that is currently begin processed.
		//will be updated on execution of AutoProcess().
		//pull nodes will only execute once per frame number
		static unsigned int FrameNumber;
};

#endif