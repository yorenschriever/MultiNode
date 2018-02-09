#include "MultiNode.h"

SumNode* sum;
SumNode* sum2;

void setup() {
  Serial.begin(115200);
  Serial.println("================");
  Serial.println("started");

  sum = new SumNode();
  sum2 = new SumNode();  
  
  sum->GetInputSocket("A")->SetValue(5);
  sum->GetInputSocket("B")->SetValue(6);

  sum2->GetInputSocket("A")->Connect(sum->GetOutputSocket("C"));
  sum2->GetInputSocket("B")->SetValue(6);
}

void loop() {

  Serial.print("Answer: ");
  Serial.println(sum2->GetOutputSocket("C")->GetValue());

  NodeManager::AutoProcess();

  Serial.println("loop");
  delay(1000);
}
