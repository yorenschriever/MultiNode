#ifndef PROCESSNODES_H
#define PROCESSNODES_H

#include "Node.h"
#include "../sockets/InputSocket.h"
#include "../sockets/OutputSocket.h"

class SumNode : public Node
{
	public: 
		SumNode();
		~SumNode();
	protected:
		virtual void ProcessInternal(Socket* caller);
		InputSocket* ptrA;
		InputSocket* ptrB;
		OutputSocket* ptrC;
};

class ToggleNode : public Node
{
	public: 
		ToggleNode();
		~ToggleNode();
	protected:
		virtual void ProcessInternal(Socket* caller);
		SOCKETTYPE lastValue=0;
		SOCKETTYPE currentValue=0;
};


class LFONode : public Node
{
	public: 
		LFONode();
		~LFONode();
	protected:
		virtual void ProcessInternal(Socket* caller);

		InputSocket* ptrPeriod;
		InputSocket* ptrAmplitude;
		InputSocket* ptrOffset;
		OutputSocket* ptrValue;

};


class TimeNode : public Node
{
	public: 
		TimeNode();
		~TimeNode();
	protected:
		virtual void ProcessInternal(Socket* caller);
};

#endif