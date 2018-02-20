#ifndef ANTIALIASNODE_H
#define ANTIALIASNODE_H

#include "GraphicsNode.h"
#include "../types.h"

class AntiAliasNode : public GraphicsNode
{
	public:
		AntiAliasNode();
		~AntiAliasNode(){};
	private:
		RGBA GetStackedColor(Position p);
		RGBA colorAt(Position p) =0; 
};

#endif