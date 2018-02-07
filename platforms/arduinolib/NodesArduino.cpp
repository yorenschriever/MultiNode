#include "Arduino.h" //must be on top
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