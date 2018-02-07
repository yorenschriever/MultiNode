
#include "RenderNode.h"
#include "../types.h"

RenderNode::RenderNode()
{
	CreateInputSocket("x",Pull,0);
	CreateInputSocket("y",Pull,0);
	CreateInputSocket("rot",Pull,0);
}

RGBA RenderNode::GetStackedColor(Position p){
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

void RenderNode::applyPositionAndTranslation(Position* p)
{
	//We want to apply rotation first, then translation.
	//But since the rotate the 'camera' instead of the object itself,
	//we have to apply these operations in the opposite direction.

	//apply translation
	p->TranslateMe(
		-1 * getInput("x"), 
		-1 * getInput("y")
		);

	//apply rotation
	float r = getInput("rot");
	if (r!=0)
		p->RotateMe(r);

}