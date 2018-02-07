#include "WebserviceComposer.h"
#include "../src/Debug.h"
#include <functional>

#include "../src/networking/IWebsocket.h"
#include <string.h>
#include "../src/nodes/ProcessNode.h"
#include "../src/NodeManager.h"

using namespace std::placeholders;

void WebserviceComposer::start()
{
    Debug::Info("creating instance");
    ws = IWebsocketFactory::GetInstance(81);

    Debug::Info("setting handler");
    ws->onMessage(std::bind(&WebserviceComposer::handleMsg, this,_1,_2,_3));

    Debug::Info("begin webservice");
    ws->begin();
}

void WebserviceComposer::loop()
{
    ws->loop();
}

void WebserviceComposer::handleMsg(uint8_t num, uint8_t * payload, size_t length)
{
    Debug::Info("got msg: " + std::string((char*)payload,length));
    ws->sendMessage(std::string((char*)payload,length));


    if (!strcmp("GETALL",(const char*) payload))
    {
        NodeManager::ResetIterator();
        Node* pointer=0;
        while(pointer = NodeManager::GetNextNode())
        {
            SendNodeToClient(pointer);
            //Debug::Info(std::string("Title: ") + pointer->Title);
            //ws->sendMessage(std::string(pointer->Title));
        }
        ws->sendMessage("{\"initconn\": true}");
    }

}

void WebserviceComposer::SendNodeToClient(Node* node)
{
    Debug::Info(std::string("Sending node: ") + node->Title);
    

    std::string result = "";
    result += "{\"node\":{";
    result += "\"id\":" + std::to_string(node->id) + ",";
    result += "\"title\":\"" + node->Title + "\",";

    result += "\"inputs\":[" + serializeInputSockets(node->GetInputSockets()) + "]";

    std::map<std::string, OutputSocket*>* outsocks = node->GetOutputSockets();
    if (outsocks!=0)
        result += ",\"outputs\":[" + serializeOutputSockets(outsocks) + "]";

    //try to cast it to a procesnode
    /*ProcessNode* processnode =  dynamic_cast<ProcessNode*> (node);

    if (processnode != 0)
    {
        //if succesful, also print the outputs of the processnode
        Debug::Info("Cast to processnode succesful");
        result += "outputs: [" + serializeOutputSockets(processnode->GetOutputSockets()) + "],";
    }*/

    result += "}}";
    ws->sendMessage(result);
}


std::string WebserviceComposer::serializeInputSockets(std::map<std::string, InputSocket*>* socks)
{
    std::string results="";
    for (std::map<std::string, InputSocket*>::iterator it=socks->begin(); it!=socks->end(); ++it)
    {
        results += std::string((it!=socks->begin())?",":" ") + "{\"name\":\"" + it->first + "\"";

        Socket* conn = it->second->GetConnectedSocket();
        if (conn !=0)
            results += ",\"connected\": {\"id\": " + std::to_string(conn->GetNode()->id) + ",\"sock\": \"" + conn->Name + "\"}";

        results += "}";
    }
    return results;
}

std::string WebserviceComposer::serializeOutputSockets(std::map<std::string, OutputSocket*>* socks)
{
    std::string results="";
    for (std::map<std::string, OutputSocket*>::iterator it=socks->begin(); it!=socks->end(); ++it)
    {
        results += std::string((it!=socks->begin())?",":" ") + "\"" + it->first + "\"";
    }
        //std::cout << it->first << " => " << it->second << '\n';
    return results;
}