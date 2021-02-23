'''
Algo idea:
    1. Sort pizza list, key ingredients
    2. Start with group 4, then 3, then 2
    3. First pizza -> most ingredients
    4. Second Pizza -> (2 options)
        4.1 -> most unique ingredients
        4.2 -> smallest intersection with P1
    5. Third Pizza -> repeat (4.1 or 4.2), only with (P1 U P2)
    6. Fourth Pizza -> Same
'''

import sys, os
import numpy as np
from functools import reduce
from itertools import chain
from collections import defaultdict
import time

M, T2, T3, T4 = map(int, input().rstrip('').split(" "))
pizzas = []
ingredients = {}

def time_decorator(original_func, *args, **kwargs):   
    def wrapper(*args, **kwargs):
        t = time.time()
        result = original_func(*args, **kwargs)
        print('%s - > time is -> %.2f seconds' %(original_func.__name__, time.time() - t))    
        return result
    return wrapper

for pizza_index in range(M):
    l = input().split(' ')

    for ingredient in l[1:]:
        if ingredient not in ingredients:
            ingredients[ingredient] = len(ingredients)

    pizzas.append((pizza_index, [ingredients[ingredient] for ingredient in l[1:]]))
    
# print('Finished reading file.')

def heuristic(union, total, new_pizza):
    U = len(union | set(new_pizza))
    T = total + len(new_pizza)
    I = T - U
    return (I, -U)

def select_team(selected_pizzas):
    r = len(pizzas) + len(selected_pizzas)
    return 3 if (r==5) else 4 if (T4>0 and r>=4) else 3 if (T3>0 and r>=3) else 2 if (T2>0 and r>=2) else 0

def get_min(selected_pizzas, pizzas):
    union = reduce(lambda a,b: a|b, (set(p[1]) for p in selected_pizzas), set())
    total = sum(len(set(p[1])) for p in selected_pizzas)
    return min(enumerate(pizzas), key = lambda p : heuristic(union, total, p[1][1]))

# Sort by heuristic for selecting first pizza
pizzas = sorted(pizzas, key = lambda p : len(p))

solution = {2:[], 3:[], 4:[]}
k = 0
while T2>0 and len(pizzas)>=2 or T3>0 and len(pizzas)>=3 or T4>0 and len(pizzas)>=4:
    #print('Team {}. Remaining pizzas {}'.format(k, len(pizzas)))
    k += 1
    selected_pizzas = [pizzas.pop()]
    team = select_team(selected_pizzas)    
    while len(selected_pizzas) < team:        
        # Select a new pizza
        i, new_pizza = get_min(selected_pizzas, pizzas)
        
        pizzas.pop(i)
        selected_pizzas.append(new_pizza)
        team = select_team(selected_pizzas)

    if team != 0:
        if team == 4:
            T4 -= 1
        elif team == 3:
            T3 -= 1
        elif team == 2:
            T2 -= 1
        solution[team].append(selected_pizzas)

print(sum(len(s) for s in solution.values()))
for key in solution.keys():
    for team in solution[key]:
        print(key,' '.join(map(lambda x: str(x[0]), team)))

def score(solution):
    total = 0
    for team in sum(solution.values(),list()):
        union = len(reduce(lambda a,b: a|b, (set(p[1]) for p in team), set()))
        total += union**2
    return total

print('Score:', score(solution))

'''
A – Example                     74 points
B – A little bit of everything  11,963 points
C – Many ingredients            449,292,610 points
D – Many pizzas                 6,444,770 points
E – Many teams                  9,841,310 points
Total score                     465,590,727 points
'''