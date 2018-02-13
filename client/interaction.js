window.onload=function(){
  
! function(a) {
  function f(a, b) {
    if (!(a.originalEvent.touches.length > 1)) {
      a.preventDefault();
      var c = a.originalEvent.changedTouches[0],
          d = document.createEvent("MouseEvents");
      d.initMouseEvent(b, !0, !0, window, 1, c.screenX, c.screenY, c.clientX, c.clientY, !1, !1, !1, !1, 0, null), a.target.dispatchEvent(d)
    }
  }

  if (a.support.touch = "ontouchend" in document, a.support.touch) {
    var e, b = a.ui.mouse.prototype,
      c = b._mouseInit,
      d = b._mouseDestroy;
    b._touchStart = function(a) {
      var b = this;
      !e && b._mouseCapture(a.originalEvent.changedTouches[0]) && (e = !0, b._touchMoved = !1, f(a, "mouseover"), f(a, "mousemove"), f(a, "mousedown"))
    }, b._touchMove = function(a) {
      e && (this._touchMoved = !0, f(a, "mousemove"))
    }, b._touchEnd = function(a) {
      e && (f(a, "mouseup"), f(a, "mouseout"), this._touchMoved || f(a, "click"), e = !1)
    }, b._mouseInit = function() {
      var b = this;
      b.element.bind({
        touchstart: a.proxy(b, "_touchStart"),
        touchmove: a.proxy(b, "_touchMove"),
        touchend: a.proxy(b, "_touchEnd")
      }), c.call(b)
    }, b._mouseDestroy = function() {
      var b = this;
      b.element.unbind({
        touchstart: a.proxy(b, "_touchStart"),
        touchmove: a.proxy(b, "_touchMove"),
        touchend: a.proxy(b, "_touchEnd")
      }), d.call(b)
    }
  }
}(jQuery);


//reposition the connector line between the sockets. used when dragging and dropping
function positionConnector(line){
  var anchor1 = $(line).data('anchor1');
  var anchor2 = $(line).data('anchor2');

  var x1 = 6+$(anchor1).position().left + $(anchor1).closest('.ui-item').position().left,
      y1 = 6+$(anchor1).position().top  + $(anchor1).closest('.ui-item').position().top,
      x2 = 6+$(anchor2).position().left + $(anchor2).closest('.ui-item').position().left,
      y2 = 6+$(anchor2).position().top  + $(anchor2).closest('.ui-item').position().top;

  //the ghost class has a marginleft of -8px, also render the line 8px to the left
  if (anchor2.hasClass('con_anchor_ghost')) x2-=8;

  $(line).attr('x1', x1)
         .attr('y1', y1)
         .attr('x2', x2)
         .attr('y2', y2);
}

function removeConnector(line){
  $(line).data('anchor1').data('line',null);
  $(line).data('anchor2').data('line',null);
  $(line).remove();
}

function removeAllConnectors()
{
  $("#connector_canvas").children("line").each(function (element) {
    removeConnector(this);
  });
}

function createConnector(anchor1, anchor2)
{
  var connector = $('#connector_canvas');

  //create the line
  var cur_con = $(document.createElementNS('http://www.w3.org/2000/svg', 'line'));
  connector.append(cur_con);

  cur_con.data('anchor1', anchor1); 
  cur_con.data('anchor2', anchor2); 
  anchor1.data('line',cur_con);
  anchor2.data('line',cur_con);

  //position the line
  positionConnector(cur_con);
}

window.removeAllConnectors = removeAllConnectors;
window.removeConnector = removeConnector;
window.createConnector = createConnector;

//code to move the nodes around
$('.node').draggable({
  containment: "#canvas",
  drag: function(event, ui) {

    event.target.setAttribute('x', ui.position.left);
    event.target.setAttribute('y', ui.position.top);

    //also move the lines along
    $(this).find('.con_anchor').each(function(id,anchor){
      if ($(anchor).data('line')){
        positionConnector($(anchor).data('line'));
      }
    });
 
  },
  stop: function(event, ui ){
    //console.log("dropped");
    window.uploadMove(this.getAttribute("bid"),ui.position.left,ui.position.top)
  }
});


$('.socket_in .con_anchor').droppable({
  accept: '.con_anchor_ghost',
  drop: function(event, ui) {
    console.log('dropped');
    //the connection is made, connect the line to the new anchor, and move back the ghost

    //get the dragged line
    var line = ui.draggable.data('line');

    //set the new anchor as endpoint of the line
    line.data('anchor2',$(this));

    //set the line in the current anchor
    $(this).data('line',line);
    
    //remove the line reference from the ghost anchor
    ui.draggable.data('line',null);

    positionConnector(line);

    //nb: the ghost is moved back to 0,0 by draggable{stop:}
  }
});


$('.con_anchor_ghost').draggable({
  containment: "#canvas",
  drag: function(event, ui) {
    positionConnector($(event.target).data('line'));  
  },
  stop: function(event, ui) {

    //if the ghost has no line,  the drop was succesful, and and the line is now connected
    //to an input anchor. even if we could access it, we didnt want to remove it.
    if (ui.helper.data('line')) {

      //remove the line
      removeConnector(ui.helper.data('line'));

    }

    //move the ghost back to where it came from
    ui.helper.css({
      top: 0,
      left: 0
    });

  }
});

$('.con_anchor_ghost').on('mousedown', function(e) {
  var anchor = $(this).parent().children('.con_anchor'); //the anchor in the node that doesnt move
  var anchor_ghost = $(this); //the ghost anchor that is dragged around

  createConnector(anchor, anchor_ghost);

});

}