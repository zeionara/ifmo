almbd = 3.3
b = 6
channels = 1

def delete_long_spaces(content):
    content = content.replace("\t"," ");
    for i in range(1,10):
        content = content.replace(i*" "," ");
    for i in range(1,10):
        content = content.replace(i*" "," ");
    for i in range(1,10):
        content = content.replace(i*" "," ");
    return content

def get_utility(section, pribor, content, primary_index, index):
    utility = content.split(section)[primary_index].split(pribor)[1].split(" ")[index];
    utility = utility.replace(".",",");
    return utility
def get_ave_time_queue(content, queue_num):
    return content.split("QUEUE")[7].split("\n")[queue_num].split(" ")[7].replace(".",",");
def get_ave_len_queue(content, queue_num):
    return content.split("QUEUE")[7].split("\n")[queue_num].split(" ")[6].replace(".",",");
def get_ave_time_semo(content):
    return content.split("TU5")[2].split(" ")[1].replace(".",",");
def get_kvr_time_semo(content):
    return content.split("TU5")[2].split(" ")[2].replace(".",",");
def get_lose_possibility(content, strt, q, index):
    came = float(content.split("TEST")[index].split(" ")[1]);
    passed = float(content.split("TEST")[index].split("QUEUE")[1].split(" ")[1]);
    return str(round(1 - passed/came,3)).replace(".",",");
    

def parse_gpss_result_main(filenames, strt, q):
    for filename in filenames:
        
        with open(filename, "r") as handler:
            content = delete_long_spaces(handler.read());
            print("Загрузка"+"\t"+get_utility("STORAGE","PRIBOR1", content, 2, 8)+"\t"+
                  get_utility("FACILITY","PRIBOR2", content, 1, 2)+"\t"+
                  get_utility("FACILITY","PRIBOR3", content, 1, 2));
            print("Нагрузка"+"\t"+str(round(b/(2*almbd),3)).replace(".",",")+
                  "\t"+str(round(q*b/almbd,3)).replace(".",",")+"\t"+str(round((1-q)*b/almbd,3)).replace(".",","));
            print("Среднее время ожидания в очередях"+"\t"+
                  get_ave_time_queue(content, 1)+"\t"+get_ave_time_queue(content, 3)+
                  "\t"+get_ave_time_queue(content, 5));
            print("Средняя длина очередей"+"\t"+
                  get_ave_len_queue(content, 1)+"\t"+get_ave_len_queue(content, 3)+
                  "\t"+get_ave_len_queue(content, 5));
            print("Среднее время пребывания в СМО"+"\t"+
                  get_ave_time_queue(content, 2)+"\t"+get_ave_time_queue(content, 4)+
                  "\t"+get_ave_time_queue(content, 6));
            print("Среднее время пребывания во всей системе: "+"\t"+get_ave_time_semo(content));
            print("Коэффициент вариации времени пребывания во всей системе: "+"\t"+get_kvr_time_semo(content));
            #get_lose_possibility(content, strt, q);
            print("Вероятности потери заявок :"+"\t"+"0"+"\t"+get_lose_possibility(content, strt, q, 1)+"\t"+
                  get_lose_possibility(content, strt, q, 2));
            
def parse_gpss_result_second(filenames, strt, q):
    for filename in filenames:
        print("-"*10)
        with open(filename, "r") as handler:
            content = delete_long_spaces(handler.read());
            print(get_utility("STORAGE","PRIBOR1", content, 2, 8)+"\t"+
                  get_utility("FACILITY","PRIBOR2", content, 1, 2)+"\t"+
                  get_utility("FACILITY","PRIBOR3", content, 1, 2));
            print(str(round(b/(channels*almbd),3)).replace(".",",")+
                  "\t"+str(round(q*b/almbd,3)).replace(".",",")+"\t"+str(round((1-q)*b/almbd,3)).replace(".",","));
            print(get_ave_time_queue(content, 1)+"\t"+get_ave_time_queue(content, 3)+
                  "\t"+get_ave_time_queue(content, 5));
            print(get_ave_len_queue(content, 1)+"\t"+get_ave_len_queue(content, 3)+
                  "\t"+get_ave_len_queue(content, 5));
            print(get_ave_time_queue(content, 2)+"\t"+get_ave_time_queue(content, 4)+
                  "\t"+get_ave_time_queue(content, 6));
            print(get_ave_time_semo(content));
            print(get_kvr_time_semo(content));
            #get_lose_possibility(content, strt, q);
            print("0"+"\t"+get_lose_possibility(content, strt, q, 1)+"\t"+
                  get_lose_possibility(content, strt, q, 2));

if __name__ == "__main__":
    parse_gpss_result_second(["result_1.txt","result_2.txt","result_3.txt","result_4.txt","result_5.txt"], 100000, 0.462);
