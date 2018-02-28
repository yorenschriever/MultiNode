#ifndef NODESARDUINO_H
#define NODESARDUINO_H

#include "Arduino.h" //must be on top
#include "MultiNode.h"

class PinInputNode : public Node {
	public: 
		PinInputNode(int pin);
		~PinInputNode();
	protected:
		virtual void ProcessInternal(Socket* caller);
		int pin;
		bool value;
};


class PinOutputNode : public Node {
	public: 
		PinOutputNode(int pin);
		~PinOutputNode();
	protected:
		virtual void ProcessInternal(Socket* caller);
		int pin;
		bool value;
};

class AnalogOutNode : public Node {
	public: 
		AnalogOutNode();
	protected:
		virtual void ProcessInternal(Socket* caller);
		
	InputSocket* ptrOut25;
	InputSocket* ptrOut26;

};

#endif