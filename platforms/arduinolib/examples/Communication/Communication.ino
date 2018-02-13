/*

This example will need 2 esp32s.
When the button on a esp is pressed, the led on the other will light up, and vice versa.

This works due to the ProxyNode.
The proxynode can be used to transit or receive on global channels. All nodes can use all channels. 

If a value is transmitted over a channel, all other proxy nodes connected to the same network
will be able to receive the value.



*/

#include "MultiNode.h"
#include <WiFi.h>

//create an input  on pin 34
PinInputNode input(34);

//create an output  on pin 33
PinOutputNode output(33);

//create a proxynode that can forward values over a channel
ProxyNode* proxy;

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

  proxy = new ProxyNode();  //proxynode must be constructed after wifi/eth connection is established

  //if the channelname argument is omitted, the receiver will listen on the channel with 
  //the same name as the socket. in this case "Value"
  proxy->CreateAndConnectReceiver(output.GetInputSocket("Value"));

  //if the channelname argument is omitted, the trasnmitter will listen on the channel with 
  //the same name as the socket. in this case "Value"
  proxy->CreateAndConnectTransmitter(input.GetOutputSocket("Value"));
}

void loop() {
  NodeManager::AutoProcess();
}
