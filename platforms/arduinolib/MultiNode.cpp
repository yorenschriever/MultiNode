//i still have to find out how to let arduino compile subdirs.
//for now i use this workaround

#include "MultiNode.h"


#include "../../src/nodes/Node.cpp"
#include "../../src/nodes/ProcessNode.cpp"
#include "../../src/nodes/ProcessNodes.cpp"
#include "../../src/nodes/AbstractProxyNode.cpp"
#include "../../src/nodes/ProxyNode.cpp"
#include "../../src/nodes/RenderNode.cpp"
#include "../../src/nodes/ShapeNode.cpp"
#include "../../src/nodes/ShapeNodes.cpp"
#include "../../src/nodes/WebsocketProxyNode.cpp"

#include "../../src/sockets/InputSocket.cpp"
#include "../../src/sockets/OutputSocket.cpp"
#include "../../src/sockets/Socket.cpp"

#include "../../src/NodeManager.cpp"
#include "../../src/Value.cpp"

#include "../../lib/gason/gason.cpp"

#include "implementations/Time.cpp"
#include "implementations/Debug.cpp"
#include "implementations/IWebsocketFactory.cpp"
#include "implementations/WebsocketESP.cpp"
#include "implementations/IUDPSocketFactory.cpp"
#include "implementations/UDPSocketESP.cpp"

#include "lib/arduinoWebSockets/src/WebSocketsServer.cpp"
#include "lib/arduinoWebSockets/src/WebSockets.cpp"

//#ifdef WITHCOMPOSER
    #include "../../composer/WebserviceComposer.cpp"
    #include "../../composer/Composer.cpp"
//#endif
