from random import randint

id_min = 1
id_max = 16

goods = ['Стиральная машина','Холодильник','Посудомоечная машина','Водонагреватель','Плита',
           'Компьютер','Моноблок','Смартфон','Планшет','Ноутбук',
           'Телевизор','3D-Телевизор','Smart TV','4K-Телевизор','Портативный телевизор',
           'HDMI-VGA переходник','HDMI-mini HDMI переходник','USB - micro USB переходник','VGA-RGB переходник','USB - HDMI переходник']
prices = [13900, 24000, 20000, 400]
corps = ['Acer','Bosh','Samsung','Apple','Sony']

model_ids = [0]*2000
models = ['']*2000

for i in range(len(model_ids)):
    model_ids[i] = (i//500 + 1)*1000 + i%1000
    models[i] = goods[(i//500)*4 + randint(0,4)]+" "+corps[randint(0,4)]+" "+chr(randint(65,89))+"-"+str(i%1000)

columns = 'ид_товара,наименование_товара,количество,ид_человека,дата_продажи,цена'

for i in range(20):
    selldate = str("%02i" % randint(1,28))+"."+str("%02i" % randint(1,12))+"."+str(randint(2015,2016))
    id_good = randint(1,len(model_ids))
    values = str(model_ids[id_good])+",\'"+models[id_good]+"\'"+","+str(randint(1,20))+","+str(randint(id_min, id_max))+\
          ",STR_TO_DATE(\'"+selldate+"\',\'%d.%m.%Y\'),"+\
        str(randint(prices[id_good//1000],prices[id_good//1000]*10))
    print("INSERT INTO таблица_3 ("+columns+") VALUES ("+values+");");
    

#print(models)
