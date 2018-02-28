#include "Arduino.h" //must be on top
#include <driver/dac.h>
#include "NodesArduino.h"


PinInputNode::PinInputNode(int pin){
    CreateOutputSocket("Value",Push);
    CreateOutputSocket("Rising",Push);
    CreateOutputSocket("Falling",Push);

	this->pin = pin;
	pinMode(pin,INPUT_PULLUP);

	this->Title = "PinInput";

    //add to the list of nodes that are processed automatically
	NodeManager::AutoProcessNode(this);
}

PinInputNode::~PinInputNode(){
}

void PinInputNode::ProcessInternal(Socket* caller)
{
	//TODO debouncing
	bool newValue = !digitalRead(pin);
	if (value != newValue)
	{
		value = newValue;
		setOutput("Value",value);
		
		setOutput("Rising",value);
		setOutput("Falling",!value);
	} else {
		setOutput("Rising",0);
		setOutput("Falling",0);
	}
}

PinOutputNode::PinOutputNode(int pin){
	CreateInputSocket("Value",Push,0);

	this->pin = pin;
	pinMode(pin,OUTPUT);

	this->Title = "PinOutput";
}

PinOutputNode::~PinOutputNode(){
}

void PinOutputNode::ProcessInternal(Socket* caller)
{
	bool newValue = getInput("Value");
	if (value != newValue)
	{
		value = newValue;
		digitalWrite(pin,value > 0);
	}
}


AnalogOutNode::AnalogOutNode(){
	Title="AnalogOut";
	ptrOut25 = CreateInputSocket("Output 25",Pull,0);
	ptrOut26 = CreateInputSocket("Output 26",Pull,1);	
}

void AnalogOutNode::ProcessInternal(Socket* caller)
{

	float valA = ptrOut25->GetValue();
	if (valA<0) valA=0;
	if (valA>255) valA=255;

	float valB = ptrOut26->GetValue();
	if (valB<0) valB=0;
	if (valB>255) valB=255;

    dac_out_voltage(DAC_CHANNEL_1, valA);
    dac_out_voltage(DAC_CHANNEL_2, valB);

}