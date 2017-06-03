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

$(document).ready(function(){
  $("input#forminput").bind("keydown",function(event){
    keyCode = event.keyCode;
    symbol = event.key;
    value = $("input#forminput")[0].value;
    if (isKeyIncorrect(keyCode, symbol) || isValueIncorrect(value, keyCode, symbol) || isNumberInorrect(keyCode, parseFloat(value + symbol))){
      event.preventDefault();
    }
  });
});
