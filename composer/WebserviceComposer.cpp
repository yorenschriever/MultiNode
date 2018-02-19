#define WITHCOMPOSER

#include "WebserviceComposer.h"
#include "../src/Debug.h"
#include <functional>

#include "../src/networking/IWebsocket.h"
#include <string.h>
#include "../src/nodes/Node.h"
#include "../src/NodeManager.h"
#include "../src/sockets/InputSocket.h"

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

    Command comm;
    parseCommand((char*) payload, &comm);

    if (!strcmp("GetAll",comm.name))
        SendAllNodesToClient();

    if (!strcmp("Move",comm.name))
        Move(
            comm.params["id"].AsIndex(), 
            comm.params["x"].AsIndex(),
            comm.params["y"].AsIndex());
    
    if (!strcmp("Title",comm.name))
        SetTitle(
            comm.params["id"].AsIndex(), 
            comm.params["title"].AsString());

    if (!strcmp("Value",comm.name))
        SetValue(
            comm.params["id"].AsIndex(), 
            comm.params["sock"].AsString(),
            comm.params["val"].AsNumber());

    if (!strcmp("Connect",comm.name))
        Connect(
            comm.params["idin"].AsIndex(), 
            comm.params["sockin"].AsString(),
            comm.params["idout"].AsIndex(), 
            comm.params["sockout"].AsString());

    if (!strcmp("Disconnect",comm.name))
        Disconnect(
            comm.params["id"].AsIndex(), 
            comm.params["sock"].AsString());



}

void WebserviceComposer::parseCommand(char* cmd, Command* command)
{
  char *endptr;
  JsonValue value;
  JsonAllocator allocator;

  int status = jsonParse(cmd, &endptr, &value, allocator);
  if (status != JSON_OK) {
    Debug::Error(std::string("Unable to parse JSON: ") + jsonStrError(status)) ;
    return;
  }    

  command->name="";
  command->params = std::map<std::string,Value>();
  
  if (value.getTag() != JSON_OBJECT){
    Debug::Error("Command is wrong type");
    return;
  }

    for (auto i : value) {
        if (!strcmp("cmd",i->key))
        {
        command->name = i->value.toString();
        continue;
        }

        if (!strcmp("params",i->key))
        {

            for (auto j : i->value) 
            {
                JsonTag tag = j->value.getTag();

                Value v; // = Value(0);
                if (tag == JSON_NUMBER)
                    v.SetValue((float)j->value.toNumber());

                if (tag == JSON_STRING)
                    v.SetValue( j->value.toString() ) ;

                if (tag == JSON_TRUE)
                    v.SetValue( true ) ;

                if (tag == JSON_FALSE)
                    v.SetValue( false ) ;

                command->params.insert( std::make_pair( std::string(j->key), v  ) );
            }
            continue;
        }
    
    }
}

void WebserviceComposer::Move(int id, int x, int y)
{
    Node* node = NodeManager::GetNode(id);
    if (node==0)
        return;

    node->x = x;
    node->y = y;

    SendNodeToClient(node);
}

void WebserviceComposer::SetTitle(int id, std::string title)
{
    Node* node = NodeManager::GetNode(id);
    if (node==0)
        return;

    node->Title = title;

    SendNodeToClient(node);
}

void WebserviceComposer::SetValue(int id, std::string inputsocket, SOCKETTYPE val)
{
    Node* node = NodeManager::GetNode(id);
    if (node==0)
        return;

    InputSocket* sock = node->GetInputSocket(inputsocket);
    if (sock==0)
        return;

    sock->SetValue(val);

    SendNodeToClient(node);
}

void WebserviceComposer::Disconnect(int id, std::string inputsocket)
{
    Node* node = NodeManager::GetNode(id);
    if (node==0)
        return;

    InputSocket* sock = node->GetInputSocket(inputsocket);
    if (sock==0)
        return;

    Socket* othersocket = sock->GetConnectedSocket();
    if (othersocket==0)
        return;

    Node* otherNode = othersocket->GetNode();

    sock->Disconnect();

    SendNodeToClient(node);
    SendNodeToClient(otherNode);
}


void WebserviceComposer::Connect(int idinp, std::string inputsocket, int idout, std::string outputsocket)
{
    Node* nodeinp = NodeManager::GetNode(idinp);
    if (nodeinp==0)
        return;

    InputSocket* sockinp = nodeinp->GetInputSocket(inputsocket);
    if (sockinp==0)
        return;

    Node* nodeout = NodeManager::GetNode(idout);
    if (nodeout==0)
        return;

    OutputSocket* sockout = nodeout->GetOutputSocket(outputsocket);
    if (sockout==0)
        return;

    sockinp->Connect((Socket*)sockout);

    SendNodeToClient(nodeinp);
}

void WebserviceComposer::SendAllNodesToClient()
{
    NodeManager::ResetIterator();
    Node* pointer=0;
    while(pointer = NodeManager::GetNextNode())
    {
        SendNodeToClient(pointer);
    }
    ws->sendMessage("{\"initconn\": true}");    
}

void WebserviceComposer::SendNodeToClient(Node* node)
{
    Debug::Info(std::string("Sending node: ") + node->Title);
    

    std::string result = "";
    result += "{\"node\":{";
    result += "\"id\":" + std::to_string(node->id) + ",";
    result += "\"x\":" + std::to_string(node->x) + ",";
    result += "\"y\":" + std::to_string(node->y) + ",";
    result += "\"title\":\"" + node->Title + "\",";

    result += "\"inputs\":[" + serializeInputSockets(node->GetInputSockets()) + "]";

    std::map<std::string, OutputSocket*>* outsocks = node->GetOutputSockets();
    if (outsocks!=0)
        result += ",\"outputs\":[" + serializeOutputSockets(outsocks) + "]";

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
        else
            results += ",\"value\": " + std::to_string(it->second->GetValue()) + "";

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