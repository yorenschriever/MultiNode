#include "ProxyNode.h"
#include "../networking/IUDPSocketFactory.h"

using namespace std::placeholders;

ProxyNode::ProxyNode() : AbstractProxyNode()
{
    Title = "ProxyNode";

    comm = IUDPSocketFactory::GetInstance(PROXYPORT);
    comm->onMessage(std::bind(&ProxyNode::handleMsg, this,_1,_2,_3));
    comm->begin();
}