function isKeyIncorrect(keyCode,symbol){
  return (keyCode != 189 && keyCode != 8 && keyCode != 39 && keyCode != 37 && symbol != '1' && symbol != '2' && symbol != '3' && symbol != '4' &&
   symbol != '5' && symbol != '6' && symbol != '7' && symbol != '8' && symbol != '9' && symbol != '0' && symbol != '.')
}

function isValueIncorrect(value,keyCode,symbol){
  return ((keyCode == 189) && (value.length > 0)) || ((symbol == '.') && (value.indexOf('.') + 1));
}

function isNumberInorrect(keyCode,number){
  return ((keyCode >= 48 && keyCode <= 57) || (keyCode == 190)) && ((number <= -5.0) || (number >= 5.0));
}

function isInArea(x,y,radius,dot,cell){
  var xhr = new XMLHttpRequest();
  var body = 'x=' + encodeURIComponent(x) +'&y=' + encodeURIComponent(y) + "&radius=" + encodeURIComponent(radius);
  console.log(body);

  xhr.open("POST", '/pip.lab2/home', true)
  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded')

  xhr.onreadystatechange = function () {
        if(xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
            console.log(xhr.responseText);
            if(xhr.responseText.indexOf("OUT") != -1){
              dot.style.backgroundColor = "red";
              cell.innerHTML = "OUT";
              return false;
            };
        };
    };

  xhr.send(body);
  return true;
}

function fillGraph(){
  tablepontos = document.getElementById("pontos").childNodes[0];
  radius = $("[name = radius]")[0].value*1;
  for (childItem in tablepontos.childNodes) {
    if (tablepontos.childNodes[childItem].nodeType == 1)
      if (tablepontos.childNodes[childItem].childNodes != undefined){
        if (tablepontos.childNodes[childItem].childNodes[0].innerHTML == "x") continue;
        dot = document.createElement('div');
        dot.className = "dot";
        console.log(tablepontos.childNodes[childItem]);
        ml = (tablepontos.childNodes[childItem].childNodes[0].innerHTML*80/radius+101);
        mt = (-tablepontos.childNodes[childItem].childNodes[1].innerHTML*80/radius+105);
        dot.style.marginLeft = (tablepontos.childNodes[childItem].childNodes[0].innerHTML*80/radius+101) + "px";
        dot.style.marginTop = (-tablepontos.childNodes[childItem].childNodes[1].innerHTML*80/radius+105) + "px";
        if ((ml >= 0) && (ml <= 205) && (mt >= 0) && (mt <= 205)){
          $("div#area").append(dot);
        }
        dot.style.backgroundColor = "green";
        if (tablepontos.childNodes[childItem].childNodes[3].innerHTML.indexOf("OUT") != -1){
          dot.style.backgroundColor = "red";
        }
        if (tablepontos.childNodes[childItem].childNodes[2].innerHTML != radius){
          console.log("Rechecking ..."+childItem);
          tablepontos.childNodes[childItem].childNodes[3].innerHTML = "IN";
          dot.style.backgroundColor = "green";
          isInArea(tablepontos.childNodes[childItem].childNodes[0].innerHTML,tablepontos.childNodes[childItem].childNodes[1].innerHTML,radius,dot,tablepontos.childNodes[childItem].childNodes[3]);
          tablepontos.childNodes[childItem].childNodes[2].innerHTML = radius;
        }
      }
    }
}

function insertAfter(elem, refElem) {
  return refElem.parentNode.insertBefore(elem, refElem.nextSibling);
}

$(document).ready(function(){
  if (document.getElementById("pontos").childNodes[0] != undefined){
    fillGraph();
  }

  $("input#forminput").bind("keyup",function(event){
    $("input#forminput")[0].value = $("input#forminput")[0].value.replace(/\,/, ".");
    keyCode = event.keyCode;
    symbol = event.key;
    value = $("input#forminput")[0].value;
    if ((isNaN(value)) || (parseFloat(value) < -5.0) || (parseFloat(value) > 5.0)){
		$("input#forminput").css("background-color", "red");
	 }
	  if (!isNaN(value) && parseFloat(value) >= -5.0 && parseFloat(value) <= 5.0){
		    $("input#forminput").css("background-color", "white");
	  }
  });
  $("input#formsubmit").bind("click",function(event){
	   if ($("input#forminput")[0].value == "" || isNaN($("input#forminput")[0].value) || parseFloat($("input#forminput")[0].value) < -5.0 || parseFloat($("input#forminput")[0].value) > 5.0){
		     alert("Y cannot has the value!");
		     event.preventDefault();
	   }
  });
  $("div#area").bind("click",function(event){
	   if (!isNaN($("[name = radius]")[0].value)){
       radius = $("[name = radius]")[0].value*1;
       x = (event.pageX - event.target.offsetLeft - 103)*(radius/80);
       y = (-(event.pageY - event.target.offsetTop) + 107)*(radius/80);

       dot = document.createElement('div');
       dot.className = "dot";
       console.log(dot.style.marginLeft);
       dot.style.marginLeft = (event.pageX - event.target.offsetLeft - 2) + "px";
       dot.style.marginTop = (event.pageY - event.target.offsetTop - 2) + "px";
       this.appendChild(dot);
       dot.style.backgroundColor = "green";

         raw = document.createElement("tr");
         cell = document.createElement("td");
         cell.innerHTML = x;
         raw.appendChild(cell);
         cell = document.createElement("td");
         cell.innerHTML = y;
         raw.appendChild(cell);
         cell = document.createElement("td");
         cell.innerHTML = radius;
         raw.appendChild(cell);
         cell = document.createElement("td");
         cell.innerHTML = "IN";

         result = isInArea(x,y,radius,dot,cell);
         raw.appendChild(cell);
         document.getElementById("pontos").childNodes[0].appendChild(raw);
     } else {
       alert("Cannot define coordinates : radius wasn't set");
     }
  });
  $( "[name = radius]" ).change(function() {
    $("div#area > div.dot").detach();
    fillGraph();
  });
});
