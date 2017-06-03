var express = require('express');
var bodyParser = require('body-parser');
var mysql = require('mysql');

var app = new express();
var jsonParser = bodyParser.json();
var connection = mysql.createConnection({
  host : "127.0.0.1",
  user : "root",
  password: "stopper",
  database : "dbmain",
});

app.use(express.static(__dirname + "/public"));
app.get("/",function(request,response){
  response.send("Main page");
});

app.post("/addnew_handler",jsonParser,function(request,response){
    if(!request.body) return response.sendStatus(400);

    connection.query("INSERT INTO cooks (name, surname, patronymic, russian, italian, japanese, morningshifts, eveningshifts, "+
    "necessityshiftstime, dayduration, necessitydayduration, workingmode_5_2, workingmode_2_2) "+
    "VALUES ('"+request.body.name+"', '"+request.body.surname+"', '"+request.body.patronymic+"', "+request.body.russian+", "+request.body.italian+", "+
    request.body.japanese+", "+request.body.morningshifts+", "+request.body.eveningshifts+", "+request.body.necessityshiftstime+", "+request.body.dayduration+
    ", "+request.body.necessitydayduration+", "+request.body.workingmode_5_2+", "+request.body.workingmode_2_2+");",function(error,result,fields){
      if(error) return response.json(error);
    });

    //console.log(request.body)
    response.json("Accepted");
});

app.post("/edit_handler",jsonParser,function(request,response){
    if(!request.body) return response.sendStatus(400);

    var rb = request.body;

    connection.query("UPDATE cooks SET name = '"+rb.name+"', surname = '"+rb.surname+"', patronymic = '"+rb.patronymic+"', russian = "+rb.russian+", italian = "+rb.italian+
    ", japanese = "+rb.japanese+", morningshifts = "+rb.morningshifts+", eveningshifts = "+rb.eveningshifts+", necessityshiftstime = "+rb.necessityshiftstime+
    ", dayduration = "+rb.dayduration+", necessitydayduration = "+rb.necessitydayduration+", workingmode_5_2 = "+rb.workingmode_5_2+", workingmode_2_2 = "+
    rb.workingmode_2_2+" WHERE cookid = "+rb.cookid+";",function(error,result,fields){
      if(error) return response.json(error);
    });

    response.json("Accepted");
});

app.post("/delete_handler",jsonParser,function(request,response){
    if(!request.body) return response.sendStatus(400);

    connection.query("DELETE FROM cooks WHERE cookid = "+request.body.cookid+";",function(error,result,fields){
      if(error) return response.json(error);
    });

    response.json("Accepted");
});

app.post("/load_cooks_handler",jsonParser,function(request, response){
  console.log("ok");
  connection.query("SELECT * FROM cooks",function(error,result,fields){
    if(error) return response.json(error);
    response.json(result);
  });
});

app.post("/create_scedule_handler",jsonParser,function(request,response){
    if(!request.body) return response.sendStatus(400);

    var result = connection.query("SELECT * FROM cooks",function(error,result,fields){
      if(error) return response.json(error);
      var schedule = createSchedule(result,parseInt(request.body.num_of_restaurants));
      response.json(schedule);
    });

});

function generateDayConfig(qualification, hour, dayduration, preferred){
  var day_config = {};
  day_config.qualification = qualification;
  day_config.begin_hour = hour;
  day_config.end_hour = hour + dayduration;
  day_config.preferred = preferred;
  return day_config;
}

function addAllPossibleConfigs(day_configs, dayduration, qualification, preferred, begin_hour, end_hour){
  for (var hour = begin_hour; hour <= end_hour; hour++){
    day_configs.push(generateDayConfig(qualification,hour,dayduration,preferred));
  }
}

function handleShiftsTime(necessityshiftstime, morningshifts, day_configs, dayduration, qualification, longday, preferred){
  var begin_hour_morning = 10;
  var end_hour_morning = 17 - dayduration;

  var begin_hour_evening = 17;
  var end_hour_evening = 24 - dayduration;

  var good_shift_time = 1;
  var bad_shift_time = 0;

  if (longday == 1){
    end_hour_morning = begin_hour_morning;
    begin_hour_evening = end_hour_evening;
  }

  if (preferred == 0){
    // preferred = 0 if it's not selected, but acceptable day duration
    good_shift_time = 0;
  }

  if (necessityshiftstime == 1){
    if (morningshifts == 1){
        addAllPossibleConfigs(day_configs, dayduration, qualification, good_shift_time, begin_hour_morning, end_hour_morning);
    } else {
        addAllPossibleConfigs(day_configs, dayduration, qualification, good_shift_time, begin_hour_evening, end_hour_evening)
    }// if it is only evening shifts
  } else {
    if (morningshifts == 1){
        addAllPossibleConfigs(day_configs, dayduration, qualification, good_shift_time, begin_hour_morning, end_hour_morning);
        addAllPossibleConfigs(day_configs, dayduration, qualification, bad_shift_time, begin_hour_evening, end_hour_evening);
    } else {
        addAllPossibleConfigs(day_configs, dayduration, qualification, good_shift_time, begin_hour_morning, end_hour_morning);
        addAllPossibleConfigs(day_configs, dayduration, qualification, bad_shift_time, begin_hour_evening, end_hour_evening);
    }// if it is only evening shifts
  }// if shiftstime is not very important
}

function handleDayDuration(dayduration, necessityshiftstime, morningshifts, day_configs, qualification, preferred){
  if (dayduration <= 7){
    handleShiftsTime(necessityshiftstime, morningshifts, day_configs, dayduration, qualification, 0, preferred);
  } else {
    handleShiftsTime(necessityshiftstime, morningshifts, day_configs, dayduration, qualification, 1, preferred);
  }
}

function handleNecessityDayDuration(necessitydayduration, dayDuration, necessityshiftstime, morningshifts, day_configs, qualification){
  if (necessitydayduration == 1){
    handleDayDuration(dayDuration, necessityshiftstime, morningshifts, day_configs, qualification, 1);
  } else {
    handleDayDuration(dayDuration, necessityshiftstime, morningshifts, day_configs, qualification, 1);
    for (var dayduration = 4; dayduration <= 10; dayduration++){
      if (dayduration == dayDuration) continue;
      handleDayDuration(dayduration, necessityshiftstime, morningshifts, day_configs, qualification, 0);
    }//for each day duration
  }// if dayduration is not very important
}

function handleDays(cook, cook_config){
  if (cook.russian == 1) handleNecessityDayDuration(cook.necessitydayduration, cook.dayduration,
    cook.necessityshiftstime, cook.morningshifts, cook_config.days, "russian");

  if (cook.italian == 1) handleNecessityDayDuration(cook.necessitydayduration, cook.dayduration,
    cook.necessityshiftstime, cook.morningshifts, cook_config.days, "italian");

  if (cook.japanese == 1) handleNecessityDayDuration(cook.necessitydayduration, cook.dayduration,
    cook.necessityshiftstime, cook.morningshifts, cook_config.days, "japanese");
}

function getCooksAttributes(cook){
  var cook_config = {};
  cook_config.workdaycounter = 0;
  cook_config.restdaycounter = 0;
  cook_config.busy = 0;
  cook_config.workingmode_5_2 = cook.workingmode_5_2;
  cook_config.days = [];//set of possible roles in working day

  handleDays(cook, cook_config);
  return cook_config;
}

function handleConfigurations(cooks){
  var cooks_attributes = new Array(cooks.length);//here we will keep additional attributes of cooks

  for (i in cooks) cooks_attributes[i] = getCooksAttributes(cooks[i]);

  return cooks_attributes;
}

function createSchedule(cooks,num_of_restaurants){
  var num_of_days = 30;
  var num_of_kitchens = 3;

  var preferring_constraint = 1;
  var schedule = initializeSchedule(schedule, num_of_days, num_of_restaurants, num_of_kitchens)
  var cooks_attributes = handleConfigurations(cooks);
  var time_restaurants = initializeTimeRestaurants(num_of_kitchens, num_of_restaurants);

  var counter = 0;
  var broke = false;

  for (var day = 0; day < num_of_days; day++){//for each day in month
    preferring_constraint = 1;//firstly try to create schedule, which will be preferred for all
    unbusyAll(cooks_attributes);
    clearTimeRestaurants(time_restaurants);
    while(!isAllBusy(time_restaurants)){// while restaurants is not enough full of cooks
      if (isAllCooksBusy(cooks_attributes)) {
        return time_restaurants;//no way because can't find unbusy cook
      }
      for (var g = 0; g < num_of_kitchens; g++){//for each kitchen
        for (var h = 0; h < num_of_restaurants; h++){// for each restaurant
          if (time_restaurants[g][h] == 24) continue;// we don't need to check handled restaurants again
          broke = false;
          for (var i = 0; i < cooks.length; i++){// for each cook
            if(cooks_attributes[i].busy == 1){
              if (i == (cooks.length - 1)){
                if (preferring_constraint == 1){
                  preferring_constraint = 0;
                  continue;
                }
                return time_restaurants;//no way because can't find required cook
              }
              continue;// if cook already busy (or get rest today), skip him
            }

            if (handleWorkCounters(cooks_attributes[i], 1, 5)) continue;//must we give to this cook a day rest?

            if (handleWorkCounters(cooks_attributes[i], 0, 2)) continue;//must we give to this cook a day rest?

            for (var l = 0; l < cooks_attributes[i].days.length; l++){//for each configure of the day

              if ((cooks_attributes[i].days[l].begin_hour == time_restaurants[g][h]) &&// if it is required time at the moment
                (cooks_attributes[i].days[l].preferred >= preferring_constraint) &&//if it is enough preferred
                (((24-cooks_attributes[i].days[l].end_hour) >= 4)||
                (cooks_attributes[i].days[l].end_hour==24))){//if it is correct working day duration at the situation

                if ((g==0) && (cooks[i].russian == 1)){
                  broke = writeCookEntry(day, h, l, cooks[i], cooks_attributes[i], "russian", time_restaurants[g], schedule[day][h][g]);
                  break;
                }
                if ((g==1) && (cooks[i].italian == 1)){
                  broke = writeCookEntry(day, h, l, cooks[i], cooks_attributes[i], "italian", time_restaurants[g], schedule[day][h][g]);
                  break;
                }
                if ((g==2) && (cooks[i].japanese == 1)){
                  broke = writeCookEntry(day, h, l, cooks[i], cooks_attributes[i], "japanese", time_restaurants[g], schedule[day][h][g]);
                  break;
                }

              }//large if
            }//for each configure of the day
            if (broke){
              break;
            } else if (i == (cooks.length - 1)){
              if (preferring_constraint == 1){
                preferring_constraint = 0;//try to find less preferred shifts
                continue;
              }
              return time_restaurants;
            }
          }// for each cook
        }// for each restaurant
      }// for each kitchen
    }// while restaurants isn't filled
  }// for each day in month
  //showSchedule(schedule);
  return schedule;
}

function showSchedule(schedule){
  console.log("Schedule:");
  for (var i = 0; i < schedule.length; i++){
    console.log((i+1)+" day :");
    for (var j = 0; j < schedule[i].length; j++){
      console.log("   "+(j+1) + " restaurant :");
      for (var k = 0; k < schedule[i][j].length; k++){
        if(k==0) console.log("      russian kitchen :");
        if(k==1) console.log("      italian kitchen :");
        if(k==2) console.log("      japanese kitchen :");
        for (var l = 0; l < schedule[i][j][k].length; l++){
          console.log("         "+schedule[i][j][k][l].snp+" : "+schedule[i][j][k][l].worktime);
        }// for each cook
      }// for each kitchen
    }// for each restaurant
  }// for each day
}

function clearTimeRestaurants(time_restaurants){
  for (var j = 0; j < time_restaurants.length; j++){
    for (var i = 0; i < time_restaurants[j].length; i++){
      time_restaurants[j][i] = 10;//clear restaurant's state
    }
  }
}

function initializeSchedule(schedule, num_of_days, num_of_restaurants, num_of_kitchens){
  var schedule = new Array(num_of_days);
  for (var i = 0; i < num_of_days; i++){
    schedule[i] = new Array(num_of_restaurants);//create in day-entry entries for each restaurant
    for (var j = 0; j < num_of_restaurants; j++){
      schedule[i][j] = new Array(num_of_kitchens);//create in restaurant-entry entries for each kitchen
      for (var k = 0; k < num_of_kitchens; k++){
        schedule[i][j][k] = [];//create in kitchen-entry place for cooks info
      }// for each kitchen
    }// for each restaurant
  }// for each day
  return schedule;
}

function initializeTimeRestaurants(num_of_kitchens, num_of_restaurants){
  var time_restaurants = new Array(num_of_kitchens);
  for (var i = 0; i < num_of_kitchens; i++){
    time_restaurants[i] = new Array(num_of_restaurants);
  }
  return time_restaurants;
}

function writeCookEntry(day,h,l, cook, cook_config, qualification, time_kitchen_entry, kitchen_entry){
  var cook_entry = {};
  cook_entry.id = cook.cookid;
  cook_entry.snp = cook.surname+" "+cook.name+" "+cook.patronymic;
  cook_entry.worktime = cook_config.days[l].begin_hour+":00 - "+cook_config.days[l].end_hour+":00";

  //schedule[day][h][g]
  kitchen_entry.push(cook_entry);

  //time_restaurants[g][h]
  time_kitchen_entry[h] = cook_config.days[l].end_hour;
  cook_config.workdaycounter++;
  cook_config.busy = 1;
  return true;
}

function handleWorkCounters(cook_config, workingmode_5_2, workdaysmax){
  if ((cook_config.workingmode_5_2 == workingmode_5_2) && (cook_config.workdaycounter >= workdaysmax)){// if cook's workmode 5/2 and he worked 5 days
    if (cook_config.restdaycounter < 2){// if he isn't got rest 2 days, skip him for today
      cook_config.busy = 1;
      cook_config.restdaycounter++;
      return true;//give him this day for rest
    } else {// if he has got 2 rest days, set counters to 0 and try to give him work
      cook_config.workdaycounter = 0;
      cook_config.restdaycounter = 0;
    }
  }
  return false;
}

function isAllBusy(time_restaurants){
  for (i in time_restaurants){
    for (j in time_restaurants[i]){
      if (time_restaurants[i][j] != 24){
        return false;
      }
    }
  }
  return true;
}

function unbusyAll(cooks){
  for (var i = 0; i < cooks.length; i++){
    cooks[i].busy = 0;
  }
}

function isAllCooksBusy(cooks){
  for (var i = 0; i < cooks.length; i++){
    if (cooks[i].busy == 0){
        return false;
    }
  }
  return true;
}

app.listen(3000);
