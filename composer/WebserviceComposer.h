#ifndef WEBSERVICECOMPOSER_H
#define WEBSERVICECOMPOSER_H

#include "../src/networking/IWebsocket.h"
#include "../src/networking/IWebsocketFactory.h"

#include "../src/nodes/Node.h"
#include "../src/nodes/ProcessNode.h"

#include "../lib/gason/gason.h"
#include "command.h"

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
        void SendAllNodesToClient();
        void SendNodeToClient(Node* node);
    private:
        IWebsocket* ws;

        //template<class T>
        std::string serializeInputSockets(std::map<std::string, InputSocket*>* socks);
        std::string serializeOutputSockets(std::map<std::string, OutputSocket*>* socks);

        void parseCommand(char* cmd, Command* command);
};

#endif