#include "WebsocketProxyNode.h"
#include "../networking/IWebsocketFactory.h"

using namespace std::placeholders;

WebsocketProxyNode::WebsocketProxyNode() : AbstractProxyNode()
{ 
    Title = "WebsocketProxyNode";

    comm = IWebsocketFactory::GetInstance(WEBSOCKETPROXYPORT);
    comm->onMessage(std::bind(&WebsocketProxyNode::handleMsg, this,_1,_2,_3));
    comm->begin();
}
