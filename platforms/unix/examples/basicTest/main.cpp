#include "MultiNode.h"

int main(){

	SumNode X = SumNode();
	SumNode Y = SumNode();

	X.GetInputSocket("A")->SetValue(1);

	X.GetInputSocket("B")->Connect(Y.GetOutputSocket("C"));

	Y.GetInputSocket("A")->SetValue(2);
	Y.GetInputSocket("B")->SetValue(100);

	Debug::Info("Antwoord: " + std::to_string(X.GetOutputSocket("C")->GetValue()));

	return 0;	
}