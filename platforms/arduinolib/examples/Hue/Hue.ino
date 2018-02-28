
#define WITHCOMPOSER
#include "MultiNode.h"
#include "esp32_digital_led_lib.h"

#include <WiFi.h>

WebserviceComposer* composer; 





//pointer to the top node, so we can easily switch the render order
GraphicsNode* topNode;

void setupLFO(LFONode* lfo, float period, float amplitude, float offset, InputSocket* socket)
{
  lfo->GetInputSocket("Period")->SetValue(period);
  lfo->GetInputSocket("Amplitude")->SetValue(amplitude);
  lfo->GetInputSocket("Offset")->SetValue(offset);
  lfo->GetOutputSocket("Value")->Connect(socket);  
}

void setupTime(TimeNode* t, float period, float prescale, InputSocket* socket)
{
  t->GetInputSocket("Period")->SetValue(period);
  t->GetInputSocket("Prescale")->SetValue(prescale);
  t->GetOutputSocket("Value")->Connect(socket);  
}

void setup() {
  Serial.begin(115200);

  WiFi.begin("Multischriever", "internet");

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  LedOutputSetup();

  Node* lastNode=0;
  for (int y=0;y<8; y++)
  {
    for(int x=0;x<2; x++)
    {
      RectangleNode* rect = new RectangeNode();
      rect->GetInputSocket("x")->SetValue(x*4+2);
      rect->GetInputSocket("y")->SetValue(y*4+2);
      rect.Color = RGBA {y * 32 , x*127, 0, 1}; 
      rect.UnderlyingNode = lastNode;

      lastNode=rect;
    }
  }

  topNode = lastNode;

  Serial.println("Shapes defined");

  composer = new WebserviceComposer();
  composer->start();

  Serial.println(ESP.getFreeHeap());
}

void loop() {

  NodeManager::AutoProcess();
  UpdateLeds();
  
  //Serial.println("frame");

  composer->loop();
}


//return the position of a led given its index
Position getLedPos(int i){
  Position p;

  p.y = 2*(i/16);
  p.x = i%16;

  if (p.x >= 8)
  {
    p.y+=1;
    p.x = 15-p.x;
  }

  return p;
}
