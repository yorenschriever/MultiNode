#ifndef ABSTRACTPROXYNODE_H
#define ABSTRACTPROXYNODE_H

#include "Node.h"
#include "../networking/UDPWrapper.h"
#include "../networking/UDPWrapperFactory.h"
#include "../sockets/Socket.h"
#include "../sockets/InputSocket.h"

#include "../networking/IUDPSocketFactory.h"

/*

Proxynode is an object that will make it possible to join nodes over the network.

Communication between nodes over the network is possible for push sockets only.
To link and output socket of nodeA on machineA to an input socket of nodeB on machineB 
over the network, you have to create a channel. 
currently the channel itself does not need to be registered somewhere.
To use a channel, create a transmitter on the proxynode of machineA, and a receiver with 
the same name on the proxynode of machineB. This will automatically generate an output
socket on proxynode A, and an input on proxynode B. Now the channel between the
nodes is set up. You can connect the output socket of node a to the input socket of
proxya, and the output socket of proxyb to the input of nodeB

Example:
=== machine A ===
PinInputNode NodeA = PinInputNode(34);
ProxyNode ProxyA = ProxyNode(); //create only one instance per machine
ProxyA.CreateTransmitter("myChannel");
ProxyA.InputSockets["myChannel"].Connect(&(NodeA.OutputSockets["Value"]));

=== machine B ===
PinOutputNode NodeB = PinOutputNode(33);
ProxyNode ProxyB = ProxyNode(); //create only one instance per machine
ProxyB.CreateReceiver("myChannel");
ProxyB.OutputSockets["myChannel"].Connect(&(NodeB.InputSockets["Value"]));

If the proxynode receive an update from a socket, it will broadcast a UDP packet to the broadcast
address with the name of the channel and the new value. All remote nodes will be listening 
and parsing these packets.

I have been thinking about a good solution to do this, and chose for this implementation,
because:

- I want to separate networking functionality from the core nodes. i am not sure if networking
  will be used in many future projects, so i don't want to clutter the Socket object with
  networking functionality

- Putting all inter-machine cumminication in a single class makes it simple to change 
  implementation later (see: Drawbacks)

- Using global channels make it easy to monitor and debug

- Using global channels makes it easy to swap hardware. No need to give machines a
  unique id, or use their mac- or ip addresses. All you need to know to cummonicate is the 
  channel name

- implementation in a gui will be relatively easy: if both nodes are present on the canvas,
  the used can drag a line between their sockets to create the connection. in the backed we can
  create a channel with a random chosen name on both machines, and connect the sockets accordingly
  If a remote node disappears, the dangling connections can be visualized, and will not cause
  severe exceptions.  
  The existance of a proxynode can be hidden in the gui, creating a transparent socket to socket 
  link for the end user.


Drawbacks:
This implementation will suffice for the first project i am going to build with it, but in the 
future the implementation might be changed to accomodate sulutions for these issues:

- Every machine on the subnet is listening to all packets, and has to parse them all. This is 
  sub optimal use of bandwidth and cpu cycles on all nodes. 

- Choosing a channel does not check if the channel name is unique. For larger projects care must
  be taken not to use the same channel name twice.

- multiple endpoints can transmit and receive on the same channel. Altough for reception this might
  be considered a feature, for transmission the behaviour is unspecified, and can cause unwanted
  effects.


notes:
- be sure to create only one proxynode per machine to avoid lost messages.


*/

class AbstractProxyNode : public Node
{
	public: 
		AbstractProxyNode();
		~AbstractProxyNode();

		void CreateTransmitter(std::string Name);
		void CreateReceiver(std::string Name);

    //some shortcut function that will help you create and link a socket quickly
    void CreateAndConnectTransmitter(OutputSocket* sock); //create transmitter with same name as socket and connect them
    void CreateAndConnectReceiver(InputSocket* sock);     //create receiver with the same name as socket and connect them
    void CreateAndConnectTransmitter(std::string Name,OutputSocket* sock);
    void CreateAndConnectReceiver(std::string Name,InputSocket* sock);

		void DeleteTransmitter(std::string Name);
		void DeleteReceiver(std::string Name);
	protected:
    ICommunication* comm;

    void handleMsg(uint8_t num, uint8_t * payload, size_t length);

		virtual void ProcessInternal(Socket* caller);
		void sendValue(Socket* socket);
		void receiveValues();

    int createMessage(char* buf, std::string socketname, SOCKETTYPE value);
    bool channelExists(std::string channel);

};

#endif