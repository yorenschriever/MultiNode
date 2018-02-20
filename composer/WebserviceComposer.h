#ifndef WEBSERVICECOMPOSER_H
#define WEBSERVICECOMPOSER_H

#include "../src/networking/IWebsocket.h"
#include "../src/networking/IWebsocketFactory.h"

#include "../src/nodes/Node.h"
//#include "../src/nodes/ProcessNode.h"

#include "../lib/gason/gason.h"
#include "Command.h"

/**
 * The workhorse of the ui.
 * Will setup a websocket server, parse the incoming messages, and call the corresponding methods in Composer.
 * Will also send any changes to all connected clients, so they are all up to date. 
 */ 

class WebserviceComposer{
    public: 
        WebserviceComposer(){}
        ~WebserviceComposer(){}

        void start();
        void handleMsg(uint8_t num, uint8_t * payload, size_t length);
        void loop();

        void Move(int id, int x, int y);
        void SetTitle(int id, std::string title);
        void SetValue(int id, std::string inputsocket, SOCKETTYPE val);
        void Disconnect(int id, std::string inputsocket);
        void Connect(int idinp, std::string inputsocket, int idout, std::string outputsocket);

        void CreateNode(std::string name);
        void DeleteNode(int id);

        void SendAllNodesToClient();
        void SendNodeToClient(Node* node);
        void SendDeleteNodeToClient(int id);
    private:
        IWebsocket* ws;

        //template<class T>
        std::string serializeInputSockets(std::map<std::string, InputSocket*>* socks);
        std::string serializeOutputSockets(std::map<std::string, OutputSocket*>* socks);

        void parseCommand(char* cmd, Command* command);
};

#endif