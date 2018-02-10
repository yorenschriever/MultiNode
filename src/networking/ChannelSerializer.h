#ifndef CHANNELSERIALIZER_H
#define CHANNELSERIALIZER_H

#include <string>
//#include "../../lib/TinyXml/TinyXML.h"
#include "../sockets/Socket.h" //TODO i dont want this reference? 
#include "../nodes/ProcessNode.h" //TODO i dont want this reference? 

#define MAXCHANNELNAMELENGTH 50

//TODO is removed TinyXMl references from this file. the serialzer wont work
//Fix this, or even better, rewrite the channelserializer 
// - without static callbacks
// - using the json parser

class ChannelSerializer
{
	public:
		static void init();
		static int createMessage(char* buf, std::string name, SOCKETTYPE value);
		static bool parseMessage(char* buf, int len, ProcessNode* nodeInstance); //we pass the node so i can check if the channel name is relevant early on during the xml processing, but i am not sure if the performance increase weighs up to the ugly interface
		static std::string channelName;
		static SOCKETTYPE value;
		
	protected:
		//static TinyXML xml;
		static bool continueParsing;
		static ProcessNode* node;
		static uint8_t* buffer; // For XML decoding
		static void XML_callback(uint8_t statusflags, char* tagName, uint16_t tagNameLen, char* data, uint16_t dataLen);
		static bool channelExists(std::string channel);	
		static bool isInit;
};

#endif