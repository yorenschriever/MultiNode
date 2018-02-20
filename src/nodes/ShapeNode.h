#ifndef SHAPENODE_H
#define SHAPENODE_H

#include "GraphicsNode.h"
#include "../types.h"

class ShapeNode : public GraphicsNode 
{
	public:
		ShapeNode() {};
		virtual ~ShapeNode() {};
		RGBA Color;
	private:
		RGBA colorAt(Position p); 
		virtual bool intersects(Position p)=0;
};

#endif