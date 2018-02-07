
#include "ShapeNode.h"

RGBA ShapeNode::colorAt(Position p)
{
	if (intersects(p))
		return Color;
	else
		return TRANSPARENT;
}