#ifndef WEBSOCKETPROXYNODE_H
#define WEBSOCKETPROXYNODE_H

#include "AbstractProxyNode.h"

#define WEBSOCKETPROXYPORT 9603

class WebsocketProxyNode : public AbstractProxyNode
{
    public:
        WebsocketProxyNode(); 
        ~WebsocketProxyNode(){};
};

#endif
