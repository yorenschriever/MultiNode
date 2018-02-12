
#include "GraphicsNode.h"
#include "../types.h"

#include "../sockets/InputSocket.h"

GraphicsNode::GraphicsNode()
{
	ptrX  =  CreateInputSocket("x",Pull,0);
	ptrY =   CreateInputSocket("y",Pull,0);
	ptrRot = CreateInputSocket("rot",Pull,0);
}

RGBA GraphicsNode::GetStackedColor(Position p){
	RGBA thisLayerColor = colorAt(p);

	if (thisLayerColor.a==1) return thisLayerColor;

	RGBA underlyingLayerColor;
	if (UnderlyingNode !=0)
		underlyingLayerColor = UnderlyingNode->GetStackedColor(p);
	else 
		underlyingLayerColor = TRANSPARENT;

	if (thisLayerColor.a==0) return underlyingLayerColor;

	RGBA result;

	result.r = thisLayerColor.r * thisLayerColor.a + underlyingLayerColor.r * (1.0-thisLayerColor.a);
	result.g = thisLayerColor.g * thisLayerColor.a + underlyingLayerColor.g * (1.0-thisLayerColor.a);
	result.b = thisLayerColor.b * thisLayerColor.a + underlyingLayerColor.b * (1.0-thisLayerColor.a);
	result.a = 1;

	return result;
}

void GraphicsNode::applyPositionAndTranslation(Position* p)
{
	//We want to apply rotation first, then translation.
	//But since the rotate the 'camera' instead of the object itself,
	//we have to apply these operations in the opposite direction.

	//apply translation
	p->TranslateMe(
		-1 * ptrX->GetValue(), //getInput("x"), 
		-1 * ptrY->GetValue()  //getInput("y")
		);

	//apply rotation
	float r = ptrRot->GetValue(); // getInput("rot");
	if (r!=0)
		p->RotateMe(r);

}