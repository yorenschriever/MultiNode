

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
        drawNode(nodes[node.id].node, nodes[node.id].element); 
    }
    

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
            html += '<div class="socket_in" id="sock_' + node.id + '_' + sock.name +'">';
            html += '  <div class="con_anchor"></div>';
            html += '  <div class="socket_title">' + sock.name + '</div>';
            html += '</div>';
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
    //todo throttle 

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