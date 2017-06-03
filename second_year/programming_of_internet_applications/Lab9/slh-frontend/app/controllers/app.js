import Ember from 'ember';

export default Ember.Controller.extend({
  isFirstlySelectedRadius : true,
  isAuthenticated : false,
  isProcessing : false,
  radius : 3,

  tryDisable : function(){
    if ((this.get("model").get("r") != undefined) && (this.get("model").get("r") != "") && (this.get("model").get("r") > 0) &&
    (this.get("model").get("y") != "") && (this.get("model").get("y") != undefined) && (this.get("model").get("y") > -5) && (this.get("model").get("y") < 5) &&
    (this.get("model").get("x") != undefined) && (this.get("model").get("x") != ""))
    {
      $('.add').removeAttr("disabled");
    } else {
      $(".add").attr("disabled","true");
    }
  },
  isRadiusValid:Ember.computed("model.r","model.isUpdating",function(){
    //console.log(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>",this.get("model"));
    //console.log(this.get("model").get("content")[0]);

    var container = document.getElementById("area");
    var dot;
    var x;
    var y;
    var inside;
    var exth = this;
    var ml;
    var mt;
    var uniques = [];
    var brokenInternal = false;

    this.tryDisable();
    if (this.get("model").get("r") != undefined){
      if (this.get("radius") == 3){
        $("#activedef").removeClass("active");
      }
      this.set("radius", this.get("model").get("r"));
    }

    if (this.get("radius") > 0){
      //selecting uniques
      this.get("model").get("content").forEach(function(ponto, i, pontos) {
        brokenInternal = false;
        //console.log("Scanning...");
        //console.log(this);
        uniques.forEach(function(uponto, j, upontos){
          if ((uponto.x == ponto.__data.x) && (uponto.y == ponto.__data.y)){
              brokenInternal = true;
              //console.log("same");
              return;
          }
          brokenInternal = false;
        });
        //console.log(brokenInternal);
        if (!brokenInternal){
          uniques.push({x : ponto.__data.x, y : ponto.__data.y});
        }
      });

      //checking uniques on counted
      uniques.forEach(function(uponto, j, upontos){
        brokenInternal = false;
        exth.get("model").get("content").forEach(function(ponto, i, pontos) {
          if ((uponto.x == ponto.__data.x) && (uponto.y == ponto.__data.y) && (exth.get("radius") == ponto.__data.rad)){
              brokenInternal = true;
              return;
          }
        });
        if (!brokenInternal){
          //console.log("need to update");
          var xhr = new XMLHttpRequest();
          xhr.open("POST", "http://localhost:20762/addponto", true);
          xhr.setRequestHeader('Content-Type', 'application/json; charset=UTF-8');
          xhr.onload = function () {
            exth.send("reload");
          };
          xhr.send(JSON.stringify({ x: uponto.x, y: uponto.y, rad : exth.get("radius")}));
        }
      });
    }
    //console.log("UUUUUUUUUUUUUUUUUUUUUUUUU ",uniques);

    if ((this.get("radius") > 0) && (!this.get("model.isUpdating"))){
      container.innerHTML = "";
      this.get("model").get("content").forEach(function(ponto, i, pontos) {
        if (ponto.__data.rad == exth.get("radius")){
          x = ponto.__data.x;
          y = ponto.__data.y;
          inside = ponto.__data.inside;
          dot = document.createElement("div");
          dot.className = "dot";
          if (inside){
              dot.className += " inside";
          }
          ml = (((x/exth.get("radius"))*77.5)+102.5);
          mt = (-y/exth.get("radius")*77.5+102.5);
          dot.style["margin-left"] = ml+"px";
          dot.style["margin-top"] = mt+"px";
          //console.log(dot.style["margin-left"]+" "+dot.style["margin-left"]);
          if (((ml >= 0) && (ml <= 205) && (mt >= 0) && (mt <= 205))){
            //console.log(ponto.__data);
             container.appendChild(dot);
          }
        }
      });
    }



    return ((this.get("model").get("r") != undefined) && (this.get("model").get("r") != "") && (this.get("model").get("r") > 0));
  }),
  isYValid:Ember.computed("model.y",function(){
    this.tryDisable();
    return ((this.get("model").get("y") != "") && (this.get("model").get("y") != undefined) && (this.get("model").get("y") > -5) && (this.get("model").get("y") < 5));
  }),
  isXValid:Ember.computed("model.x",function(){
    this.tryDisable();
    //console.log("x : "+this.get("model").get("x"));
    return ((this.get("model").get("x") != undefined) && (this.get("model").get("x") != ""));
  }),
  init : function(){
    //
    $(document).ready(function(){
      if($(window).width() <= 885) {
          //console.log("---------------------------------");
          //console.log($('.bigheader'));
          $('.bigheader').addClass('bh885');
          $('#area').addClass('area885');
          $('.emberbuttongroup').addClass('ebg885');
          $('.embererror').addClass('ee885');
          $('.embersubmitbutton').addClass('esb885');
          $('.secondaryheader').addClass('sch885');
          $('.embertextfield').addClass('etf885');
          $('#pontos').addClass('pontos885');
        } else if($(window).width() <= 1094) {
            //console.log("---------------------------------");
            //console.log($('.bigheader'));
            $('.bigheader').addClass('bh1094');
            $('#area').addClass('area1094');
            $('.emberbuttongroup').addClass('ebg1094');
            $('.embererror').addClass('ee1094');
            $('.embersubmitbutton').addClass('esb1094');
            $('.secondaryheader').addClass('sch1094');
            $('.embertextfield').addClass('etf1094');
            $('#pontos').addClass('pontos1094');
          } else {
            $('.embersubmitbutton').addClass('esblarge');
            $('.embertextfield').addClass('etflarge');
            $('#pontos').addClass('pontoslarge');
          }
    });

    $(window).on('resize', function() {
      if($(window).width() <= 885) {
          //console.log("---------------------------------");
          //console.log($('.bigheader'));
          $('.bigheader').addClass('bh885');
          $('#area').addClass('area885');
          $('.emberbuttongroup').addClass('ebg885');
          $('.embererror').addClass('ee885');
          $('.embersubmitbutton').addClass('esb885');
          $('.secondaryheader').addClass('sch885');
          $('.embertextfield').addClass('etf885');
          $('#pontos').addClass('pontos885');
        } else {
          $('.bigheader').removeClass('bh885');
          $('#area').removeClass('area885');
          $('.emberbuttongroup').removeClass('ebg885');
          $('.embererror').removeClass('ee885');
          $('.embersubmitbutton').removeClass('esb885');
          $('.secondaryheader').removeClass('sch885');
          $('.embertextfield').removeClass('etf885');
          $('#pontos').removeClass('pontos885');
        }
        if(($(window).width() > 885) && ($(window).width() < 1094)) {
            //console.log("---------------------------------");
            //console.log($('.bigheader'));
            $('.bigheader').addClass('bh1094');
            $('#area').addClass('area1094');
            $('.emberbuttongroup').addClass('ebg1094');
            $('.embererror').addClass('ee1094');
            $('.embersubmitbutton').addClass('esb1094');
            $('.secondaryheader').addClass('sch1094');
            $('.embertextfield').addClass('etf1094');
            $('#pontos').addClass('pontos1094');
          } else {
            $('.bigheader').removeClass('bh1094');
            $('#area').removeClass('area1094');
            $('.emberbuttongroup').removeClass('ebg1094');
            $('.embererror').removeClass('ee1094');
            $('.embersubmitbutton').removeClass('esb1094');
            $('.secondaryheader').removeClass('sch1094');
            $('.embertextfield').removeClass('etf1094');
            $('#pontos').removeClass('pontos1094');
          }
        if($(window).width() >= 1094) {
          $('.embersubmitbutton').addClass('esblarge');
          $('.embertextfield').addClass('etflarge');
          $('#pontos').addClass('pontoslarge');
        } else {
          $('.embersubmitbutton').removeClass('esblarge');
          $('.embertextfield').removeClass('etflarge');
          $('#pontos').removeClass('pontoslarge');
        }
    });

    //
    var external_this = this;
    this.set("r","3");
    ////console.log("RRRRRRRRRRRRRRRRR",this);
    //console.log("all ok");

    this.set("isProcessing", true);
    $.get("http://localhost:20762/login",{}).then(function(data){
      external_this.set("isProcessing", false);
      if (data.result){
        //console.log("authenticated");
        external_this.set("isAuthenticated", true);
        //external_this.set("radius", 3);
        //external_this.set("r", 3);
      }
    }, function(){
      this.set("isProcessing", false);
    }.bind(this));
  },
  actions : {
    logout(){
      $.get("http://localhost:20762/logout",{}).then(function(data){
        document.location = "app";
      });
    },
    login(){
      document.location = "main";
    },
    changeButtonGroupValueX(data){
      //console.log(data);
    },
    changedR(dd){
      //console.log(dd);

      //console.log("radius now is ",r);
    }, add(data){
      ////console.log($("button.rbtn, .active"));
      var x = this.get("model.x");
      var y = this.get("model.y");
      //var r = this.get("model.r");
      var request;
      var ex_th=this;
      var model = this.get("model");
      //console.log(this.get("model.x"));
      //console.log(this.get("model").get("x"));
      //console.log(this.get("model").get("y"));
      ////console.log(this.get("model").get("r"));
      //console.log("adding");

      x.forEach(function(item, i, x) {
        request = "{ x : '"+item+"', y : '"+y+"' }";
        //console.log(request);
        var xhr = new XMLHttpRequest();
        xhr.open("POST", "http://localhost:20762/addponto", true);
        xhr.setRequestHeader('Content-Type', 'application/json; charset=UTF-8');
        xhr.onload = function () {
          ex_th.send("reload");
        };
        xhr.send(JSON.stringify({ x: item, y: y, rad : ex_th.get("radius")}));

        //document.location = "/ui/app";
      });
    }, reload_model(){
      //console.log("reloading...");
    }
  }
});
