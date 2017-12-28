from random import randint

id_min = 1
id_max = 16
num_of_days = 30
departments = ['отдел продаж северного крыла','отдел продаж южного крыла','отдел продаж восточного крыла','отдел продаж западного крыла']
day_individual_statuses = ['отпуск','командировка','больничный']
day_common_statuses = ['выходной','праздник']

days = ['']*num_of_days
weekend = 0
days_after_holiday = randint(0,5)
for i in range(num_of_days):
    if (days_after_holiday == 5) and (weekend == 0):
        weekend = 1
        days[i] = day_common_statuses[0]
        continue;
    elif (days_after_holiday == 5) and (weekend == 1):
        weekend = 2
        days[i] = day_common_statuses[0]
        continue;
    elif weekend == 2:
        weekend = 0
        days_after_holiday = 1
        continue;
    days_after_holiday+=1

#print(days)

ill_period_length = 0
comand_period_length = 2
free_period_length = 0
worker_is_ill = 0
worker_is_comand = 0
worker_is_free = 0

for person_id in range(id_min, id_max+1):

    personal_days = ['']*num_of_days
    for i in range(len(personal_days)):
        personal_days[i] = days[i]

    for i in range(len(personal_days)):
        if (worker_is_ill == 0) and (worker_is_comand == 0) and (worker_is_free == 0):
            worker_status = randint(1,50)
            if worker_status >= 49:
                ill_period_length = randint(2,10)
                worker_is_ill = 1
            elif worker_status >= 46 and i + 1 < len(personal_days):
                if (personal_days[i] == '') and (personal_days[i+1] == ''):
                    worker_is_comand = 2
            elif worker_status >= 45:
                free_period_length = randint(7,14)
                worker_is_free = 1

        if (worker_is_ill == 1) and (ill_period_length > 0) and personal_days[i] == '':
            personal_days[i] = day_individual_statuses[2]
            ill_period_length -= 1
        elif (worker_is_ill == 1) and (ill_period_length == 0):
            worker_is_ill = 0

        if (worker_is_comand > 0):
            personal_days[i] = day_individual_statuses[1]
            worker_is_comand -=1

        if (worker_is_free == 1) and (free_period_length > 0):
            personal_days[i] = day_individual_statuses[0]
            free_period_length -= 1
        elif (worker_is_free == 1) and (ill_period_length == 0):
            worker_is_free = 0



    num_of_departments = randint(1,3)
    last_departments = []
        
    for j in range(num_of_departments):
        id_of_department = randint(0,3)
        while id_of_department in last_departments:
            id_of_department = randint(0,3)
        values = str(person_id) + "," + str(id_of_department+1)
        columns = "ид_человека,ид_отдела"
        for k in range(1, num_of_days+1):
            if personal_days[k-1] != '':
                columns += ",день_"+str(k);
                values += ",\'"+personal_days[k-1]+"\'"
        #print(columns)
        #print(values)
        print("INSERT INTO таблица_2 ("+columns+") VALUES ("+values+");")
        #print(personal_days)
        last_departments.append(id_of_department)
    





##for i in range(id_min, id_max+1):
##    num_of_departments = randint(1,3)
##    last_departments = []
##    
##    
##    for j in range(num_of_departments):
##        id_of_department = randint(0,3)
##        while id_of_department in last_departments:
##            id_of_department = randint(0,3)
##        last_departments.append(id_of_department)
##        
##    for j in num_of_days:
##        days[j] = 
##
##    for j in last_departments:
        
