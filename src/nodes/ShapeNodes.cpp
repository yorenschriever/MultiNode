
#include "ShapeNodes.h"

RectangleNode::RectangleNode()
{
	Title="Rectangle";
	CreateInputSocket("width",Pull,0);
	CreateInputSocket("height",Pull,0);
}

bool RectangleNode::intersects(Position p){
	applyPositionAndTranslation(&p);

	return (abs(p.x) < getInput("height") && abs(p.y) < getInput("width"));
}


CircleNode::CircleNode()
{
	Title="Circle";
	CreateInputSocket("radius",Pull,0);
}

bool CircleNode::intersects(Position p){
	applyPositionAndTranslation(&p);

	float r = getInput("radius");
	return (p.x*p.x + p.y*p.y) < r*r;
}