function removeChilds(element, num_left){
  while(element.childNodes.length > num_left) element.removeChild(element.lastChild);
}

function showCooks(data){
  for (var i=0; i < data.length; i++){//for each cook

    var rawElement = document.createElement('tr');
    rawElement.setAttribute("class","cookinfo");

    for (key in data[i]){//for each property of cook
      if (key == 'workingmode_2_2') continue;

      var cellElement = document.createElement('td');
      cellElement.innerHTML = data[i][key];
      cellElement.setAttribute("class",key);

      ((data[i][key] == 1)&&(key != 'cookid'))?cellElement.innerHTML = 'yes':data[i][key] == 0?cellElement.innerHTML = 'no':console.log();

      if (key == 'workingmode_5_2'){
        data[i][key] == 1?cellElement.innerHTML = '5/2':cellElement.innerHTML = '2/2';
        cellElement.setAttribute("class","workingmode");
      }
      rawElement.appendChild(cellElement);
    }//for each property of cook
    document.getElementById("cooks").appendChild(rawElement);
  }//for each cook
}

function loadCooksInfo(){
    removeChilds(document.getElementById("cooks"), 2);//clear table
    $.ajax({
      type : "post",
      url : "/load_cooks_handler",
      success : function(data){
        showCooks(data);
      },
    });
}

function showActionResult(form_elems, result, good_result, good_msg, bad_msg){
  resetError(form_elems.submit.parentNode);
  resetNotification(form_elems.submit.parentNode);
  if (result==good_result) {
    showNotification(form_elems.submit.parentNode, good_msg);
  } else {
    showError(form_elems.submit.parentNode, bad_msg+" : "+data);
  }
}

function getRequestObject(action, form){
  var cookid;

  if(action == "edit") cookid = cid;

  var name = form.elements["name"].value;
  var surname = form.elements["surname"].value;
  var patronymic = form.elements["patronymic"].value;

  var japanese = form.elements["japanese"].checked;
  var italian = form.elements["italian"].checked;
  var russian = form.elements["russian"].checked;

  var morningshifts = false;
  var eveningshifts = false;
  if (form.elements["shiftstime"].value == 'evening'){
    eveningshifts = true;
  } else {
    morningshifts = true;
  }

  var necessityshiftstime = form.elements["necessityshiftstime"].checked;

  var dayduration = form.elements["dayduration"].value;
  var necessitydayduration = form.elements["necessitydayduration"].checked;

  var workingmode_5_2 = false;
  var workingmode_2_2 = false;
  if (form.elements["workingmode"].value == '5/2'){
    workingmode_5_2 = true;
  } else {
    workingmode_2_2 = true;
  }

  if (action == "edit"){
    return {cookid : cookid, name : name, surname : surname, patronymic : patronymic, russian : russian, italian : italian, japanese : japanese,
    morningshifts : morningshifts, eveningshifts : eveningshifts, necessityshiftstime : necessityshiftstime, dayduration : dayduration,
    necessitydayduration : necessitydayduration, workingmode_5_2 : workingmode_5_2, workingmode_2_2 : workingmode_2_2};
  } else {
    return {name : name, surname : surname, patronymic : patronymic, russian : russian, italian : italian, japanese : japanese,
    morningshifts : morningshifts, eveningshifts : eveningshifts, necessityshiftstime : necessityshiftstime, dayduration : dayduration,
    necessitydayduration : necessitydayduration, workingmode_5_2 : workingmode_5_2, workingmode_2_2 : workingmode_2_2};
  }
}

function addNewCook(e){
  e.preventDefault();

  if(isValid(this)){

    var form = this;

    $.ajax({
      type : "post",
      url : "/addnew_handler",
      data : JSON.stringify(getRequestObject("addnew",form)),
      dataTpe : "json",
      contentType : "application/json",
      success : function(data){
        loadCooksInfo();
        showActionResult(form.elements, data, "Accepted", "New cook added", "New cook wasn't added");
      },
    });
  };//if(isValid(this))
}

function editCook(e){
  e.preventDefault();

  if(isValid(this)){

    var form = this;

    $.ajax({
      type : "post",
      url : "/edit_handler",
      data : JSON.stringify(getRequestObject("edit",form)),
      dataTpe : "json",
      contentType : "application/json",
      success : function(data){
        loadCooksInfo();
        showActionResult(form.elements, data, "Accepted", "Changes saved", "Changes wasn't saved");
      },
    });//ajax
  };//if(isValid(this))
}

function showMessage(container, classNameContainer, elementName, classNameElement, message){
  container.className = classNameContainer;
  var msgElem = document.createElement(elementName);
  msgElem.className = classNameElement;
  msgElem.innerHTML = message;
  container.appendChild(msgElem);
}

function resetMessage(container, classNameElement) {
  container.className = '';
  if (container.lastChild.className == classNameElement) {
    container.removeChild(container.lastChild);
  }
}

function showError(container, errorMessage) {
  showMessage(container,"error","span","error-message",errorMessage);
}

function showNotification(container, notificationMessage) {
  showMessage(container,"notification","span","notification-message",notificationMessage);
}

function resetError(container) {
  resetMessage(container, "error-message");
}

function resetNotification(container) {
  resetMessage(container, "notification-message");
}

function validate(element, condition, errorMessage){
  resetError(element);
  if (!condition) {
    showError(element, errorMessage);
    return false;
  }
  return true;
}

function isValid(form) {
  var elems = form.elements;
  var RegLetters = new RegExp("^[A-zА-яЁё]+$");
  var valid = true;

  valid = validate(elems.name.parentNode, (elems.name.value && RegLetters.test(elems.name.value)), "Please, type valid name");
  if(valid == false) return false;

  valid = validate(elems.surname.parentNode, (elems.surname.value && RegLetters.test(elems.surname.value)), "Please, type valid surname");
  if(valid == false) return false;

  valid = validate(elems.russian.parentNode, (elems.russian.checked || elems.italian.checked || elems.japanese.checked), "Cook can\'t have no qualifications");
  if(valid == false) return false;

  valid = validate(elems.shiftstime[0].parentNode, (elems.shiftstime.value!=""), "Cook can\'t have no desired time of shifts");
  if(valid == false) return false;

  valid = validate(elems.dayduration.parentNode,
    (!((parseInt(elems.dayduration.value) > parseInt(elems.dayduration.max)) || (parseInt(elems.dayduration.value) < parseInt(elems.dayduration.min)))),
    "Please, select valid duration of the working day");

  return valid;
}

function setAlternative(rawElement, form_id, old_attribute, new_attribute, good_value, new_good, new_bad){
  if(rawElement.getElementsByClassName(old_attribute)[0].innerHTML == good_value){
    document.getElementById(form_id).elements[new_attribute].value = new_good;
  } else {
    document.getElementById(form_id).elements[new_attribute].value = new_bad;
  }
}

function setSwitcher(rawElement, form_id, old_attribute, new_attribute, good_value){
  if(rawElement.getElementsByClassName(old_attribute)[0].innerHTML == good_value){
    document.getElementById(form_id).elements[new_attribute].checked = true;
  } else {
    document.getElementById(form_id).elements[new_attribute].checked = false;
  }
}


function initializeEditingCook(e){
  if(e.target.parentNode != document.getElementById("cooks").getElementsByTagName("tr")[0]){
    var rawElement = e.target.parentNode;

    cid = rawElement.getElementsByClassName("cookid")[0].innerHTML;
    document.getElementById("edit").elements["name"].value = rawElement.getElementsByClassName("name")[0].innerHTML;
    document.getElementById("edit").elements["surname"].value = rawElement.getElementsByClassName("surname")[0].innerHTML;

    setAlternative(rawElement, "edit", "patronymic", "patronymic", "no", "", rawElement.getElementsByClassName("patronymic")[0].innerHTML);

    setSwitcher(rawElement, "edit", "russian", "russian", "yes");

    setSwitcher(rawElement, "edit", "italian", "italian", "yes");

    setSwitcher(rawElement, "edit", "japanese", "japanese", "yes");

    setAlternative(rawElement, "edit", "morningshifts", "shiftstime", "yes", "morning", "evening");

    setSwitcher(rawElement, "edit", "necessityshiftstime", "necessityshiftstime", "yes");

    document.getElementById("edit").elements["dayduration"].value = rawElement.getElementsByClassName("dayduration")[0].innerHTML;

    setSwitcher(rawElement, "edit", "necessitydayduration", "necessitydayduration", "yes");

    setAlternative(rawElement, "edit", "workingmode", "workingmode", "5/2", "5/2", "2/2");

    showEditingForm();
  }
}

function showEditingForm(){
  $('#overlay').fadeIn(400,
		 	function(){
				$('#modal_form')
					.css('display', 'block')
					.animate({opacity: 1, top: '50%'}, 200);
	});
}

function hideEditingForm(){
  $('#modal_form')
    .animate({opacity: 0, top: '45%'}, 200,
      function(){
        $(this).css('display', 'none');
        $('#overlay').fadeOut(400);
        resetError(document.getElementById("edit").elements["submit"].parentNode);
        resetError(document.getElementById("edit").elements["russian"].parentNode);
        resetNotification(document.getElementById("edit").elements["submit"].parentNode);
      }
    );
}

function deleteCook(){
  console.log("delete");
  var cookid = cid;

  $.ajax({
    type : "post",
    url : "/delete_handler",
    data : JSON.stringify({cookid : cookid}),
    dataTpe : "json",
    contentType : "application/json",
    success : function(data){
      console.log(data);
      loadCooksInfo();
      showActionResult(document.getElementById("edit").elements, data, "Accepted", "Cook deleted", "Cook wasn't deleted");
    },
  });
}

function switchCooksVisibility(){
  if($("table#cooks").css("display") == "table"){
    document.getElementById("hide_cooks").innerHTML = "Show";
    $("table#cooks").css("display","none");
  } else {
    document.getElementById("hide_cooks").innerHTML = "Hide";
    $("table#cooks").css("display","table");
  }
}

function addNewElement(name,className,innerHTML,parent_id,id){
  var elem = document.createElement(name);
  if(className != "") elem.className = className;
  if(innerHTML != "") elem.innerHTML = innerHTML;
  if(id != "") elem.id = id;
  console.log(document.getElementById(parent_id));
  console.log(parent_id);
  document.getElementById(parent_id).appendChild(elem);
}

function showAntiSchedule(data){
  removeChilds(document.getElementById("schedule"), 0);

  addNewElement("h3","bad_schedule_header","Can't make schedule with this params.","schedule","");

  addNewElement("h3","bad_schedule_header","Required : ","schedule","");

  addNewElement("ul","","","schedule","bad_schedule_list");

  var kitchen;
  for (var i = 0; i < data.length; i++){
      if (i == 0) kitchen = "russian";
      if (i == 1) kitchen = "italian";
      if (i == 2) kitchen = "japanese";

      for (var j = 0; j < data[i].length; j++){
        if (data[i][j] < 24){
          var liElem = document.createElement("li");
          liElem.innerHTML = "Cook(s) for "+kitchen+" kitchen in "+(j+1)+" restaurant for time "+data[i][j]+":00 - 24:00";
          document.getElementById("bad_schedule_list").appendChild(liElem);
        }
      }
  }
}

function showSchedule(data){
  removeChilds(document.getElementById("schedule"), 0);

  addNewElement("h3","good_schedule_header","Schedule","schedule","")

  addNewElement("ul","","","schedule","good_schedule_list")

  var kitchen;
  for (var i = 0; i < data.length; i++){

    addNewElement("li","",(i+1)+" day :","good_schedule_list","day_"+i);

    addNewElement("ul","day_list","","day_"+i,"good_schedule_list_day_"+i);

    for (var j = 0; j < data[i].length; j++){

      addNewElement("li","",(j+1)+" restaurant :","good_schedule_list_day_"+i,"day_"+i+"_restaurant_"+j);

      addNewElement("ul","restaurant_list","","day_"+i+"_restaurant_"+j,"good_schedule_list_day_"+i+"_restaurant_"+j);

      for (var k = 0; k < data[i][j].length; k++){
        if (k == 0) kitchen = "russian";
        if (k == 1) kitchen = "italian";
        if (k == 2) kitchen = "japanese";

        addNewElement("li","",kitchen+" kitchen : ","good_schedule_list_day_"+i+"_restaurant_"+j,"day_"+i+"_restaurant_"+j+"_kitchen_"+k);

        addNewElement("ul","kitchen_list","","day_"+i+"_restaurant_"+j+"_kitchen_"+k,"good_schedule_list_day_"+i+"_restaurant_"+j+"_kitchen_"+k);

        for (var l = 0; l < data[i][j][k].length; l++){
          addNewElement("li","",data[i][j][k][l].snp+"( id = "+data[i][j][k][l].id+" ) : "+data[i][j][k][l].worktime,
            "good_schedule_list_day_"+i+"_restaurant_"+j+"_kitchen_"+k,"");
        }
      }
    }
  }
}

function createScedule(){
  var num_of_restaurants = document.getElementById("num_of_restaurants").value;

  $.ajax({
    type : "post",
    url : "/create_scedule_handler",
    data : JSON.stringify({num_of_restaurants : num_of_restaurants}),
    dataTpe : "json",
    contentType : "application/json",
    success : function(data){
      if (typeof(data[0][0]) == "number"){
        showAntiSchedule(data);
      } else {
        showSchedule(data);
      }
      //loadCooksInfo();
    },
  });//ajax
}

$(document).ready(function(){

  loadCooksInfo();

  $("form#addnew").submit(addNewCook);

  $("button#load_cooks").click(loadCooksInfo);

  $("button#hide_cooks").click(switchCooksVisibility);

  $("input#delete").click(deleteCook);

  $("table#cooks").click(initializeEditingCook);

  $('#modal_close, #overlay').click(hideEditingForm);

  $("form#edit").submit(editCook);

  $("button#create_scedule").click(createScedule);
});
