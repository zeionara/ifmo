import re


#(название класса лексемы; следует ли искать точное соответствие в наборе значений или же там
#приведено регулярное выражение; набор значений; набор названий классов лексем, которые могут предшествовать
#лексеме данного класса)
lex_classes = (("keyword",True,("Begin","End","If","Var"),[]),
               ("separator",True,(",",";","."),[]),
               ("identifier",False,["[a-zA-Z]"],[]),
               ("constant",False,["[0-9]"],[]),
               ("binary comparasion operator",True,(">","<","=="),["identifier"]),
               ("equality operator",True,["="],["identifier"]),
               ("binary simple operator",True,("-","+"),["identifier"]),
               ("binary complex operator",True,("**","/","*"),["identifier"]),
               ("bracket",True,("(",")"),[]),
               ("unary operator",True,("-","not"),["equality operator", "bracket", "keyword"]))



table = {}

previous_class = ""

row_number = 1
comment = False
report = []
stop_after_fail = False



#Вывод названий всех классов лексем и соответствующих значений токенов в исходной программе
def show_lex_classes():
    print("%-30s %-10s" % ("class name","possible values"))
    for lex_class in lex_classes:
        print("%-30s %-10s" % (lex_class[0], " ".join(lex_class[2])))

show_lex_classes()

#Добавление в результирующую таблицу токена с номером строки, где он был обнаружен.
#Запись в таблице идентифицируется именем класса и значением токена.
#Если такой токен в таблице уже есть, то записывется только дополнительный номер строки.
def append_token_to_table(token_class, token_name, row_number):
    try:
        table.get((token_class, token_name)).append(row_number)
    except:
        table[(token_class, token_name)] = [row_number]

#Чтение программы из внешнего файла
def get_program_from_file(filename):
    program = ""
    with open(filename) as file_with_program:
        program += file_with_program.read()
    return program
shrp = []
#Попытка выделения лексемы из "урезанной" программы, то есть из программы, n начальных символов которой
#отброшены - при этом предполагается, что лексема должна начинаться с первого символа переданной
#программы и имеет максимально возможный размер. Функция возвращает длину выделенного токена в случае
#его идентификации и -1 в случае ошибки. Помимо всего прочего функция записывает строку в протокол
#разбора программы, а также фиксирует результат в таблице токенов
def match(program, lex_classes):
    global row_number
    global previous_class
    global comment
    global stop_after_fail
    if (ord(program[0]) == 10):
        row_number += 1
        if (comment):
            comment = False
        return 1
    if (comment):
        return 1
    if (program[:2] == "//"):
        comment = True
        return 1
    for lex_class in lex_classes:
        if ((len(lex_class[3]) != 0) and (previous_class not in (lex_class[3]))):
            continue
        if (lex_class[1]):
            for lex_template in lex_class[2]:
                if (program[:len(lex_template)] == lex_template):
                    report.append("%2i %s %s" % (row_number, lex_class[0], lex_template))
                    if (lex_class[0] == "keyword") or (lex_class[0] == "separator") or (lex_class[0] == "bracket"):
                        shrp.append("%s%s" % (lex_class[0], lex_template))
                    else:
                        shrp.append(lex_class[0])
                    #print("%2i %s %s" % (row_number, lex_class[0], lex_template))
                    append_token_to_table(lex_class[0], lex_template, row_number)
                    previous_class = lex_class[0]
                    return len(lex_template)
        else:
            for lex_template in lex_class[2]:
                length = 1
                matching_result = re.search("%s{%i}" % (lex_template, length),program[:length])
                if (matching_result == None):
                    continue
                while (matching_result != None):
                    length += 1
                    matching_result = re.search("%s{%i}" % (lex_template, length),program[:length])
                length -= 1
                matching_result = re.search("%s{%i}" % (lex_template, length),program[:length]).group(0)
                if (lex_class[0] == "constant"):
                    matching_result = hex(int(matching_result))
                report.append("%2i %s %s" % (row_number, lex_class[0], matching_result))
                shrp.append(lex_class[0])
                #print("%2i %s %s" % (row_number, lex_class[0], matching_result.group(0)))
                append_token_to_table(lex_class[0], matching_result, row_number)
                previous_class = lex_class[0]
                return length
    if (stop_after_fail):
        return -1
    return 1


#Удаление пробелов и символов табуляции из строки
def delete_spaces(string):
    return string.replace(chr(9),"").replace(chr(32),"")

#Основная функция, которая производит последовательный анализ переданной программы, выводит протокол
#анализа программы в случае успешного завершения и результирующую таблицу, и сообщение об ошибке,
#если был встречен неверный токен или неверная пара токенов
def analyze(program):
    global report
    start_index = 0

    while (start_index < len(program)):
        matching_result = match(program[start_index:], lex_classes)
        if (matching_result < 0):
            print(row_number)
            print("Program contains invalid token. Analyzing aborted.")
            return
        start_index += matching_result
    print("Program analyzed successfully")
    print("Program :")
    for row in report:
        print(row)
    print("Table : ")
    print("%-30s %-20s %-30s" % ("token class","token","row numbers"))
    for key in table:
        print("%-30s %-20s %-30s" % (key[0],key[1],",".join([str(row_num) for row_num in set(table[key])])))

analyze(delete_spaces(get_program_from_file("program2.txt")))
print(shrp)
