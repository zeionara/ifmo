from random import randint

id_min = 17
id_max = 21

salary_min = 1000
salary_max = 5000

columns = 'ид_человека,зарплата_за_день,отпускные_за_день,больничные_за_день,командировочные_за_день'

for i in range(id_min, id_max+1):
    salary = randint(salary_min, salary_max)
    ill_k = randint(10,15)/10
    rest_k = randint(5,10)/10
    cmd_k = randint(15,20)/10
    values = str(i)+","+str(salary)+","+str(round(salary*rest_k))+","+str(round(salary*ill_k))+","+str(round(salary*cmd_k))
    print("INSERT INTO зарплаты ("+columns+") VALUES ("+values+");");

