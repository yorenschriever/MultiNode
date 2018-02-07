#include "ProcessNodes.h"
#include "../Time.h"
#include "../Debug.h"
#include <math.h>

SumNode::SumNode(){
	Title="Sum";
	CreateInputSocket("A",Pull,0);
	CreateInputSocket("B",Pull,0);
	CreateOutputSocket("C",Pull);
}

SumNode::~SumNode(){
}

void SumNode::ProcessInternal(Socket* caller)
{
	setOutput("C",getInput("A")+getInput("B"));
}



ToggleNode::ToggleNode(){
	Title="Toggle";
	CreateInputSocket("In",Push,0);
	CreateOutputSocket("Out",Push);
	Title = "ToggleNode";
}

ToggleNode::~ToggleNode(){
}

void ToggleNode::ProcessInternal(Socket* caller)
{
	SOCKETTYPE val = getInput("In");
	if (val==0 && lastValue!=0)
	{
		currentValue = (currentValue==0)?1:0;
		setOutput("Out",currentValue);
    }
    lastValue = val;
}




LFONode::LFONode(){
	Title="LFO";
	CreateInputSocket("Period",Pull,1);
	CreateInputSocket("Amplitude",Pull,0);
	CreateInputSocket("Offset",Pull,0);
	CreateOutputSocket("Value",Pull);
}

LFONode::~LFONode(){
}

void LFONode::ProcessInternal(Socket* caller)
{
	SOCKETTYPE period = getInput("Period");
	if (period==0)
		return;

	setOutput("Value",getInput("Offset")+getInput("Amplitude") * sin((float)Time::Millis() /1000.0 * 2*3.141592658 / period));
}



TimeNode::TimeNode(){
	Title="Time";
	CreateInputSocket("Period",Pull,0);
	CreateInputSocket("Prescale",Pull,1000);
	CreateOutputSocket("Value",Pull);
}

TimeNode::~TimeNode(){
}

void TimeNode::ProcessInternal(Socket* caller)
{
	SOCKETTYPE prescale = getInput("Prescale");
	if (prescale==0)
		return;

	SOCKETTYPE period = getInput("Period");
	if (period > 0)
		setOutput("Value", fmod((SOCKETTYPE) Time::Millis() / getInput("Prescale") , getInput("Period")));
	else
		setOutput("Value", ((SOCKETTYPE) Time::Millis() / getInput("Prescale")) );
}