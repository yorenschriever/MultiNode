#ifndef RENDERNODE_H
#define RENDERNODE_H

#include "Node.h"

/*
 render nodes are a special class of nodes, which do not process values to an output,
 but are able to generate pixel data  
 */

class RenderNode : public Node
{
	public:
		RenderNode();
		RenderNode* UnderlyingNode=0; 	
		virtual RGBA GetStackedColor(Position p);
	protected:
		//i do it this way, so i can support bitmaps and non-linear blending with layers below (like blurry glass)
		virtual RGBA colorAt(Position p)=0; 

		//since all rendernodes will probably support rotation and translation (position), it is implemented here.
		//can be used in intersect()
		void applyPositionAndTranslation(Position* p);

		void ProcessInternal(Socket* caller) {}; //rendernode do not process 
};

#endif