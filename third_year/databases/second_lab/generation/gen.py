from random import randint

m_names = ['Дмитрий','Алексей','Александр','Евгений','Владислав','Никита']
f_names = ['Дарья','Мария','Анастасия','Наташа','Евгения','Елена']

m_fams = ['Иванов','Петров','Сидоров','Краснов','Белов','Никитин']
f_fams = ['Иванова','Петрова','Сидорова','Краснова','Белова','Никитина']

m_pats = ['Дмитриевич','Алексеевич','Александрович','Евгеньевич',
          'Владиславович','Никитич']
f_pats = ['Дмитриевна','Алексеевна','Александровна','Евгеньевна',
          'Владиславовна','Никитична']
cities = ['Москва','Санкт-Петербург','Владивосток','Калининград','Магнитогорск','Екатеринбург']
streets = ['пр. Победы','пер. Гривцова','пр. Кронверкский','ул. Фучика','ул. Турку','ул. Димитрова']

for i in range(20):
    phone = '8 ('+str(randint(900,999))+') '+str("%03i" % randint(0,999))+'-'+str("%02i" % randint(0,99))+'-'+str("%02i" % randint(0,99))
    sex = randint(1, 2)
    pat = randint(1, 10)
    birthday = str("%02i" % randint(1,28))+"."+str("%02i" % randint(1,12))+"."+str(randint(1950,1990))
    if (pat < 8):    
        print('INSERT INTO таблица_1 (фамилия, имя, отчество, дата_рождения, пол, место_рождения, адрес, телефон)');
    
        if sex == 1:
            print('VALUES(\''+m_fams[randint(0,5)]+'\',\''+m_names[randint(0,5)]+'\',\''+m_pats[randint(0,5)]+'\',STR_TO_DATE(\''+birthday+"\',\'%d.%m.%Y\'),\'м\',\'"+
              cities[randint(0,5)]+'\',\''+streets[randint(0,5)]+' д '+str(randint(2,30))+' кв '+str(randint(13,666))+
              '\',\''+phone+'\');')
        else:
            print('VALUES(\''+f_fams[randint(0,5)]+'\',\''+f_names[randint(0,5)]+'\',\''+f_pats[randint(0,5)]+'\',STR_TO_DATE(\''+birthday+"\',\'%d.%m.%Y\'),\'ж\',\'"+
              cities[randint(0,5)]+'\',\''+streets[randint(0,5)]+' д '+str(randint(2,30))+' кв '+str(randint(13,666))+
              '\',\''+phone+'\');')
        print()
    else:
        print('INSERT INTO таблица_1 (фамилия, имя, дата_рождения, пол, место_рождения, адрес, телефон)');
        if sex == 1:
            print('VALUES(\''+m_fams[randint(0,5)]+'\',\''+m_names[randint(0,5)]+'\',STR_TO_DATE(\''+birthday+"\',\'%d.%m.%Y\'),\'м\',\'"+
              cities[randint(0,5)]+'\',\''+streets[randint(0,5)]+' д '+str(randint(2,30))+' кв '+str(randint(13,666))+
              '\',\''+phone+'\');')
        else:
            print('VALUES(\''+f_fams[randint(0,5)]+'\',\''+f_names[randint(0,5)]+'\',STR_TO_DATE(\''+birthday+"\',\'%d.%m.%Y\'),\'ж\',\'"+
              cities[randint(0,5)]+'\',\''+streets[randint(0,5)]+' д '+str(randint(2,30))+' кв '+str(randint(13,666))+
              '\',\''+phone+'\');')
        print()
