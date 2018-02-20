#ifndef SHAPENODES_H
#define SHAPENODES_H

#include "ShapeNode.h"
#include "../types.h"

class RectangleNode : public ShapeNode
{
	public:
		RectangleNode();		
		~RectangleNode() {}
	private:
		bool intersects(Position p);

		InputSocket* ptrWidth;
		InputSocket* ptrHeight;
};

class CircleNode : public ShapeNode
{
	public:
		CircleNode();	
		~CircleNode(){}	

	private:
		bool intersects(Position p);

		InputSocket* ptrRadius;
};

#endif
