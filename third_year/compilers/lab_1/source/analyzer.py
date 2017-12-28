import re


#(название класса лексемы; следует ли искать точное соответствие в наборе значений или же там
#приведено регулярное выражение; набор значений; набор названий классов лексем, которые могут предшествовать
#лексеме данного класса)
lex_classes = (("KEYWORD",True,("Begin","End","If","Var"),[]),
               ("SEPARATOR",True,(",",";","."),[]),
               ("IDENTIFIER",False,["[a-zA-Z]"],[]),
               ("CONSTANT",False,["[0-9]"],[]),
               ("BINARY COMPARASION OPERATOR",True,(">","<","=="),["IDENTIFIER"]),
               ("EQUALITY OPERATOR",True,["="],["IDENTIFIER"]),
               ("BINARY SIMPLE OPERATOR",True,("-","+"),["IDENTIFIER"]),
               ("BINARY COMPLEX OPERATOR",True,("**","/","*"),["IDENTIFIER"]),
               ("BRACKET",True,("(",")"),[]),
               ("UNARY OPERATOR",True,("-","not"),["EQUALITY OPERATOR", "BRACKET", "KEYWORD"]))

grammar = {(("VARIABLES DECLARATION",""),("COMPUTINGS DESCRIPTION","")): "PROGRAM",
           (("KEYWORD","Begin"),("OPERATORS LIST",""),("KEYWORD","End"),("SEPARATOR",".")):"COMPUTINGS DESCRIPTION",
           (("KEYWORD","Var"),("VARIABLES LIST","")):"VARIABLES DECLARATION",
           (("IDENTIFIER",""),("SEPARATOR",";")):"VARIABLES LIST",
           (("IDENTIFIER",""),("SEPARATOR",","),("VARIABLES LIST","")):"VARIABLES LIST",
           (("IDENTIFIER",""),("SEPARATOR",";"),("VARIABLES LIST","")):"VARIABLES LIST",
           (("OPERATOR","")):"OPERATORS LIST",
           (("OPERATOR",""),("OPERATORS LIST","")):"OPERATORS LIST",
           (("EQUALITY","")):"OPERATOR",
           (("HARD OPERATOR","")):"OPERATOR",
           (("COMPLEX OPERATOR","")):"OPERATOR",
           (("IDENTIFICATOR",""),("EQUALITY OPERATOR","="),("EXPRESSION","")):"EQUALITY",
           (("UNARY OPERATOR",""), ("SUBEXPRESSION","")):"EXPRESSION",
           (("SUBEXPRESSION","")):"EXPRESSION",
           (("BRACKET","("),("EXPRESSION",""),("BRACKET",")")):"SUBEXPRESSION",
           (("OPERAND","")):"SUBEXPRESSION",
           (("SUBEXPRESSION",""),("BINARY SIMPLE OPERATOR",""),("SUBEXPRESSION","")):"SUBEXPRESSION",
           (("SUBEXPRESSION",""),("BINARY COMPLEX OPERATOR",""),("SUBEXPRESSION","")):"SUBEXPRESSION",
           (("SUBEXPRESSION",""),("BINARY COMPARASION OPERATOR",""),("SUBEXPRESSION","")):"SUBEXPRESSION",
           (("IDENTIFIER","")):"OPERAND",
           (("CONSTANT","")):"OPERAND",
           (("KEYWORD","If"),("BRACKET","("),("EXPRESSION",""),("BRACKET",")"),("OPERATOR","")):"HARD OPERATOR"}
#print(grammar)

def is_hardset(token_class):
    global lex_classes
    for cl in lex_classes:
        if cl[0] == token_class:
            return cl[1]
        
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
        
#show_lex_classes()

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
                    report.append((lex_class[0], lex_template, is_hardset(lex_class[0])))
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
                if (lex_class[0] == "CONSTANT"):
                    matching_result = hex(int(matching_result))
                report.append((lex_class[0], matching_result,is_hardset(lex_class[0])))
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
            #print(row_number)
            #print("Program contains invalid token. Analyzing aborted.")
            return
        start_index += matching_result
    #print("Program analyzed successfully")
    #print("Program :")
    
    #print("Table : ")
    #print("%-30s %-20s %-30s" % ("token class","token","row numbers"))
    #for key in table:
    #    print("%-30s %-20s %-30s" % (key[0],key[1],",".join([str(row_num) for row_num in set(table[key])])))

def get_grammar_sub(key):
    #print(key)
    global grammar
    try:
        return grammar[key]
    except KeyError:
        return None

def substitute(report, index, new):
    return report[:index] + [new] + report[(index+1):]

def find(sett, item):
    for i in sett:
        if i == item:
            return True
    return False

def find_id(sett, items):
    ind = 0
    l = len(items)
    for i in range(0, len(sett)-l):
        #print(sett[i])
        il = 0
        found = True
        for it in items:
            #print(">>>>>"+str(it))
            if it != sett[i + il]:
                found = False
                break
            il += 1
        if (found):
            return i
    return None

def replacess(replaced, report):
    global grammar;
    for rep in replaced:
        print(rep)
        beg = find_id(report,rep)
        if beg == None:
            continue
        return report[:beg] + [(grammar[rep],"")] + report[beg+len(rep):]
    return report

srep = []

def syntaxically_analyzes(report):
    global srep
    for row in report:
        if (is_hardset(row[0])):
            old = ((row[0],row[1]))
        else:
            old = ((row[0],""))
        srep.append(old)
    
    index = 0
    for i in range(6):
        hard_sett = []
        print("STARTED");
        print(srep)
        print(hard_sett)
        index = 0
        print("--"*10)
        old_sett = []
        new_sett = []
        for key in grammar:
            old_sett.append([key,[]])
        hard_sett = []
        ind = 0
        while (len(old_sett) > 0):
            print("iiiiiiiiiiiiiiiiiiiiiiiiiiiiiii")
            for row in srep:
                #print("="*20)
                #print(old)
                for key in old_sett:
                    #print(key)
                    try:
                        if ((len(key[0]) == 1) and (key[0] == row)) or ((len(key[0]) > 1) and (key[0][ind] == row) and ):
                            new_sett.append(key)
                    except:
                        hard_sett.append(key)
                        pass
                    #print("ok!")
            old_sett = list(set(old_sett))
            new_sett = list(set(new_sett))
            print(old_sett)
            print("--"*30)
            print(new_sett)
            old_sett = []
            for s in new_sett:
                old_sett.append(s)
            new_sett = []
            ind += 1
        print(list(set(hard_sett)))
        print(srep)
        srep = replacess(list(set(hard_sett)), srep)
        print("0000000000")
        print(srep)
            #if (is_hardset(row[0])):
            #    new = (get_grammar_sub((row[0],row[1])),"")
            #else:
            #    new = (get_grammar_sub((row[0],"")),"")
            #print(new)
            #if (new[0] != None):
                #print(new)
            #    report = substitute(report, index, new)
                #print(report)
            #index += 1
        #print(report)
        
def syntaxically_analyze(report):
    global srep
    for row in report:
        if (is_hardset(row[0])):
            old = ((row[0],row[1]))
        else:
            old = ((row[0],""))
        srep.append(old)
    
    
    for i in srep:
        for j in srep:
            for k in srep:
                for l in srep:
                    for m in srep:
                        get_grammar_sub((i,j,k,l))
    print(srep)
        

    
analyze(delete_spaces(get_program_from_file("program2.txt")))
syntaxically_analyze(report)

#syntaxically_analyze(report)