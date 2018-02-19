

var exampleSocket = new WebSocket("ws://192.168.1.184:81", "MultiNode");

exampleSocket.onopen = function (event) {
    exampleSocket.send('{"cmd": "GetAll"}'); 
};


var nodes = {};

exampleSocket.onmessage = function(event) {
    var parsed = JSON.parse( event.data);

    console.log("incoming message", parsed);

    if (parsed.node)
        addNode(parsed.node)

    if (parsed.initconn)
    {

        removeAllNodeConnections();
        drawNodeConnections();
    }

        
    //todo, this will bind a lot of events multiple times,
    //for example socket ondblclick.
    //change this to only add events to the changed/newly generated node
    window.onload();
};

function addNode(node)
{
    if (nodes[node.id] == undefined)
    {
        nodes[node.id] = {
            node: node, 
            element: createNodeElement(node.id)
        }
        
    } else {
        nodes[node.id].node = node;
    }
    
    drawNode(nodes[node.id].node, nodes[node.id].element); 
    $(nodes[node.id].element).css({top: node.y, left: node.x});

    removeAllNodeConnections();
    drawNodeConnections();

    
}

/*function removeConnectionsFromNode(el)
{

}*/

function removeAllNodeConnections()
{
    window.removeAllConnectors();
}

function drawInputConnectionsForNode(node)
{
    if (node.inputs)
    {
        node.inputs.forEach(function(inp){
            if (inp.connected)
            {
                drawConnection(node.id, inp.name, inp.connected.id, inp.connected.sock);
            }
        });
    }
}

function drawNodeConnections()
{
    Object.values(nodes).forEach(function(node2){
        drawInputConnectionsForNode(node2.node);
    });
}

function drawConnection(ida, socka, idb, sockb)
{

    var enda = $("#sock_" + ida + "_" + socka)[0];
    var endb = $("#sock_" + idb + "_" + sockb)[0];

    if (enda && endb)
    window.createConnector(
        $("#sock_" + ida + "_" + socka).children('.con_anchor'), 
        $("#sock_" + idb + "_" + sockb).children(".con_anchor") )
}

function createNodeElement(id)
{
    var nodeel = document.createElement("div"); 

    nodeel.setAttribute('bid', id);
    nodeel.setAttribute('class',"node ui-item item-1")

    document.getElementById("canvas").appendChild(nodeel); 
    return nodeel;
}

function drawNode(node, element)
{
    //html =  '<div class="node ui-item item-1" bid=' + node.id + '>';
    html="";
    html += '<div class="node_title">' + node.title + '</div>'
    html += '<div class="sockets_in">';
    if (node.inputs!=undefined)
    {
        node.inputs.forEach(function(sock) { 
            console.log("creating socket", sock.name, sock.value)
            html += '<div class="socket_in" id="sock_' + node.id + '_' + sock.name +'">';
            html += '  <div class="con_anchor" val="'+sock.value+'" ></div>';
            html += '  <div class="socket_title">' + sock.name + '</div>';
            html += '</div>';

            UpdateInputValue(node.id, sock.name, sock.value);
        })
        
    }
    html += '</div>';

    html += '<div class="sockets_out">';
    if (node.outputs!=undefined)
    {   
        node.outputs.forEach(function(sock) { 
            html += '<div class="socket_out" id="sock_' + node.id + '_' + sock +'">';
            html += '  <div class="socket_title">' + sock + '</div>';
            html += '  <div class="con_anchor"></div><div class="con_anchor_ghost"></div>';
            html += '</div>';
        })   
    }
    html += '</div>';


    html += '<div class="socket_end"></div> ';
    //html += '</div>';

    
    element.innerHTML = html;
}

function uploadMove(id, x, y, force=false)
{
    console.log("moving ", id, x, y);

    content = JSON.stringify({cmd: "Move", params : {
        id: id,
        x: x,
        y: y
    }});
                
    console.log(content);
    exampleSocket.send(content); 
}
window.uploadMove = uploadMove;

function UploadValue(id, socket, value)
{
    console.log("Set value ", id, socket, value);

    content = JSON.stringify({cmd: "Value", params : {
        id: id,
        sock: socket,
        val: value
    }});
                
    console.log(content);
    exampleSocket.send(content); 
}
window.UploadValue = UploadValue;

function UploadConnect(nodein, sockin, nodeout, sockout)
{
    console.log("Connecting ", nodein, sockin, nodeout, sockout);

    content = JSON.stringify({cmd: "Connect", params : {
        idin: nodein,
        sockin: sockin,
        idout: nodeout,
        sockout: sockout
    }});
                
    console.log(content);
    exampleSocket.send(content); 
}
window.UploadConnect = UploadConnect;

function UploadDisconnect(node, sock)
{
    console.log("Disconnecting ", node, sock);

    content = JSON.stringify({cmd: "Disconnect", params : {
        id: node, 
        sock: sock,
    }});
                
    console.log(content);
    exampleSocket.send(content); 
}
window.UploadDisconnect = UploadDisconnect;