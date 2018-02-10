
#include "ChannelSerializer.h"
#include "../Debug.h"
#include "../sockets/Socket.h"

#define XMLBUFFERSIZE 150

//initialize static fields:
bool ChannelSerializer::continueParsing = true;
ProcessNode* ChannelSerializer::node = 0;
uint8_t* ChannelSerializer::buffer = (uint8_t*) malloc(XMLBUFFERSIZE);
//TinyXML ChannelSerializer::xml = TinyXML();
std::string ChannelSerializer::channelName = std::string();
SOCKETTYPE ChannelSerializer::value=0;
bool ChannelSerializer::isInit = false;


void ChannelSerializer::init()
{
  if (isInit) //initialize only once
    return;
  isInit = true;
	
  //xml.init((uint8_t *)buffer, XMLBUFFERSIZE, &ChannelSerializer::XML_callback);
}

int ChannelSerializer::createMessage(char* buf, std::string name, SOCKETTYPE value)
{
	  return sprintf(buf, "<msg ch=\"%s\">" SOCKETTYPETOSTR "</msg>", name.c_str(), value);
}		

bool ChannelSerializer::parseMessage(char* buf, int msglen, ProcessNode* nodeInstance){
  /*ChannelSerializer::node = nodeInstance;
  //Debug::Info("Channelserializer is Setting node to: " + node->Title);

  xml.reset();

  continueParsing = true;
  
  for(int i=0;i<msglen && continueParsing;i++){
    xml.processChar(buf[i]);
  }
  */
  return continueParsing;
}

int min(int a, int b){
  return a<b?a:b;
}

bool ChannelSerializer::channelExists(std::string channel)
{
  //Debug::Info(String("Checking channel: ") + channel.c_str());
  //Debug::Info(String("Looking in node: ") + String(node->Title.c_str()));

  return node->GetOutputSocket(channel)!=0;
}

void ChannelSerializer::XML_callback(uint8_t statusflags, char* tagName, uint16_t tagNameLen, char* data, uint16_t dataLen)
{
  /*
  if (statusflags & STATUS_ERROR){
    continueParsing = false;
    Debug::Error("Error in xml parsing");
    return;
  }

  if (statusflags & STATUS_START_TAG && strcasecmp(tagName, "/msg"))
  {
    continueParsing = false;
    Debug::Error("Incorrect tag");
    return;
  }

  if (statusflags & STATUS_ATTR_TEXT && !strcasecmp(tagName, "ch"))
  {
    if (!channelExists(std::string(data, dataLen))){
      Debug::Error("Channel does not exist");
      continueParsing = false;
      return;
    } else {
      channelName = std::string(data, dataLen);
    }
  }

  if (statusflags & STATUS_TAG_TEXT){
      value = SOCKETTYPEPARSE(data);  
  }
  */
}