#include "NodeManager.h"
#include <string.h>
#include <algorithm>
#include "Debug.h"

//initialize static vectors
std::map<int, Node*> NodeManager::allNodes  = std::map<int, Node*>(); 
std::vector<Node*> NodeManager::autoProcessNodes = std::vector<Node*>();

int NodeManager::maxid=0;
unsigned int NodeManager::FrameNumber=0;
std::map<int, Node*>::iterator NodeManager::iterator = std::map<int, Node*>::iterator(); 

void NodeManager::AutoProcess(){
  //Process all nodes that were marked to automatically processed	
  for (std::vector<Node*>::iterator it = autoProcessNodes.begin() ; it != autoProcessNodes.end(); ++it)
  {
    Node* n = (*it);
    n->Process();
  }

  FrameNumber++;
}
 
void NodeManager::AddNode(Node* node)
{
  //give the node an id, if it doesnt have one yet.

  //the algorithm used here allows nodes with ids to be deserialised
  //with conservation of id. Afterwards, new nodes can be added, but only 
  //if the NodeManager can choose their id.
  
  int newid;
  if (node->id==0){

    //newly created node, generate unique id:
    do {
      newid = ++NodeManager::maxid;
    } while(allNodes.count(newid)!=0);


  } else {
    //imported node, check if id is unique

    if (allNodes.count(node->id)!=0){
      Debug::Error("Error: imported id already in use.");
      return;
    }

  }

  node->id = newid;


  //register the node.
  allNodes[node->id] = node;

  //Debug::Info("Node registered with id " + std::to_string(node->id));
  //Debug::Info("Number of registered nodes: " + std::to_string(allNodes.size()));
}

void NodeManager::AutoProcessNode(Node* node)
{
	autoProcessNodes.push_back(node);
}

void NodeManager::RemoveNode(Node* node)
{
  allNodes.erase(node->id);
  autoProcessNodes.erase(std::remove(autoProcessNodes.begin(), autoProcessNodes.end(), node), autoProcessNodes.end());

  //Debug::Info("Node removed with id " + std::to_string(node->id));
  //Debug::Info("Number of registered nodes: " + std::to_string(allNodes.size()));
}

void NodeManager::ResetIterator(){
  //Debug::Info("resetting iterator");
  iterator = allNodes.begin();
}

Node* NodeManager::GetNextNode()
{
  if (iterator==allNodes.end()){
    return 0;  
  }
  
  //Debug::Info("now at " + std::to_string((unsigned int) iterator->first)); //+ std::string(iterator->second->Title));

  Node* result = iterator->second; //GetNode(iterator->first); //
  iterator++;
  return result;
}


//get node by id
Node* NodeManager::GetNode(int id)
{
  if (allNodes.count(id)==0)
  {
    Debug::Error("Node with id not found: ");
    //Debug::Error("Node with id not found: " + std::to_string(id));
    return 0;
  }

  return allNodes[id];
}