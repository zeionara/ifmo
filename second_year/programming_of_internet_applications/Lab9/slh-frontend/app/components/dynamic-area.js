import Ember from 'ember';

export default Ember.Component.extend({
  needs : ['controller'],
  click: function(e) {
    console.log(this.controller);
    if (!((e.offsetX <= 205) && (e.offsetX >= 0) && (e.offsetY <= 205) && (e.offsetY >= 0))) return;
    var x = (e.offsetX-102.5)/77.5*this.controller.get("radius");
    var y = (-e.offsetY+102.5)/77.5*this.controller.get("radius");
    var ex_this = this;
    console.log("x is ",x);
    console.log("y is ",y);
    var ex_th = this;

    var request = "{ x : '"+x+"', y : '"+y+"' }";
    console.log(request);
    var xhr = new XMLHttpRequest();

    xhr.open("POST", "http://localhost:20762/addponto", true);
    xhr.setRequestHeader('Content-Type', 'application/json; charset=UTF-8');
    xhr.onload = function () {
      ex_th.controller.send("reload");
    };
    xhr.send(JSON.stringify({ x: x, y: y, rad: ex_th.controller.get("radius")}));


    //document.location = "/ui/app";
  }
});
