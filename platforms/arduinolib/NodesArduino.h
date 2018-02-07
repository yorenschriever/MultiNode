#ifndef NODESARDUINO_H
#define NODESARDUINO_H

#include "Arduino.h" //must be on top
#include "MultiNode.h"

class PinInputNode : public ProcessNode {
	public: 
		PinInputNode(int pin);
		~PinInputNode();
	protected:
		virtual void ProcessInternal(Socket* caller);
		int pin;
		bool value;
};


class PinOutputNode : public ProcessNode {
	public: 
		PinOutputNode(int pin);
		~PinOutputNode();
	protected:
		virtual void ProcessInternal(Socket* caller);
		int pin;
		bool value;
};

#endif