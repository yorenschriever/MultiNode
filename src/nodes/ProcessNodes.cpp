
#include "ProcessNodes.h"
#include "../Time.h"
#include "../Debug.h"
#include <math.h>

#include "../sockets/InputSocket.h"
#include "../sockets/OutputSocket.h"

SumNode::SumNode(){
	Title="Sum";
	ptrA = CreateInputSocket("A",Pull,0); 
	ptrB = CreateInputSocket("B",Pull,0);
	ptrC = CreateOutputSocket("C",Pull); 
}

//SumNode::~SumNode(){}

void SumNode::ProcessInternal(Socket* caller)
{
	//This method works for a variable number of sockets
	//setOutput("C",getInput("A")+getInput("B"));

	//but when the number of sockets is fixed, performance 
	//can be increased 5-fold by using pointers
	ptrC->SetValue(ptrA->GetValue() + ptrB->GetValue());
}



ToggleNode::ToggleNode(){
	Title="Toggle";
	CreateInputSocket("In",Push,0);
	CreateOutputSocket("Out",Push);
	Title = "ToggleNode";
}

//ToggleNode::~ToggleNode(){}

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
	ptrPeriod = CreateInputSocket("Period",Pull,1);
	ptrAmplitude = CreateInputSocket("Amplitude",Pull,0);
	ptrOffset = CreateInputSocket("Offset",Pull,0);
	ptrValue = CreateOutputSocket("Value",Pull);
}

//LFONode::~LFONode(){}

void LFONode::ProcessInternal(Socket* caller)
{
	SOCKETTYPE period = ptrPeriod->GetValue(); //getInput("Period");
	if (period==0)
		return;

	//why is this faster than the pointer impl?
	setOutput("Value",getInput("Offset")+getInput("Amplitude") * sin((float)Time::Millis() /1000.0 * 2*3.141592658 / period));
	/*ptrValue->SetValue(
		ptrOffset->GetValue() + ptrAmplitude->GetValue() * sin((float)Time::Millis() /1000.0 * 2*3.141592658 / period)
	);*/
}



TimeNode::TimeNode(){
	Title="Time";
	CreateInputSocket("Period",Pull,0);
	CreateInputSocket("Prescale",Pull,1000);
	CreateOutputSocket("Value",Pull);
}

//TimeNode::~TimeNode(){}

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


SinNode::SinNode(){
	Title="Sin";
	ptrTime = CreateInputSocket("Time",Pull,0);
	ptrPeriod = CreateInputSocket("Period",Pull,1);
	ptrAmplitude = CreateInputSocket("Amplitude",Pull,1);
	ptrOffset = CreateInputSocket("Offset",Pull,0);
	ptrPhase = CreateInputSocket("Phase",Pull,0);

	ptrValue = CreateOutputSocket("Value",Pull);
}

void SinNode::ProcessInternal(Socket* caller)
{
	SOCKETTYPE period = ptrPeriod->GetValue(); 
	if (period==0)
		return;

	setOutput("Value",getInput("Offset")+getInput("Amplitude") * sin(getInput("Time") * 2*3.141592658 / period + getInput("Phase")*3.14159265/180.0));
}