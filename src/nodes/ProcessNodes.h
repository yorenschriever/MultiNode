#ifndef PROCESSNODES_H
#define PROCESSNODES_H

#include "ProcessNode.h"

class SumNode : public ProcessNode
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

class ToggleNode : public ProcessNode
{
	public: 
		ToggleNode();
		~ToggleNode();
	protected:
		virtual void ProcessInternal(Socket* caller);
		SOCKETTYPE lastValue=0;
		SOCKETTYPE currentValue=0;
};


class LFONode : public ProcessNode
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


class TimeNode : public ProcessNode
{
	public: 
		TimeNode();
		~TimeNode();
	protected:
		virtual void ProcessInternal(Socket* caller);
};

#endif