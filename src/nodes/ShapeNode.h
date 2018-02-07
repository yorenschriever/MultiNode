#ifndef SHAPENODE_H
#define SHAPENODE_H

#include "RenderNode.h"
#include "../types.h"

class ShapeNode : public RenderNode 
{
	public:
		RGBA Color;
	private:
		RGBA colorAt(Position p); 
		virtual bool intersects(Position p)=0;
};

#endif