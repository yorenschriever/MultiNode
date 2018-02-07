
#include "Socket.h"
#include "Nodes.h"
//#include "NodeManager.h"

#include <iostream>

int main(){

	SumNode X = SumNode();
	SumNode Y = SumNode();

	X.GetInputSocket("A")->SetValue(1);

	X.GetInputSocket("B")->Connect(Y.GetOutputSocket("C"));

	Y.GetInputSocket("A")->SetValue(2);
	Y.GetInputSocket("B")->SetValue(100);

	std::cout << "Antwoord: "  << X.GetOutputSocket("C")->GetValue() << "\n";

	//NodeManager::AutoProcess();

	return 0;
	
}