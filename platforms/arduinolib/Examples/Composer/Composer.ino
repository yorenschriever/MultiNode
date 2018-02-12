
#define WITHCOMPOSER
#include "MultiNode.h"
#include "esp32_digital_led_lib.h"

#include <WiFi.h>

WebserviceComposer* composer; 


RectangleNode rect;
RectangleNode rect2;
CircleNode circ;

LFONode recty;
TimeNode rectrot;

LFONode rect2x;
LFONode rect2y;
TimeNode rect2rot;

LFONode circx;
LFONode circy;
LFONode circrad;


//pointer to the top node, so we can easily switch the render order
GraphicsNode* topNode = &rect2;

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

  rect.GetInputSocket("x")->SetValue(2.5);
  rect.GetInputSocket("width")->SetValue(3.5);
  rect.GetInputSocket("height")->SetValue(3.5);
  rect.Color = RGBA {175, 0, 0, 0.5};  
  setupLFO(&recty, 2.5,10,10, rect.GetInputSocket("y"));
  setupTime(&rectrot, 3.141592648, 200, rect.GetInputSocket("rot"));

  rect2.GetInputSocket("width")->SetValue(2);
  rect2.GetInputSocket("height")->SetValue(2);
  rect2.Color = RGBA {0, 0, 255, 0.5};  
  setupLFO(&rect2x, 0.5,  -10,  15,  rect2.GetInputSocket("y"));
  setupLFO(&rect2y, 0.7, -3.5, 3.5, rect2.GetInputSocket("x"));
  setupTime(&rect2rot, 3.141592648, -500, rect2.GetInputSocket("rot"));

  circ.GetInputSocket("x")->SetValue(4);
  circ.GetInputSocket("y")->SetValue(16);
  circ.GetInputSocket("radius")->SetValue(20);
  circ.Color = RGBA {0, 255, 0, 0.5};
  setupLFO(&circx,   5, 20 ,  15,  circ.GetInputSocket("y"));
  setupLFO(&circy,   3, 5,    3.5,  circ.GetInputSocket("x"));
  setupLFO(&circrad, 5, 5, 5,  circ.GetInputSocket("radius"));


  rect.UnderlyingNode = &circ;
  rect2.UnderlyingNode = &rect; 

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
