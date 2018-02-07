#ifndef ANTIALIASNODE_H
#define ANTIALIASNODE_H

#include "RenderNode.h"
#include "../types.h"

class AntiAliasNode : public RenderNode
{
	public:
		AntiAliasNode();
	private:
		RGBA GetStackedColor(Position p);
		RGBA colorAt(Position p) {}; 
};

#endif