import Ember from 'ember';

export default Ember.Component.extend({
  init(){
    //var x = (e.offsetX-102.5)/77.5*this.controller.r;
    //var y = (-e.offsetY+102.5)/77.5*this.controller.r;
    /*console.log(this);
    console.log($("div.dot")+this.x+this.y+this.r);
    console.log((this.x/this.r*77.5+102.5)+"px");
    console.log(Ember.$("div#dot"+this.id));
    var container = document.getElementById("area");
    var dot = document.createElement("div");
    dot.className = "dot";
    dot.style["margin-left"] = (((this.x/this.r)*77.5)+102.5)+"px";
    dot.style["margin-top"] = (-this.y/this.r*77.5+102.5)+"px";
    container.appendChild(dot);*/
    //$("div#dot"+this.id).css("margin-left",(((this.x/this.r)*77.5)+102.5)+"px");
    //$("div#dot"+this.id).css("margin-top",(-this.y/this.r*77.5+102.5)+"px");
    this._super();
  }
});
