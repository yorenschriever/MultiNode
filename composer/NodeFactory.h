#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include <string>
#include "../src/nodes/Node.h"
#include "../src/nodes/ProcessNodes.h"
#include "../src/nodes/ShapeNodes.h"

/**
 * Will create a node of a certain type
 */ 

class NodeFactory
{
    Node* create(std::string type){
        if (type=="Circle") 
            return new CircleNode();

        else if (type=="Rectangle")
            return new RectangleNode();

        else if (type=="Sum")
            return new SumNode();
    }
};

#endif