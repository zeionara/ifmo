from threading import Thread
from time import sleep
import numpy as np

grammar = (
    ("program", [
        [
            ["variables declaration", None],
            ["computings declaration", None]
        ]
    ]),
    ("computings declaration", [
        [
            ["keyword", "Begin"],
            ["operators list", None],
            ["keyword", "End"],
            ["separator", "."]
        ]
    ]),
    ("variables declaration", [
        [
            ["keyword","Var"],
            ["variables list", None]
        ]
    ]),
    ("variables list", [
        [
            ["identifier", None],
            ["continuation of variables list", None]
        ]
    ]),
    ("continuation of variables list", [
        [
            ["separator", ","],
            ["variables list", None]
        ],
        [
            ["separator", ";"],
            ["end of variables list", None]
        ]
    ]),
    ("end of variables list", [
        [
            ["variables list", None]
        ],
        [
            #[None, None]
        ]
    ]),
    ("operators list", [
        [
            ["operator", None],
            ["continuation of operators list", None]
        ]
    ]),
    ("continuation of operators list", [
        [
            ["operators list", None]
        ],
        [
            #[None, None]
        ]
    ]),
    ("operator", [
        [
            ["making equal operator", None]
        ],
        [
            ["hard operator", None]
        ],
        [
            ["complex operator", None]
        ]
    ]),
    ("complex operator",[
        [
            ["keyword", "Begin"],
            ["operators list", None],
            ["keyword", "End"]
        ]
    ]),
    ("making equal operator", [
        [
            ["identifier", None],
            ["equality operator", None],
            ["expression", None],
            ["separator", ";"]
        ]
    ]),
    ("expression", [
        [
            ["unary operator", None],
            ["subexpression", None]
        ],
        [
            ["subexpression", None]
        ]
    ]),
    ("subexpression", [
        [
            ["bracket", "("],
            ["expression", None],
            ["bracket", ")"],
            ["continuation of subexpression", None]
        ],
        [
            ["operand", None],
            ["continuation of subexpression", None]
        ]
    ]),
    ("continuation of subexpression", [
        [
            ["binary simple operator", None],
            ["subexpression", None],
            ["continuation of subexpression", None]
        ],
        [
            ["binary complex operator", None],
            ["subexpression", None],
            ["continuation of subexpression", None]
        ],
        [
            ["binary comparasion operator", None],
            ["subexpression", None],
            ["continuation of subexpression", None]
        ],
        [
            #[None, None]
        ]
    ]),
    ("operand", [
        [
            ["identifier", None]
        ],
        [
            ["constant", None]
        ]
    ]),
    ("hard operator", [
        [
            ["keyword", "If"],
            ["bracket", "("],
            ["expression", None],
            ["bracket", ")"],
            ["operator", None]
        ]
    ])
)

tst = ['keywordVar', 'identifier', 'separator,', 'identifier', 'separator,', 'identifier', 'separator;', 'keywordBegin', 'identifier',
'equality operator', 'constant', 'separator;', 'identifier', 'equality operator', 'unary operator', 'bracket(', 'identifier',
 'binary simple operator', 'constant', 'bracket)', 'keywordIf', 'bracket(', 'identifier', 'binary simple operator', 'identifier',
  'binary comparasion operator', 'constant', 'bracket)', 'keywordBegin', 'identifier', 'equality operator', 'identifier',
  'binary complex operator', 'constant', 'keywordEnd', 'keywordEnd', 'separator.']

def get_key(item):
    if item[1] != None:
        key = item[0] + item[1]
    else:
        key = item[0]
    return key

def rep(program, position, key, k):
    return program[:position] + [key] + program[position + k:]

def contains(lst, value):
    try:
        lst.index(value)
    except ValueError:
        return False
    return True

def replace(program, deep):
    if deep == 0:
        return
    print(program)
    global grammar
    single = []
    double = []
    triple = []
    quadro = []
    penta = []
    #print(program)
    for i in range(len(program)):
        for rule in grammar:
            for alternative in rule[1]:
                if (len(alternative) == 1):
                    if (get_key(alternative[0]) == program[i]):
                        #print(program[i])
                        single.append([i, rule[0]])
                        if (len(alternative) == 2) and (i < len(program) - 1):
                            if (get_key(alternative[1]) == program[i + 1]):
                                #print("------",program[i])
                                double.append([i, rule[0]])
                                if (len(alternative) == 3) and (i < len(program) - 2):
                                    if (get_key(alternative[2]) == program[i + 2]):
                                        #print("------>>>>>>>>>",program[i])
                                        triple.append([i, rule[0]])
                                        if (len(alternative) == 4) and (i < len(program) - 3):
                                            if (get_key(alternative[3]) == program[i + 3]):
                                                #print("------>>>>>>>>>////////////",program[i])
                                                quadro.append([i, rule[0]])
                                                if (len(alternative) == 5) and (i < len(program) - 4):
                                                    if (get_key(alternative[4]) == program[i + 4]):
                                                        #print("------>>>>>>>>>+++++++++++",program[i])
                                                        penta.append([i, rule[0]])




    for s in penta:
        thread = Thread(target = replace, args = (rep(program, s[0], s[1], 5), deep - 1))
        thread.start()
    for s in quadro:
        thread = Thread(target = replace, args = (rep(program, s[0], s[1], 4), deep - 1))
        thread.start()
    for s in triple:
        thread = Thread(target = replace, args = (rep(program, s[0], s[1], 3), deep - 1))
        thread.start()
    for s in double:
        thread = Thread(target = replace, args = (rep(program, s[0], s[1], 2), deep - 1))
        thread.start()
    for s in single:
        thread = Thread(target = replace, args = (rep(program, s[0], s[1], 1), deep - 1))
        thread.start()
    #np = program
    #for s in single:
    #    used = []
    #    if (not contains(used, s[0])):
    #        np = rep(np, s[0], s[1], 1)
    #        used.append(s[0])

    #thread = Thread(target = replace, args = (np, deep - 1))
    #thread.start()
    #print(rep(program, single[0][0], single[0][1], 1))
    #print(single, double, triple, quadro, penta)



def insert(program, alt, pos):
    res = []
    for al in alt:
        if al[1] == None:
            res.append(al[0])
        else:
            res.append(al[0]+al[1])
    return list(program[:pos]) + res + list(program[pos+1:])

def threaded_function(arg):
    print(arg)

def threadededd_function(arg):
    global leng
    while True:
        if (len(stats) > 0):
            print(np.amax(stats))
        sleep(1)

stats = []
leng = 0

def cmp(prog):
    global tst
    global leng
    cnt = 0
    for i in range(len(prog)):
        if tst[i] == prog[i]:
            cnt += 1
        else:
            break;
    for i in range(len(prog)):
        if tst[-i] == prog[-i]:
            cnt += 1
        else:
            break;
    if (len(stats) > 0):
        old_max = np.amax(stats)
    else:
        old_max = -100
    stats.append(cnt/len(tst)*100)
    #stats.sort()

    if old_max <= np.amax(stats):
        return True
    else:
        leng = len(prog)
        return False
    #return cnt/len(tst)*100

def threadeded_function(program, deep):
    print(program)
    global stats
    global leng
    #cmpres = cmp(program)
    #print(program, len(program))
    #if cmp(program):
    #    return
    #if len(stats) > 0:
        #print(program, np.amax(stats), leng)
    if deep == 0:
        return
    while True:
        for sentence in program:
            for rule in grammar:
                #print(rule[0])
                if rule[0] == sentence:
                    for alternative in rule[1]:
                        if (len(rule[1]) == 1):
                            program = insert(program, alternative, program.index(sentence))
                            #print(program)
                        else:
                            if cmp(insert(program, alternative, program.index(sentence))):
                                thread = Thread(target = threadeded_function, args = (insert(program, alternative, program.index(sentence)), deep - 1))
                                thread.start()

                    if (len(rule[1]) > 1):
                        return




if __name__ == "__main__":
    replace(tst, 10)
    #deep = 2
    #program = ["program"]
    #print(program)
    #thread = Thread(target = threadededd_function, args = (1,))

    #thread.start()
    #for sentence in program:
        #for rule in grammar:
            #if rule[0] == sentence:
                #for alternative in rule[1]:
                    #thread = Thread(target = threadeded_function, args = (insert(program, alternative, 0), deep))
                    #thread.start()
                #print(newp)
    #
    #thread.start()
    #thread.join()
    #print("thread finished...exiting")
