#include "Arduino.h"

#include "patches.h"

#include "../../src/nodes/ProcessNodes.h"
#include "../../src/nodes/ShapeNodes.h"

#include "../../src/nodes/ProxyNode.h"
#include "../../src/nodes/WebsocketProxyNode.h"

#include "../../src/NodeManager.h"

#include "NodesArduino.h"

#include "implementations/WebsocketESP.h"
#include "implementations/UDPSocketESP.h"

//#ifdef WITHCOMPOSER
    #include "../../composer/WebserviceComposer.h"
//#endif