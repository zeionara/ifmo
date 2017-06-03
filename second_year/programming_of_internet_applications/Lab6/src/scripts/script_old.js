$(document).ready(function(){
  $("input#forminput").bind("keydown",function(event){
    kc = event.keyCode;
    c = event.key;
    if (kc != 189 && kc != 8 && kc != 39 && kc != 37 && c != '1' && c != '2' && c != '3' && c != '4' &&
     c != '5' && c != '6' && c != '7' && c != '8' && c != '9' && c != '0' && c != '.'){
      event.preventDefault();
    } else if (!(((kc >= 48 && kc <= 57) || (kc == 190)) && (parseFloat($("input#forminput")[0].value+c) >= -5.0) &&
    (parseFloat($("input#forminput")[0].value+c) <= 5.0))){
      console.log($("input#forminput")[0].value.length > 0);
      if ((kc != 8 && kc != 39 && kc != 37)){
        if (kc == 189){
          if ($("input#forminput")[0].value.length > 0){
            event.preventDefault();
          }
        } else {
          event.preventDefault();
        }
      }
    }
  });
});
