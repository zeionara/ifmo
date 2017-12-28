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
            [None, None]
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
            [None, None]
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
            [None, None]
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

def get_key(item):
    if item[1] != None:
        key = item[0] + item[1]
    else:
        key = item[0]
    return key

def get_nullable(grammar):
    nullable = {}
    changed = False
    for rule in grammar:
        nullable[rule[0]] = False
        for alternative in rule[1]:
            for item in alternative:
                if (item[0] != None):
                    nullable[get_key(item)] = False

    changed = True
    while (changed == True):
        changed = False
        for rule in grammar:
            for alternative in rule[1]:
                all_nullable = True
                for item in alternative:
                    if (item[0] != None):
                        if (nullable[get_key(item)]) == False:
                            all_nullable = False
                            break
                if (all_nullable == True) and (nullable[rule[0]] == False):
                    nullable[rule[0]] = True
                    changed = True

    return nullable

def get_terminals(grammar):
    non_terminals = [rule[0] for rule in grammar]
    terminals = []
    for rule in grammar:
        for alternative in rule[1]:
            for item in alternative:
                try:
                    non_terminals.index(item[0])
                except Exception as e:
                    if (item[0] != None):
                        terminals.append(get_key(item))
    return list(set(terminals))

def not_contains(lst, values):
    for value in values:
        try:
            lst.index(value)
        except:
            return True
    return False

def get_first(grammar, nullable):
    terminals = get_terminals(grammar)
    non_terminals = [rule[0] for rule in grammar]
    first = {}
    for terminal in terminals:
        first[terminal] = [terminal]
    for non_terminal in non_terminals:
        first[non_terminal] = []
    #print(first)
    changed = True
    while (changed == True):
        changed = False
        for rule in grammar:
            for alternative in rule[1]:
                if (alternative[0][0] != None) and (not_contains(first[rule[0]], first[get_key(alternative[0])])):
                    first[rule[0]] = list(set(first[rule[0]] + first[get_key(alternative[0])]))
                    changed = True
                for i in range(1, len(alternative) - 1):
                    if (nullable[get_key(alternative[i])] == True) and (not_contains(first[rule[0]], first[get_key(alternative[i + 1])])):
                        first[rule[0]] = list(set(first[rule[0]] + first[get_key(alternative[i + 1])]))
                        changed = True
                    else:
                        break
    return first

def get_first_for_chain(beta_chain, first):
    if beta_chain == []:
        return beta_chain
    result = []
    if (get_key(beta_chain[0]) != None):
        result += first[get_key(beta_chain[0])]
    for i in range(1, len(beta_chain) - 1):
        if (get_key(beta_chain[i]) == None):
            continue
        if (nullable[get_key(beta_chain[i])] == True):
            result += first[get_key(beta_chain[i + 1])]
        else:
            break
    return result

def is_chain_nullable(beta_chain, nullable):
    if beta_chain == []:
        return True
    for item in beta_chain:
        if item[0] == None:
            continue
        if nullable[get_key(item)] == False:
            return False
    return True

def get_follow(grammar, nullable, first):
    non_terminals = [rule[0] for rule in grammar]
    follow = {}
    for non_terminal in non_terminals:
        follow[non_terminal] = []

    changed = True
    last_alt = []
    while changed:

        changed = False
        for non_terminal in non_terminals:
            print("\n",follow,"\n")
            print("\nscanning ",non_terminal)
            for rule in grammar:
                for alternative in rule[1]:
                    matched = False
                    for item in alternative:
                        if (item[0] == non_terminal):
                            matched = True
                    if matched:
                        print("alternative found : ",alternative)
                        beta_chain = alternative[[get_key(item) for item in alternative].index(non_terminal) + 1:]
                        print("beta chain : ",beta_chain)
                        first_for_beta_chain = get_first_for_chain(beta_chain, first)
                        print("first for beta chain : ",first_for_beta_chain)
                        if (not_contains(follow[non_terminal], first_for_beta_chain)):
                            follow[non_terminal] = list(set(follow[non_terminal] + first_for_beta_chain))
                            changed = True
                        if (is_chain_nullable(beta_chain, nullable)) and (not_contains(follow[non_terminal], follow[rule[0]])):
                            print("merging before (original): ",follow[non_terminal])
                            print(rule[0])
                            print("merging before (connected): ",follow[rule[0]])
                            follow[non_terminal] = list(set(follow[non_terminal] + follow[rule[0]]))
                            changed = True
    return follow

def contains(lst, value):
    try:
        lst.index(value)
    except ValueError:
        return False
    return True

nullable = get_nullable(grammar)
#print(nullable)
first = get_first(grammar, nullable)
#print(first)
follow = get_follow(grammar, nullable, first)
#print(follow)
#print(nullable)

terminals = get_terminals(grammar)
non_terminals = [rule[0] for rule in grammar]

for x in non_terminals:
    for c in terminals:
        counter = 0
        #print(x,c)
        for rule in grammar:
            if (rule[0] != x):
                continue
            for alternative in rule[1]:
                if contains(get_first_for_chain(alternative, first), c) or (contains(follow[x], c) and is_chain_nullable(alternative, nullable)):
                    #print(follow[x])
                    #print(x,c)
                    #print(rule[0], " ::= ", alternative)
                    if counter >= 1:
                        print("Found collision for non-terminal %s and terminal %s" % (x,c))
                        print(alternative)
                        print(last_alt)
                        #print("===================================================")
                    last_alt = alternative
                    counter += 1



#for rule in grammar:
#    for alternative in rule[1]:
#        print(rule[0]," ::= ",alternative)
#        print(get_first_for_chain(alternative, first))
