
#include "ShapeNodes.h"
#include "../sockets/InputSocket.h"

RectangleNode::RectangleNode()
{
	Title="Rectangle";
	ptrWidth = CreateInputSocket("width",Pull,0);
	ptrHeight = CreateInputSocket("height",Pull,0);
}

bool RectangleNode::intersects(Position p){
	applyPositionAndTranslation(&p);

	//return (abs(p.x) < getInput("height") && abs(p.y) < getInput("width"));
	return (abs(p.x) < ptrHeight->GetValue() && abs(p.y) < ptrWidth->GetValue());
}


CircleNode::CircleNode()
{
	Title="Circle";
	ptrRadius = CreateInputSocket("radius",Pull,0);
}

bool CircleNode::intersects(Position p){
	applyPositionAndTranslation(&p);

	float r = ptrRadius->GetValue(); //getInput("radius");
	return (p.x*p.x + p.y*p.y) < r*r;
}