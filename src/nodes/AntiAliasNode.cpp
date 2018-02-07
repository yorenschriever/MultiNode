#include "AntiAliasNode.h"

AntiAliasNode::AntiAliasNode()
{
	CreateInputSocket("width",Pull,0);
}

RGBA AntiAliasNode::GetStackedColor(Position p){
	if (UnderlyingNode==0)
		return TRANSPARENT;

	float w = getInput("width");
	//Debug::Info("width="+String(w));

	int r,g,b,a=0;

	RGBA c  = UnderlyingNode->GetStackedColor(p);
	RGBA cu = UnderlyingNode->GetStackedColor(p.Translate(w,    w));
	RGBA cd = UnderlyingNode->GetStackedColor(p.Translate(-1*w, w));
	RGBA cl = UnderlyingNode->GetStackedColor(p.Translate(-1*w, -1*w));
	RGBA cr = UnderlyingNode->GetStackedColor(p.Translate(w,    -1*w));

	//r = (c.a*c.r + cu.a*cu.r + cd.a*cd.r + cl.a*cl.r + cr.a*cr.r)/5;
	//g = (c.a*c.g + cu.a*cu.g + cd.a*cd.g + cl.a*cl.g + cr.a*cr.g)/5;
	//b = (c.a*c.b + cu.a*cu.b + cd.a*cd.b + cl.a*cl.b + cr.a*cr.b)/5;
	////a = ((int)c.a + cu.a + cd.a + cl.a + cr.a)/5;

	r = (c.r + cu.r + cd.r + cl.r + cr.r)/5;
	g = (c.g + cu.g + cd.g + cl.g + cr.g)/5;
	b = (c.b + cu.b + cd.b + cl.b + cr.b)/5;

	RGBA result;

	result.r = r;
	result.g = g;
	result.b = b;
	result.a = 1;

	return result;
}